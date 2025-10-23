#include "Garfield/AvalancheMC.hh"

#include <array>
#include <cmath>
#include <iostream>
#include <string>

#include "Garfield/Component.hh"
#include "Garfield/Exceptions.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Medium.hh"
#include "Garfield/Numerics.hh"
#include "Garfield/Random.hh"
#include "Garfield/Sensor.hh"
#include "Garfield/ViewDrift.hh"

namespace {

Garfield::AvalancheMC::Point MakePoint(const std::array<double, 3>& x,
                                       const double t) {
  Garfield::AvalancheMC::Point p;
  p.x = x[0];
  p.y = x[1];
  p.z = x[2];
  p.t = t;
  return p;
}

Garfield::AvalancheMC::Point MakePoint(const double x, const double y,
                                       const double z, const double t) {
  Garfield::AvalancheMC::Point p;
  p.x = x;
  p.y = y;
  p.z = z;
  p.t = t;
  return p;
}

Garfield::AvalancheMC::Seed MakeSeed(const Garfield::AvalancheMC::Point point,
                                     const Garfield::Particle particle,
                                     const size_t w) {
  Garfield::AvalancheMC::Seed seed;
  seed.pt = point;
  seed.type = particle;
  seed.w = w;
  return seed;
}

std::string PrintVec(const std::array<double, 3>& x) {
  return "(" + std::to_string(x[0]) + ", " + std::to_string(x[1]) + ", " +
         std::to_string(x[2]) + ")";
}

double Mag(const std::array<double, 3>& x) {
  return sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
}

double Dist(const std::array<double, 3>& x0, const std::array<double, 3>& x1) {
  std::array<double, 3> d = x1;
  for (size_t i = 0; i < 3; ++i) d[i] -= x0[i];
  return Mag(d);
}

double Slope(const double x0, const double x1) {
  return (x0 > 0. && x1 > 0.) ? fabs(x1 - x0) / (x0 + x1) : 0.;
}

std::array<double, 3> MidPoint(const std::array<double, 3>& x0,
                               const std::array<double, 3>& x1) {
  std::array<double, 3> xm;
  for (size_t k = 0; k < 3; ++k) xm[k] = 0.5 * (x0[k] + x1[k]);
  return xm;
}

}  // namespace

namespace Garfield {

/// Return the number of electrons and ions/holes in the avalanche.
std::pair<std::size_t, std::size_t> AvalancheMC::GetAvalancheSize() const {
  return std::make_pair(m_nElectrons, std::max(m_nIons, m_nHoles));
}
/// Return the number of electrons and ions/holes in the avalanche.
void AvalancheMC::GetAvalancheSize(std::size_t& ne, std::size_t& ni) const {
  ne = m_nElectrons;
  ni = std::max(m_nIons, m_nHoles);
}

AvalancheMC::AvalancheMC(Sensor* sensor) { SetSensor(sensor); }

void AvalancheMC::SetSensor(Sensor* sensor) {
  if (!sensor) throw Exception("sensor can't be nullptr");
  m_sensor = sensor;
}

void AvalancheMC::EnablePlotting(ViewDrift* view) {
  if (!view) throw Exception("ViewDrift* is nullptr");
  m_viewer = view;
}

void AvalancheMC::SetTimeSteps(const double d) {
  m_stepModel = StepModel::FixedTime;
  if (d < Small) {
    std::cerr << m_className << "::SetTimeSteps:\n    "
              << "Step size is too small. Using default (20 ps) instead.\n";
    m_tMc = 0.02;
    return;
  }
  if (m_debug) {
    std::cout << m_className << "::SetTimeSteps:\n"
              << "    Step size set to " << d << " ns.\n";
  }
  m_tMc = d;
}

void AvalancheMC::SetDistanceSteps(const double d) {
  m_stepModel = StepModel::FixedDistance;
  if (d < Small) {
    std::cerr << m_className << "::SetDistanceSteps:\n    "
              << "Step size is too small. Using default (10 um) instead.\n";
    m_dMc = 0.001;
    return;
  }
  if (m_debug) {
    std::cout << m_className << "::SetDistanceSteps:\n"
              << "    Step size set to " << d << " cm.\n";
  }
  m_dMc = d;
}

void AvalancheMC::SetCollisionSteps(const std::size_t n) {
  m_stepModel = StepModel::CollisionTime;
  if (n < 1) {
    std::cerr << m_className << "::SetCollisionSteps:\n    "
              << "Number of collisions set to default value (100).\n";
    m_nMc = 100;
    return;
  }
  if (m_debug) {
    std::cout << m_className << "::SetCollisionSteps:\n    "
              << "Number of collisions to be skipped set to " << n << ".\n";
  }
  m_nMc = n;
}

void AvalancheMC::SetStepDistanceFunction(double (*f)(double x, double y,
                                                      double z)) {
  if (!f) throw Exception("f is nullptr");
  m_fStep = f;
  m_stepModel = StepModel::UserDistance;
}

void AvalancheMC::SetTimeWindow(const double t0, const double t1) {
  if (fabs(t1 - t0) < Small)
    throw Exception("Time interval must be greater than zero");
  m_tMin = std::min(t0, t1);
  m_tMax = std::max(t0, t1);
  m_hasTimeWindow = true;
}

void AvalancheMC::GetIonEndpoint(const size_t i, double& x0, double& y0,
                                 double& z0, double& t0, double& x1, double& y1,
                                 double& z1, double& t1, int& status) const {
  if (i >= m_ions.size()) throw Exception("Index out of range");
  x0 = m_ions[i].path.front().x;
  y0 = m_ions[i].path.front().y;
  z0 = m_ions[i].path.front().z;
  t0 = m_ions[i].path.front().t;
  x1 = m_ions[i].path.back().x;
  y1 = m_ions[i].path.back().y;
  z1 = m_ions[i].path.back().z;
  t1 = m_ions[i].path.back().t;
  status = m_ions[i].status;
}

void AvalancheMC::GetNegativeIonEndpoint(const size_t i, double& x0, double& y0,
                                         double& z0, double& t0, double& x1,
                                         double& y1, double& z1, double& t1,
                                         int& status) const {
  if (i >= m_negativeIons.size()) throw Exception("Index out of range");
  x0 = m_negativeIons[i].path.front().x;
  y0 = m_negativeIons[i].path.front().y;
  z0 = m_negativeIons[i].path.front().z;
  t0 = m_negativeIons[i].path.front().t;
  x1 = m_negativeIons[i].path.back().x;
  y1 = m_negativeIons[i].path.back().y;
  z1 = m_negativeIons[i].path.back().z;
  t1 = m_negativeIons[i].path.back().t;
  status = m_negativeIons[i].status;
}

void AvalancheMC::GetElectronEndpoint(const size_t i, double& x0, double& y0,
                                      double& z0, double& t0, double& x1,
                                      double& y1, double& z1, double& t1,
                                      int& status) const {
  if (i >= m_electrons.size()) throw Exception("Index out of range");
  x0 = m_electrons[i].path.front().x;
  y0 = m_electrons[i].path.front().y;
  z0 = m_electrons[i].path.front().z;
  t0 = m_electrons[i].path.front().t;
  x1 = m_electrons[i].path.back().x;
  y1 = m_electrons[i].path.back().y;
  z1 = m_electrons[i].path.back().z;
  t1 = m_electrons[i].path.back().t;
  status = m_electrons[i].status;
}

bool AvalancheMC::DriftElectron(const double x, const double y, const double z,
                                const double t, const size_t w) {
  std::vector<Seed> stack;
  stack.emplace_back(MakeSeed(MakePoint(x, y, z, t), Particle::Electron, w));
  return TransportParticles(stack, true, false, false);
}

bool AvalancheMC::DriftHole(const double x, const double y, const double z,
                            const double t, const size_t w) {
  std::vector<Seed> stack;
  stack.emplace_back(MakeSeed(MakePoint(x, y, z, t), Particle::Hole, w));
  return TransportParticles(stack, false, true, false);
}

bool AvalancheMC::DriftIon(const double x, const double y, const double z,
                           const double t, const size_t w) {
  std::vector<Seed> stack;
  stack.emplace_back(MakeSeed(MakePoint(x, y, z, t), Particle::Ion, w));
  return TransportParticles(stack, false, true, false);
}

bool AvalancheMC::DriftNegativeIon(const double x, const double y,
                                   const double z, const double t,
                                   const size_t w) {
  std::vector<Seed> stack;
  stack.emplace_back(MakeSeed(MakePoint(x, y, z, t), Particle::NegativeIon, w));
  return TransportParticles(stack, false, true, false);
}

int AvalancheMC::DriftLine(const Seed& seed, std::vector<Point>& path,
                           std::vector<Seed>& stack, const bool aval,
                           const bool signal) const {
  std::array<double, 3> x0 = {seed.pt.x, seed.pt.y, seed.pt.z};
  double t0 = seed.pt.t;
  // Make sure the starting point is inside an active region.
  std::array<double, 3> e0 = {0., 0., 0.};
  std::array<double, 3> b0 = {0., 0., 0.};
  Medium* m0 = nullptr;
  int status = GetField(x0, e0, b0, m0);

  if (status != 0) {
    std::cerr << m_className + "::DriftLine: "
              << PrintVec(x0) + " is not in a valid drift region.\n";
    return status;
  }
  // Add the first point to the line.
  path.push_back(seed.pt);
  if (m_debug) {
    std::cout << m_className + "::DriftLine: Starting at "
              << PrintVec(x0) + ".\n";
  }
  // Make sure the starting time is within the requested window.
  if (m_hasTimeWindow && (t0 < m_tMin || t0 > m_tMax)) {
    if (m_debug) std::cout << "    Outside the time window.\n";
    return StatusOutsideTimeWindow;
  }
  // Determine if the medium is a gas or semiconductor.
  const bool sc = m0->IsSemiconductor();
  const Particle ptype = seed.type;
  while (0 == status) {
    constexpr double tol = 1.e-10;
    // Make sure the electric field has a non-vanishing component.
    const double emag = Mag(e0);
    if (emag < tol && !m_useDiffusion) {
      std::cerr << m_className + "::DriftLine: Too small electric field at "
                << PrintVec(x0) + ".\n";
      status = StatusCalculationAbandoned;
      break;
    }
    // Compute the drift velocity at this point.
    std::array<double, 3> v0;
    if (!GetVelocity(ptype, m0, x0, e0, b0, v0)) {
      status = StatusCalculationAbandoned;
      break;
    }

    // Make sure the drift velocity vector has a non-vanishing component.
    double vmag = Mag(v0);
    if (vmag < tol && !m_useDiffusion) {
      std::cerr << m_className + "::DriftLine: Too small drift velocity at "
                << PrintVec(x0) + ".\n";
      status = StatusCalculationAbandoned;
      break;
    }

    // Coordinates after the step.
    std::array<double, 3> x1 = x0;
    // Time after the step.
    double t1 = t0;
    if (vmag < tol || emag < tol) {
      // Diffusion only. Get the mobility.
      const double mu = GetMobility(ptype, m0, x0);
      if (mu < 0.) {
        std::cerr << m_className + "::DriftLine: Invalid mobility.\n";
        status = StatusCalculationAbandoned;
        break;
      }
      // Calculate the diffusion coefficient.
      const double dif = mu * BoltzmannConstant * m0->GetTemperature();
      double sigma = 0.;
      switch (m_stepModel) {
        case StepModel::FixedTime:
          sigma = sqrt(2. * dif * m_tMc);
          t1 += m_tMc;
          break;
        case StepModel::FixedDistance:
          sigma = m_dMc;
          break;
        case StepModel::CollisionTime: {
          // Thermal velocity.
          const double vth =
              SpeedOfLight *
              sqrt(2 * BoltzmannConstant * m0->GetTemperature() / ElectronMass);
          sigma = m_nMc * dif / vth;
        } break;
        case StepModel::UserDistance:
          sigma = m_fStep(x0[0], x0[1], x0[2]);
          break;
        default:
          std::cerr << m_className + "::DriftLine: Unknown stepping model.\n";
          status = StatusCalculationAbandoned;
          break;
      }
      if (status != 0) break;
      if (m_stepModel != StepModel::FixedTime) {
        t1 += sigma * sigma / (2 * dif);
      }

      for (size_t i = 0; i < 3; ++i) x1[i] += RndmGaussian(0., sigma);
      if (!aval && m_useAttachment) {
        const double eta = GetAttachment(ptype, m0, x0, e0, b0);
        double patt = 0.;
        if (eta < 0.) {
          patt = 1. - std::exp(eta * (t1 - t0));
        } else {
          const double ds = Dist(x0, x1);
          patt = 1. - std::exp(-eta * ds);
        }
        if (RndmUniform() < patt) {
          x1 = MidPoint(x0, x1);
          t1 = 0.5 * (t0 + t1);
          path.emplace_back(MakePoint(x1, t1));
          status = StatusAttached;
          if (m_debug) std::cout << "    Attached.\n";
          break;
        }
      }

      if (m_useRecombination) {
        double prec = 0.;
        if (ptype == Particle::NegativeIon) {
          const double rho = GetNegativeIonDensity(x0);
          prec = 1. - std::exp(-m_alphaRecombination * rho * (t1 - t0));
        }
        if (ptype == Particle::Ion) {
          const double rho = GetIonDensity(x0);
          prec = 1. - std::exp(-m_alphaRecombination * rho * (t1 - t0));
        }
        if (RndmUniform() < prec) {
          x1 = MidPoint(x0, x1);
          t1 = 0.5 * (t0 + t1);
          path.emplace_back(MakePoint(x1, t1));
          status = StatusRecombined;
          if (m_debug) std::cout << "    Recombined.\n";
          break;
        }
      }

    } else {
      // Drift and diffusion. Determine the time step.
      double dt = 0.;
      switch (m_stepModel) {
        case StepModel::FixedTime:
          dt = m_tMc;
          break;
        case StepModel::FixedDistance:
          dt = m_dMc / vmag;
          break;
        case StepModel::CollisionTime:
          if (ptype == Particle::Ion || ptype == Particle::NegativeIon) {
            constexpr double c1 =
                AtomicMassUnitElectronVolt / (SpeedOfLight * SpeedOfLight);
            dt = -m_nMc * (c1 * vmag / emag) * log(RndmUniformPos());
          } else {
            constexpr double c1 = ElectronMass / (SpeedOfLight * SpeedOfLight);
            dt = -m_nMc * (c1 * vmag / emag) * log(RndmUniformPos());
          }
          break;
        case StepModel::UserDistance:
          dt = m_fStep(x0[0], x0[1], x0[2]) / vmag;
          break;
        default:
          std::cerr << m_className + "::DriftLine: Unknown stepping model.\n";
          status = StatusCalculationAbandoned;
          break;
      }
      if (status != 0) break;

      double difl = 0., dift = 0.;
      if (m_useDiffusion) {
        // Get the diffusion coefficients.
        if (!GetDiffusion(ptype, m0, e0, b0, difl, dift)) {
          PrintError("DriftLine", "diffusion", ptype, x0);
          status = StatusCalculationAbandoned;
          break;
        }
        if (m_stepModel != StepModel::FixedTime) {
          const double ds = vmag * dt;
          const double dif = std::max(difl, dift);
          if (dif * dif > ds) {
            dt = ds * ds / (dif * dif * vmag);
          }
        }
      }
      // Compute the proposed end point of this step.
      for (size_t k = 0; k < 3; ++k) x1[k] += dt * v0[k];
      std::array<double, 3> v1 = v0;
      std::array<double, 3> e1 = e0;
      std::array<double, 3> b1 = b0;
      constexpr std::size_t nMaxIter = 3;
      for (std::size_t i = 0; i < nMaxIter; ++i) {
        Medium* m1 = nullptr;
        status = GetField(x1, e1, b1, m1);
        if (status != 0) {
          // Point is outside the active region. Reduce the step size.
          x1 = MidPoint(x0, x1);
          dt *= 0.5;
          continue;
        }
        // Compute the velocity at the proposed end point.
        if (!GetVelocity(ptype, m1, x1, e1, b1, v1)) {
          status = StatusCalculationAbandoned;
          break;
        }
        if (Slope(vmag, Mag(v1)) < 0.05) break;
        // Halve the step.
        x1 = MidPoint(x0, x1);
        dt *= 0.5;
      }
      if (status == StatusCalculationAbandoned) break;
      if (m_doRKF) {
        StepRKF(ptype, x0, v0, dt, x1, v1, status);
        vmag = Mag(v1);
      }
      if (m_useDiffusion) AddDiffusion(sqrt(vmag * dt), difl, dift, x1, v1);
      if (!aval && m_useAttachment) {
        const double eta = GetAttachment(ptype, m0, x0, e0, b0);
        double patt = 0.;
        if (eta < 0.) {
          patt = 1. - std::exp(eta * dt);
        } else {
          const double ds = Dist(x0, x1);
          patt = 1. - std::exp(-eta * ds);
        }
        if (RndmUniform() < patt) {
          x1 = MidPoint(x0, x1);
          dt *= 0.5;
          path.emplace_back(MakePoint(x1, t0 + dt));
          status = StatusAttached;
          if (m_debug) std::cout << "    Attached.\n";
          break;
        }
      }
      if (m_useRecombination) {
        double prec = 0.;
        if (ptype == Particle::NegativeIon) {
          const double rho = GetIonDensity(x0);
          prec = 1. - std::exp(-m_alphaRecombination * rho * dt);
        }
        if (ptype == Particle::Ion) {
          const double rho = GetNegativeIonDensity(x0);
          prec = 1. - std::exp(-m_alphaRecombination * rho * dt);
        }
        if (RndmUniform() < prec) {
          x1 = MidPoint(x0, x1);
          dt *= 0.5;
          path.emplace_back(MakePoint(x1, t0 + dt));
          status = StatusRecombined;
          if (m_debug) std::cout << "    Recombined.\n";
          break;
        }
      }
      t1 += dt;
    }
    if (m_debug) std::cout << "    Next point: " << PrintVec(x1) + ".\n";

    // Get the electric and magnetic field at the new position.
    status = GetField(x1, e0, b0, m0);
    if (status == StatusLeftDriftMedium || status == StatusLeftDriftArea) {
      // Point is not inside a "driftable" medium or outside the drift area.
      // Try terminating the drift line close to the boundary.
      Terminate(x0, t0, x1, t1);
      if (m_debug) std::cout << "    Left the drift region.\n";
      // Add the point to the drift line.
      path.emplace_back(MakePoint(x1, t1));
      break;
    }
    // Check if the particle has crossed a wire.
    std::array<double, 3> xc = x0;
    double rc = 0.;
    if (m_sensor->CrossedWire(x0[0], x0[1], x0[2], x1[0], x1[1], x1[2], xc[0],
                              xc[1], xc[2], false, rc)) {
      if (m_debug) std::cout << "    Hit a wire.\n";
      status = StatusLeftDriftMedium;
      // Adjust the time step.
      double tc = t0 + (t1 - t0) * Dist(x0, xc) / Dist(x0, x1);
      Terminate(x0, t0, xc, tc);
      // Add the point to the drift line.
      path.emplace_back(MakePoint(xc, tc));
      break;
    }
    if (m_sensor->CrossedPlane(x0[0], x0[1], x0[2], x1[0], x1[1], x1[2], xc[0],
                               xc[1], xc[2])) {
      if (m_debug) std::cout << "    Hit a plane.\n";
      status = StatusHitPlane;
      // Adjust the time step.
      double tc = t0 + (t1 - t0) * Dist(x0, xc) / Dist(x0, x1);
      Terminate(x0, t0, xc, tc);
      // Add the point to the drift line.
      path.emplace_back(MakePoint(xc, tc));
      break;
    }

    // Make sure the time is still within the specified interval.
    if (m_hasTimeWindow && (t1 < m_tMin || t1 > m_tMax)) {
      status = StatusOutsideTimeWindow;
    }
    // Add the point to the drift line.
    path.emplace_back(MakePoint(x1, t1));
    // Update the current position and time.
    x0 = x1;
    t0 = t1;
  }

  if (status == StatusCalculationAbandoned) {
    std::cerr << m_className + "::DriftLine: Abandoned the calculation.\n";
  }

  // Compute Townsend and attachment coefficients for each drift step.
  if ((ptype == Particle::Electron || ptype == Particle::Hole) && aval &&
      // TODO
      (m_sizeCut == 0 || m_nElectrons < m_sizeCut)) {
    ComputeGainLoss(ptype, seed.w, path, status, stack, sc);
    if (status == StatusAttached && m_debug) std::cout << "    Attached.\n";
  }

  if (m_debug) {
    std::cout << "    Stopped at "
              << PrintVec({path.back().x, path.back().y, path.back().z}) +
                     ".\n";
  }

  // Compute the induced signal and induced charge if requested.
  double scale = 1.;
  if (ptype == Particle::Electron) {
    scale = -m_scaleE;
  } else if (ptype == Particle::Ion) {
    scale = m_scaleI;
  } else if (ptype == Particle::Hole) {
    scale = m_scaleH;
  } else if (ptype == Particle::NegativeIon) {
    scale = -m_scaleI;
  }
  if (signal) ComputeSignal(scale * seed.w, path);
  if (m_doInducedCharge) ComputeInducedCharge(scale * seed.w, path);

  // Plot the drift line if requested.
  if (m_viewer && !path.empty()) {
    const size_t nP = path.size();
    // Register the new drift line and get its ID.
    const size_t id =
        m_viewer->NewDriftLine(ptype, nP, seed.pt.x, seed.pt.y, seed.pt.z);
    // Set the points along the trajectory.
    for (size_t i = 0; i < nP; ++i) {
      m_viewer->SetDriftLinePoint(id, i, path[i].x, path[i].y, path[i].z);
    }
  }
  return status;
}

bool AvalancheMC::AvalancheElectron(const double x, const double y,
                                    const double z, const double t,
                                    const bool holes, const size_t w) {
  std::vector<Seed> stack;
  stack.emplace_back(MakeSeed(MakePoint(x, y, z, t), Particle::Electron, w));
  return TransportParticles(stack, true, holes, m_useMultiplication);
}

bool AvalancheMC::AvalancheHole(const double x, const double y, const double z,
                                const double t, const bool electrons,
                                const size_t w) {
  std::vector<Seed> stack;
  stack.emplace_back(MakeSeed(MakePoint(x, y, z, t), Particle::Hole, w));
  return TransportParticles(stack, electrons, true, m_useMultiplication);
}

bool AvalancheMC::AvalancheElectronHole(const double x, const double y,
                                        const double z, const double t,
                                        const size_t w) {
  std::vector<Seed> stack;
  stack.emplace_back(MakeSeed(MakePoint(x, y, z, t), Particle::Electron, w));
  stack.emplace_back(MakeSeed(MakePoint(x, y, z, t), Particle::Hole, w));
  return TransportParticles(stack, true, true, m_useMultiplication);
}

void AvalancheMC::AddElectron(const double x, const double y, const double z,
                              const double t, const size_t w) {
  EndPoint p;
  p.status = StatusAlive;
  p.path = {MakePoint(x, y, z, t)};
  p.weight = w;
  m_electrons.push_back(std::move(p));
}

void AvalancheMC::AddHole(const double x, const double y, const double z,
                          const double t, const size_t w) {
  EndPoint p;
  p.status = StatusAlive;
  p.path = {MakePoint(x, y, z, t)};
  p.weight = w;
  m_holes.push_back(std::move(p));
}

void AvalancheMC::AddIon(const double x, const double y, const double z,
                         const double t, const size_t w) {
  EndPoint p;
  p.status = StatusAlive;
  p.path = {MakePoint(x, y, z, t)};
  p.weight = w;
  m_ions.push_back(std::move(p));
}

void AvalancheMC::AddNegativeIon(const double x, const double y, const double z,
                                 const double t, const size_t w) {
  EndPoint p;
  p.status = StatusAlive;
  p.path = {MakePoint(x, y, z, t)};
  p.weight = w;
  m_negativeIons.push_back(std::move(p));
}

bool AvalancheMC::ResumeAvalanche(const bool electrons, const bool holes) {
  std::vector<Seed> stack;
  for (const auto& p : m_electrons) {
    if (p.status == StatusAlive || p.status == StatusOutsideTimeWindow) {
      stack.push_back(MakeSeed(p.path.back(), Particle::Electron, p.weight));
    }
  }
  for (const auto& p : m_holes) {
    if (p.status == StatusAlive || p.status == StatusOutsideTimeWindow) {
      stack.push_back(MakeSeed(p.path.back(), Particle::Hole, p.weight));
    }
  }
  for (const auto& p : m_ions) {
    if (p.status == StatusAlive || p.status == StatusOutsideTimeWindow) {
      stack.push_back(MakeSeed(p.path.back(), Particle::Ion, p.weight));
    }
  }
  for (const auto& p : m_negativeIons) {
    if (p.status == StatusAlive || p.status == StatusOutsideTimeWindow) {
      stack.push_back(MakeSeed(p.path.back(), Particle::NegativeIon, p.weight));
    }
  }
  return TransportParticles(stack, electrons, holes, m_useMultiplication);
}

bool AvalancheMC::TransportParticles(std::vector<Seed>& stack, const bool withE,
                                     const bool withH, const bool aval) {
  // -----------------------------------------------------------------------
  //   DLCMCA - Subroutine that computes a drift line using a Monte-Carlo
  //            technique to take account of diffusion and of avalanche
  //            formation.
  // -----------------------------------------------------------------------

  m_electrons.clear();
  m_holes.clear();
  m_ions.clear();
  m_negativeIons.clear();

  // Make sure the sensor is defined.
  if (!m_sensor) throw Exception("Sensor is not defined");

  // Count the number of particles.
  m_nElectrons = 0;
  m_nHoles = 0;
  m_nIons = 0;
  m_nNegativeIons = 0;

  if (!withH && !withE) {
    std::cerr << m_className + "::TransportParticles: "
              << "Neither electron nor hole/ion component requested.\n";
  }

  const bool signal = m_doSignal && (m_sensor->GetNumberOfElectrodes() > 0);
  std::vector<Seed> secondaries;
  while (!stack.empty()) {
    for (const auto& seed : stack) {
      const Particle ptype = seed.type;
      if (!withE && ptype == Particle::Electron) {
        m_nElectrons += seed.w;
        continue;
      }
      if (!withH && ptype != Particle::Electron) {
        if (ptype == Particle::Hole) {
          m_nHoles += seed.w;
        } else if (ptype == Particle::Ion) {
          m_nIons += seed.w;
        }
        continue;
      }
      std::vector<Point> path;
      const int status = DriftLine(seed, path, secondaries, aval, signal);
      if (path.empty()) continue;
      EndPoint p;
      p.status = status;
      if (m_storeDriftLines) {
        p.path = std::move(path);
      } else {
        p.path = {path.front(), path.back()};
      }
      p.weight = seed.w;
      if (ptype == Particle::Electron) {
        m_electrons.push_back(std::move(p));
        if (status != StatusAttached) m_nElectrons += seed.w;
      } else if (ptype == Particle::Hole) {
        m_holes.push_back(std::move(p));
        if (status != StatusAttached) m_nHoles += seed.w;
      } else if (ptype == Particle::Ion) {
        m_ions.push_back(std::move(p));
        if (status != StatusAttached) m_nIons += seed.w;
      } else if (ptype == Particle::NegativeIon) {
        m_negativeIons.push_back(std::move(p));
        if (status != StatusAttached) m_nNegativeIons += seed.w;
      } else {
        std::cerr << m_className
                  << "::TransportParticles: Unexpected particle type.\n";
      }
    }
    stack.swap(secondaries);
    secondaries.clear();
  }
  return true;
}

int AvalancheMC::GetField(const std::array<double, 3>& x,
                          std::array<double, 3>& e, std::array<double, 3>& b,
                          Medium*& medium) const {
  e.fill(0.);
  b.fill(0.);
  int status = 0;
  // Get the magnetic field.
  m_sensor->MagneticField(x[0], x[1], x[2], b[0], b[1], b[2], status);
  // Get the electric field.
  m_sensor->ElectricField(x[0], x[1], x[2], e[0], e[1], e[2], medium, status);
  // Make sure the point is inside a drift medium.
  if (status != 0 || !medium) return StatusLeftDriftMedium;
  // Make sure the point is inside the drift area.
  if (!m_sensor->IsInArea(x[0], x[1], x[2])) return StatusLeftDriftArea;

  return 0;
}

double AvalancheMC::GetMobility(const Particle ptype, Medium* medium,
                                const std::array<double, 3>& x) const {
  if (m_useMobilityMap) {
    double mu = -1.;
    const auto nComponents = m_sensor->GetNumberOfComponents();
    for (size_t i = 0; i < nComponents; ++i) {
      auto cmp = m_sensor->GetComponent(i);
      if (!cmp->HasMobilityMap()) continue;
      if (ptype == Particle::Electron) {
        if (!cmp->ElectronMobility(x[0], x[1], x[2], mu)) continue;
      } else {
        if (!cmp->HoleMobility(x[0], x[1], x[2], mu)) continue;
      }
      return mu;
    }
  }
  if (ptype == Particle::Electron) {
    return medium->ElectronMobility();
  } else if (ptype == Particle::Hole) {
    return medium->HoleMobility();
  } else if (ptype == Particle::Ion) {
    return medium->IonMobility();
  } else if (ptype == Particle::NegativeIon) {
    return medium->NegativeIonMobility();
  }
  return -1.;
}

bool AvalancheMC::GetVelocity(const Particle ptype, Medium* medium,
                              const std::array<double, 3>& x,
                              const std::array<double, 3>& e,
                              const std::array<double, 3>& b,
                              std::array<double, 3>& v) const {
  v.fill(0.);
  bool ok = false;
  if (m_useVelocityMap && ptype != Particle::Ion &&
      ptype != Particle::NegativeIon) {
    // We assume there is only one component with a velocity map.
    const auto nComponents = m_sensor->GetNumberOfComponents();
    for (size_t i = 0; i < nComponents; ++i) {
      auto cmp = m_sensor->GetComponent(i);
      if (!cmp->HasVelocityMap()) continue;
      if (ptype == Particle::Electron) {
        ok = cmp->ElectronVelocity(x[0], x[1], x[2], v[0], v[1], v[2]);
      } else if (ptype == Particle::Hole) {
        ok = cmp->HoleVelocity(x[0], x[1], x[2], v[0], v[1], v[2]);
      }
      if (!ok) continue;
      // Seems to have worked.
      if (m_debug) {
        std::cout << m_className << "::GetVelocity: Velocity at " << PrintVec(x)
                  << " = " << PrintVec(v) << "\n";
      }
      return true;
    }
  }
  if (ptype == Particle::Electron) {
    ok = medium->ElectronVelocity(e[0], e[1], e[2], b[0], b[1], b[2], v[0],
                                  v[1], v[2]);
  } else if (ptype == Particle::Hole) {
    ok = medium->HoleVelocity(e[0], e[1], e[2], b[0], b[1], b[2], v[0], v[1],
                              v[2]);
  } else if (ptype == Particle::Ion) {
    ok = medium->IonVelocity(e[0], e[1], e[2], b[0], b[1], b[2], v[0], v[1],
                             v[2]);
  } else if (ptype == Particle::NegativeIon) {
    ok = medium->NegativeIonVelocity(e[0], e[1], e[2], b[0], b[1], b[2], v[0],
                                     v[1], v[2]);
  }
  if (!ok) {
    PrintError("GetVelocity", "velocity", ptype, x);
    return false;
  }
  if (m_debug) {
    std::cout << m_className << "::GetVelocity: Velocity at "
              << PrintVec(x)
              //              << " = " << PrintVec(v) << "\n";
              << " = " << v[0] << ", " << v[1] << ", " << v[2] << "\n";
  }
  return true;
}

bool AvalancheMC::GetDiffusion(const Particle ptype, Medium* medium,
                               const std::array<double, 3>& e,
                               const std::array<double, 3>& b, double& dl,
                               double& dt) const {
  dl = 0.;
  dt = 0.;
  bool ok = false;
  if (ptype == Particle::Electron) {
    ok = medium->ElectronDiffusion(e[0], e[1], e[2], b[0], b[1], b[2], dl, dt);
  } else if (ptype == Particle::Hole) {
    ok = medium->HoleDiffusion(e[0], e[1], e[2], b[0], b[1], b[2], dl, dt);
  } else if (ptype == Particle::Ion || ptype == Particle::NegativeIon) {
    ok = medium->IonDiffusion(e[0], e[1], e[2], b[0], b[1], b[2], dl, dt);
  }
  return ok;
}

double AvalancheMC::GetAttachment(const Particle ptype, Medium* medium,
                                  const std::array<double, 3>& x,
                                  const std::array<double, 3>& e,
                                  const std::array<double, 3>& b) const {
  double eta = 0.;
  if (m_useAttachmentMap) {
    const auto nComponents = m_sensor->GetNumberOfComponents();
    for (size_t i = 0; i < nComponents; ++i) {
      auto cmp = m_sensor->GetComponent(i);
      if (!cmp->HasAttachmentMap()) continue;
      if (ptype == Particle::Electron) {
        if (!cmp->ElectronAttachment(x[0], x[1], x[2], eta)) continue;
      } else {
        if (!cmp->HoleAttachment(x[0], x[1], x[2], eta)) continue;
      }
      return eta;
    }
  }
  if (ptype == Particle::Electron) {
    medium->ElectronAttachment(e[0], e[1], e[2], b[0], b[1], b[2], eta);
  } else {
    medium->HoleAttachment(e[0], e[1], e[2], b[0], b[1], b[2], eta);
  }
  return eta;
}

double AvalancheMC::GetIonDensity(const std::array<double, 3>& x) const {
  double rho = 0.;
  if (m_useDensityMap) {
    const auto nComponents = m_sensor->GetNumberOfComponents();
    for (size_t i = 0; i < nComponents; ++i) {
      auto cmp = m_sensor->GetComponent(i);
      if (!cmp->HasIonDensityMap()) continue;
      cmp->IonDensity(x[0], x[1], x[2], rho);
    }
  }
  return rho;
}

double AvalancheMC::GetNegativeIonDensity(
    const std::array<double, 3>& x) const {
  double rho = 0.;
  if (m_useDensityMap) {
    const auto nComponents = m_sensor->GetNumberOfComponents();
    for (size_t i = 0; i < nComponents; ++i) {
      auto cmp = m_sensor->GetComponent(i);
      if (!cmp->HasNegativeIonDensityMap()) continue;
      cmp->NegativeIonDensity(x[0], x[1], x[2], rho);
    }
  }
  return rho;
}

double AvalancheMC::GetTownsend(const Particle ptype, Medium* medium,
                                const std::array<double, 3>& x,
                                const std::array<double, 3>& e,
                                const std::array<double, 3>& b) const {
  double alpha = 0.;
  if (m_useTownsendMap) {
    const auto nComponents = m_sensor->GetNumberOfComponents();
    for (size_t i = 0; i < nComponents; ++i) {
      auto cmp = m_sensor->GetComponent(i);
      if (!cmp->HasTownsendMap()) continue;
      if (ptype == Particle::Electron) {
        if (!cmp->ElectronTownsend(x[0], x[1], x[2], alpha)) continue;
      } else {
        if (!cmp->HoleTownsend(x[0], x[1], x[2], alpha)) continue;
      }
      return alpha;
    }
  }
  if (ptype == Particle::Electron) {
    medium->ElectronTownsend(e[0], e[1], e[2], b[0], b[1], b[2], alpha);
  } else {
    medium->HoleTownsend(e[0], e[1], e[2], b[0], b[1], b[2], alpha);
  }
  return alpha;
}

void AvalancheMC::StepRKF(const Particle ptype, const std::array<double, 3>& x0,
                          const std::array<double, 3>& v0, const double dt,
                          std::array<double, 3>& xf, std::array<double, 3>& vf,
                          int& status) const {
  // Constants appearing in the RKF formulas.
  constexpr double ci0 = 214. / 891.;
  constexpr double ci1 = 1. / 33.;
  constexpr double ci2 = 650. / 891.;
  constexpr double beta10 = 1. / 4.;
  constexpr double beta20 = -189. / 800.;
  constexpr double beta21 = 729. / 800.;

  vf = v0;
  // First probe point.
  for (size_t k = 0; k < 3; ++k) {
    xf[k] = x0[k] + dt * beta10 * v0[k];
  }
  std::array<double, 3> e;
  std::array<double, 3> b;
  Medium* medium = nullptr;
  status = GetField(xf, e, b, medium);
  if (status != 0) return;

  // Get the velocity at the first point.
  std::array<double, 3> v1;
  if (!GetVelocity(ptype, medium, xf, e, b, v1)) {
    status = StatusCalculationAbandoned;
    return;
  }

  // Second point.
  for (size_t k = 0; k < 3; ++k) {
    xf[k] = x0[k] + dt * (beta20 * v0[k] + beta21 * v1[k]);
  }
  status = GetField(xf, e, b, medium);
  if (status != 0) return;

  // Get the velocity at the second point.
  std::array<double, 3> v2;
  if (!GetVelocity(ptype, medium, xf, e, b, v2)) {
    status = StatusCalculationAbandoned;
    return;
  }

  // Compute the mean velocity and endpoint of the step.
  for (size_t k = 0; k < 3; ++k) {
    vf[k] = ci0 * v0[k] + ci1 * v1[k] + ci2 * v2[k];
    xf[k] = x0[k] + dt * vf[k];
  }
}

void AvalancheMC::AddDiffusion(const double step, const double dl,
                               const double dt, std::array<double, 3>& x,
                               const std::array<double, 3>& v) const {
  // Draw a random diffusion direction in the particle frame.
  const auto rt = RndmGaussians(0., dt);
  const std::array<double, 3> d = {step * RndmGaussian(0., dl), step * rt.first,
                                   step * rt.second};
  if (m_debug) {
    std::cout << m_className << "::AddDiffusion: Adding diffusion step "
              << PrintVec(d) << "\n";
  }
  // Compute the rotation angles to align diffusion and drift velocity vectors.
  const double vt = sqrt(v[0] * v[0] + v[1] * v[1]);
  const double phi = vt > Small ? atan2(v[1], v[0]) : 0.;
  const double theta = vt > Small  ? atan2(v[2], vt)
                       : v[2] < 0. ? -HalfPi
                                   : HalfPi;
  const double cphi = cos(phi);
  const double sphi = sin(phi);
  const double ctheta = cos(theta);
  const double stheta = sin(theta);

  x[0] += cphi * ctheta * d[0] - sphi * d[1] - cphi * stheta * d[2];
  x[1] += sphi * ctheta * d[0] + cphi * d[1] - sphi * stheta * d[2];
  x[2] += stheta * d[0] + ctheta * d[2];
}

void AvalancheMC::Terminate(const std::array<double, 3>& x0, const double t0,
                            std::array<double, 3>& x1, double& t1) const {
  double dt = t1 - t0;
  // Calculate the normalised direction vector.
  std::array<double, 3> dx = {x1[0] - x0[0], x1[1] - x0[1], x1[2] - x0[2]};
  double ds = Mag(dx);
  if (ds > 0.) {
    const double scale = 1. / ds;
    for (std::size_t k = 0; k < 3; ++k) dx[k] *= scale;
  }
  x1 = x0;
  t1 = t0;
  while (ds > BoundaryDistance) {
    dt *= 0.5;
    ds *= 0.5;
    std::array<double, 3> xm = x1;
    for (std::size_t k = 0; k < 3; ++k) xm[k] += dx[k] * ds;
    // Check if the mid-point is inside the drift medium and the drift area.
    double ex = 0., ey = 0., ez = 0.;
    int status = 0;
    Medium* medium = nullptr;
    m_sensor->ElectricField(xm[0], xm[1], xm[2], ex, ey, ez, medium, status);
    if (status == 0 && m_sensor->IsInArea(xm[0], xm[1], xm[2])) {
      x1 = xm;
      t1 += dt;
    }
  }
}

bool AvalancheMC::ComputeGainLoss(const Particle ptype, const size_t w,
                                  std::vector<Point>& path, int& status,
                                  std::vector<Seed>& stack,
                                  const bool sc) const {
  std::vector<double> alps;
  std::vector<double> etas;
  // Compute the integrated Townsend and attachment coefficients.
  if (!ComputeAlphaEta(ptype, path, alps, etas)) return false;

  // Opposite-charge particle produced in the avalanche.
  Particle other = Particle::Electron;
  if (ptype == Particle::Electron) {
    other = sc ? Particle::Hole : Particle::Ion;
  }
  const size_t nPoints = path.size();
  // Loop over the drift line.
  for (size_t i = 0; i < nPoints - 1; ++i) {
    // Start with the initial electron (or hole).
    int ne = 1;
    int ni = 0;
    if (etas[i] < Small) {
      ne = RndmYuleFurry(std::exp(alps[i]));
      ni = ne - 1;
    } else {
      // Subdivision of a step.
      constexpr double probth = 0.01;
      // Compute the number of subdivisions.
      const int nDiv = std::max(int((alps[i] + etas[i]) / probth), 1);
      // Compute the probabilities for gain and loss.
      const double p = std::max(alps[i] / nDiv, 0.);
      const double q = std::max(etas[i] / nDiv, 0.);
      // Loop over the subdivisions.
      for (int j = 0; j < nDiv; ++j) {
        if (ne > 100) {
          // Gaussian approximation.
          const auto r = RndmGaussians();
          const int gain = int(ne * p + r.first * sqrt(ne * p * (1. - p)));
          const int loss = int(ne * q + r.second * sqrt(ne * q * (1. - q)));
          ne += gain - loss;
          ni += gain;
        } else {
          // Binomial approximation
          for (int k = ne; k--;) {
            if (RndmUniform() < p) {
              ++ne;
              ++ni;
            }
            if (RndmUniform() < q) --ne;
          }
        }
        // Check if the electron (or hole) has survived.
        if (ne <= 0) {
          status = StatusAttached;
          const double f0 = (j + 0.5) / nDiv;
          const double f1 = 1. - f0;
          path.resize(i + 2);
          path[i + 1].x = f0 * path[i].x + f1 * path[i + 1].x;
          path[i + 1].y = f0 * path[i].y + f1 * path[i + 1].y;
          path[i + 1].z = f0 * path[i].z + f1 * path[i + 1].z;
          path[i + 1].t = f0 * path[i].t + f1 * path[i + 1].t;
          break;
        }
      }
    }
    // Add the new electrons to the table.
    if (ne > 1) {
      for (int j = 0; j < ne - 1; ++j) {
        stack.push_back(MakeSeed(path[i + 1], ptype, w));
      }
    }
    // Add the new holes/ions to the table.
    if (ni > 0) {
      const double n1 = std::expm1(alps[i]);
      const double a1 = n1 > 0. ? 1. / std::log1p(n1) : 0.;
      for (int j = 0; j < ni; ++j) {
        const double f1 = n1 > 0. ? a1 * std::log1p(RndmUniform() * n1) : 0.5;
        const double f0 = 1. - f1;
        Point point;
        point.x = f0 * path[i].x + f1 * path[i + 1].x;
        point.y = f0 * path[i].y + f1 * path[i + 1].y;
        point.z = f0 * path[i].z + f1 * path[i + 1].z;
        point.t = f0 * path[i].t + f1 * path[i + 1].t;
        stack.push_back(MakeSeed(std::move(point), other, w));
      }
    }
    // If trapped, exit the loop over the drift line.
    if (status == StatusAttached) return true;
  }
  return true;
}

bool AvalancheMC::ComputeAlphaEta(const Particle ptype,
                                  std::vector<Point>& path,
                                  std::vector<double>& alps,
                                  std::vector<double>& etas) const {
  // -----------------------------------------------------------------------
  //    DLCEQU - Computes equilibrated alphas and etas.
  // -----------------------------------------------------------------------

  // Loop a first time over the drift line and get alpha at each point.
  size_t nPoints = path.size();
  alps.assign(nPoints, 0.);
  etas.assign(nPoints, 0.);
  for (size_t i = 0; i < nPoints; ++i) {
    const std::array<double, 3> x0 = {path[i].x, path[i].y, path[i].z};
    std::array<double, 3> e0, b0;
    Medium* medium = nullptr;
    if (GetField(x0, e0, b0, medium) != 0) continue;
    alps[i] = GetTownsend(ptype, medium, x0, e0, b0);
  }

  std::vector<Point> pathExt;
  for (size_t i = 0; i < nPoints - 1; ++i) {
    pathExt.push_back(path[i]);
    if (Slope(alps[i], alps[i + 1]) < 0.5) continue;
    const std::array<double, 3> x0 = {path[i].x, path[i].y, path[i].z};
    const std::array<double, 3> x1 = {path[i + 1].x, path[i + 1].y,
                                      path[i + 1].z};
    auto xm = MidPoint(x0, x1);
    std::array<double, 3> em, bm;
    Medium* medium = nullptr;
    if (GetField(xm, em, bm, medium) != 0) continue;
    Point pm;
    pm.x = xm[0];
    pm.y = xm[1];
    pm.z = xm[2];
    pm.t = 0.5 * (path[i].t + path[i + 1].t);
    pathExt.push_back(std::move(pm));
  }
  pathExt.push_back(path.back());
  path.swap(pathExt);

  nPoints = path.size();
  alps.assign(nPoints, 0.);
  etas.assign(nPoints, 0.);
  if (nPoints < 2) return true;

  // Locations and weights for Gaussian integration.
  constexpr size_t nG = 6;
  auto tg = Numerics::GaussLegendreNodes6();
  auto wg = Numerics::GaussLegendreWeights6();

  bool equilibrate = m_doEquilibration;
  // Loop over the drift line.
  for (size_t i = 0; i < nPoints - 1; ++i) {
    const std::array<double, 3> x0 = {path[i].x, path[i].y, path[i].z};
    const std::array<double, 3> x1 = {path[i + 1].x, path[i + 1].y,
                                      path[i + 1].z};
    // Compute the step length.
    const std::array<double, 3> del = {x1[0] - x0[0], x1[1] - x0[1],
                                       x1[2] - x0[2]};
    const double dmag = Mag(del);
    if (dmag < Small) continue;
    const double veff = dmag / (path[i + 1].t - path[i].t);
    // Integrate drift velocity and Townsend and attachment coefficients.
    std::array<double, 3> vd = {0., 0., 0.};
    for (size_t j = 0; j < nG; ++j) {
      const double f = 0.5 * (1. + tg[j]);
      std::array<double, 3> x = x0;
      for (size_t k = 0; k < 3; ++k) x[k] += f * del[k];
      // Get the field.
      std::array<double, 3> e;
      std::array<double, 3> b;
      Medium* medium = nullptr;
      const int status = GetField(x, e, b, medium);
      // Make sure we are in a drift medium.
      if (status != 0) {
        // Check if this point is the last but one.
        if (i < nPoints - 2) {
          std::cerr << m_className << "::ComputeAlphaEta: Got status " << status
                    << " at segment " << j + 1 << "/" << nG << ", drift point "
                    << i + 1 << "/" << nPoints << ".\n";
          return false;
        }
        continue;
      }
      // Get the drift velocity.
      std::array<double, 3> v;
      if (!GetVelocity(ptype, medium, x, e, b, v)) continue;
      for (size_t k = 0; k < 3; ++k) vd[k] += wg[j] * v[k];
      // Get the Townsend coefficient.
      double alpha = GetTownsend(ptype, medium, x, e, b);
      alps[i] += wg[j] * alpha;
      if (!m_useAttachment) continue;
      double eta = GetAttachment(ptype, medium, x, e, b);
      if (eta < 0.) {
        eta = std::abs(eta) / veff;
        equilibrate = false;
      }
      etas[i] += wg[j] * eta;
    }

    // Compute the scaling factor for the projected length.
    double scale = 1.;
    if (equilibrate) {
      const double vdmag = Mag(vd);
      if (vdmag * dmag <= 0.) {
        scale = 0.;
      } else {
        const double dinv = del[0] * vd[0] + del[1] * vd[1] + del[2] * vd[2];
        scale = dinv < 0. ? 0. : dinv / (vdmag * dmag);
      }
    }
    alps[i] *= 0.5 * dmag * scale;
    if (m_useAttachment) etas[i] *= 0.5 * dmag * scale;
  }

  // Skip equilibration if projection has not been requested.
  if (!equilibrate) return true;
  if (!Equilibrate(alps)) {
    if (m_debug) {
      std::cerr << m_className << "::ComputeAlphaEta:\n"
                << "    Unable to even out alpha steps.\n"
                << "    Calculation is probably inaccurate.\n";
    }
    return false;
  }
  if (m_useAttachment) {
    if (!Equilibrate(etas)) {
      if (m_debug) {
        std::cerr << m_className << "::ComputeAlphaEta:\n"
                  << "    Unable to even out eta steps.\n"
                  << "    Calculation is probably inaccurate.\n";
      }
      return false;
    }
  }
  // Seems to have worked.
  return true;
}

bool AvalancheMC::Equilibrate(std::vector<double>& alphas) const {
  const size_t nPoints = alphas.size();
  // Try to equilibrate the returning parts.
  for (size_t i = 0; i < nPoints - 1; ++i) {
    // Skip non-negative points.
    if (alphas[i] >= 0.) continue;
    // Targets for subtracting
    double sub1 = -0.5 * alphas[i];
    double sub2 = sub1;
    bool try1 = false;
    bool try2 = false;
    // Try to subtract half in earlier points.
    for (size_t j = 0; j < i - 1; ++j) {
      if (alphas[i - j] > sub1) {
        alphas[i - j] -= sub1;
        alphas[i] += sub1;
        sub1 = 0.;
        try1 = true;
        break;
      } else if (alphas[i - j] > 0.) {
        alphas[i] += alphas[i - j];
        sub1 -= alphas[i - j];
        alphas[i - j] = 0.;
      }
    }
    // Try to subtract the other half in later points.
    for (size_t j = 0; j < nPoints - i - 1; ++j) {
      if (alphas[i + j] > sub2) {
        alphas[i + j] -= sub2;
        alphas[i] += sub2;
        sub2 = 0.;
        try2 = true;
        break;
      } else if (alphas[i + j] > 0.) {
        alphas[i] += alphas[i + j];
        sub2 -= alphas[i + j];
        alphas[i + j] = 0.;
      }
    }

    // Done if both sides have margin left.
    bool done = false;
    if (try1 && try2) {
      done = true;
    } else if (try1) {
      // Try earlier points again.
      sub1 = -alphas[i];
      for (size_t j = 0; j < i - 1; ++j) {
        if (alphas[i - j] > sub1) {
          alphas[i - j] -= sub1;
          alphas[i] += sub1;
          sub1 = 0.;
          done = true;
          break;
        } else if (alphas[i - j] > 0.) {
          alphas[i] += alphas[i - j];
          sub1 -= alphas[i - j];
          alphas[i - j] = 0.;
        }
      }
    } else if (try2) {
      // Try later points again.
      sub2 = -alphas[i];
      for (size_t j = 0; j < nPoints - i - 1; ++j) {
        if (alphas[i + j] > sub2) {
          alphas[i + j] -= sub2;
          alphas[i] += sub2;
          sub2 = 0.;
          done = true;
          break;
        } else if (alphas[i + j] > 0.) {
          alphas[i] += alphas[i + j];
          sub2 -= alphas[i + j];
          alphas[i + j] = 0.;
        }
      }
    }
    // See whether we succeeded.
    if (!done) return false;
  }
  return true;
}

void AvalancheMC::ComputeSignal(const double q,
                                const std::vector<Point>& path) const {
  const size_t nPoints = path.size();
  if (nPoints < 2) return;

  std::vector<double> ts;
  std::vector<std::array<double, 3> > xs;

  for (const auto& p : path) {
    ts.push_back(p.t);
    xs.push_back({p.x, p.y, p.z});
  }

  if (m_useWeightingPotential) {
    m_sensor->AddSignalWeightingPotential(q, ts, xs);
  } else {
    constexpr bool integrate = false;
    m_sensor->AddSignalWeightingField(q, ts, xs, integrate);
  }
}

void AvalancheMC::ComputeInducedCharge(const double q,
                                       const std::vector<Point>& path) const {
  if (path.size() < 2) return;
  const auto& p0 = path.front();
  const auto& p1 = path.back();
  m_sensor->AddInducedCharge(q, p0.x, p0.y, p0.z, p1.x, p1.y, p1.z);
}

void AvalancheMC::PrintError(const std::string& fcn, const std::string& par,
                             const Particle ptype,
                             const std::array<double, 3>& x) const {
  const std::string ehi = ptype == Particle::Electron ? "electron"
                          : ptype == Particle::Hole   ? "hole"
                                                      : "ion";
  std::cerr << m_className + "::" + fcn + ": Error calculating " + ehi + " "
            << par + " at " + PrintVec(x) << ".\n";
}
}  // namespace Garfield
