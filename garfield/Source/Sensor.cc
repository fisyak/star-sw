#include "Garfield/Sensor.hh"

#include <TGraph.h>

#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "Garfield/Component.hh"
#include "Garfield/Exceptions.hh"
#include "Garfield/GarfieldConstants.hh"
#include "Garfield/Numerics.hh"
#include "Garfield/Random.hh"
#include "Garfield/Shaper.hh"
#include "Garfield/ViewBase.hh"
#include "Garfield/ViewSignal.hh"

namespace {

double Interpolate(const std::vector<double> &y, const std::vector<double> &x,
                   const double xx, const std::size_t order) {
  if (xx < x.front() || xx > x.back()) return 0.;
  if (order > 1) {
    return Garfield::Numerics::Divdif(y, x, x.size(), xx, order);
  }
  return Garfield::Numerics::LinearInterpolation(y, x, xx);
}

double Trapezoid2(const std::vector<std::pair<double, double>> &f) {
  const size_t n = f.size();
  if (n < 2) return -1.;
  double sum = 0.;
  const double x0 = f[0].first;
  const double y0 = f[0].second;
  const double x1 = f[1].first;
  const double y1 = f[1].second;
  // Scale the function such that the peak amplitude is unity.
  double ymax = y0;
  for (size_t i = 0; i < n; ++i) {
    if (f[i].second > ymax) ymax = f[i].second;
  }
  if (fabs(ymax) < Garfield::Small) return -1.;
  const double scale = 1. / (ymax * ymax);
  if (n == 2) {
    sum = (x1 - x0) * (y0 * y0 + y1 * y1);
  } else if (n == 3) {
    const double x2 = f[2].first;
    const double y2 = f[2].second;
    sum = (x1 - x0) * y0 * y0 + (x2 - x0) * y1 * y1 + (x2 - x1) * y2 * y2;
  } else {
    sum = (x1 - x0) * y0 * y0 + (f[2].first - x0) * y1 * y1;
    const double xm = f[n - 2].first;
    const double ym = f[n - 2].second;
    const double xn = f[n - 1].first;
    const double yn = f[n - 1].second;
    sum += (xn - f[n - 3].first) * ym * ym + (xn - xm) * yn * yn;
    if (n > 4) {
      for (size_t k = 2; k < n - 2; ++k) {
        const double y = f[k].second;
        sum += (f[k + 1].first - f[k - 1].first) * y * y;
      }
    }
  }
  return 0.5 * sum * scale;
}

}  // namespace

namespace Garfield {

Sensor::Sensor(Component *comp) { AddComponent(comp); }

void Sensor::AddComponent(Component *cmp) {
  if (!cmp) throw Exception("::AddComponent: Null pointer.");
  m_components.push_back(std::make_tuple(cmp, true, true));
}

void Sensor::FillBin(Electrode &electrode, const std::size_t bin,
                     const double signal, const bool electron,
                     const bool delayed) {
  std::lock_guard<std::mutex> guard(m_mutex);
  electrode.signal[bin] += signal;
  if (delayed) electrode.delayedSignal[bin] += signal;
  if (electron) {
    electrode.electronSignal[bin] += signal;
    if (delayed) electrode.delayedElectronSignal[bin] += signal;
  } else {
    electrode.ionSignal[bin] += signal;
    if (delayed) electrode.delayedIonSignal[bin] += signal;
  }
}

void Sensor::ElectricField(const double x, const double y, const double z,
                           double &ex, double &ey, double &ez, double &v,
                           Medium *&medium, int &status) {
  ex = ey = ez = v = 0.;
  status = -10;
  medium = nullptr;
  double fx = 0., fy = 0., fz = 0., p = 0.;
  Medium *med = nullptr;
  int stat = 0;
  // Add up electric field contributions from all components.
  for (const auto &cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    std::get<0>(cmp)->ElectricField(x, y, z, fx, fy, fz, p, med, stat);
    if (status != 0) {
      status = stat;
      medium = med;
    }
    if (stat == 0) {
      ex += fx;
      ey += fy;
      ez += fz;
      v += p;
    }
  }
}

void Sensor::ElectricField(const double x, const double y, const double z,
                           double &ex, double &ey, double &ez, Medium *&medium,
                           int &status) {
  ex = ey = ez = 0.;
  status = -10;
  medium = nullptr;
  double fx = 0., fy = 0., fz = 0.;
  Medium *med = nullptr;
  int stat = 0;
  // Add up electric field contributions from all components.
  for (const auto &cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    std::get<0>(cmp)->ElectricField(x, y, z, fx, fy, fz, med, stat);
    if (status != 0) {
      status = stat;
      medium = med;
    }
    if (stat == 0) {
      ex += fx;
      ey += fy;
      ez += fz;
    }
  }
}

void Sensor::MagneticField(const double x, const double y, const double z,
                           double &bx, double &by, double &bz, int &status) {
  bx = by = bz = 0.;
  double fx = 0., fy = 0., fz = 0.;
  // Add up contributions.
  for (const auto &cmp : m_components) {
    if (!std::get<2>(cmp)) continue;
    std::get<0>(cmp)->MagneticField(x, y, z, fx, fy, fz, status);
    if (status != 0) continue;
    bx += fx;
    by += fy;
    bz += fz;
  }
}

void Sensor::WeightingField(const double x, const double y, const double z,
                            double &wx, double &wy, double &wz,
                            const std::string &label) {
  wx = wy = wz = 0.;
  // Add up field contributions from all components.
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label) {
      double fx = 0., fy = 0., fz = 0.;
      electrode.comp->WeightingField(x, y, z, fx, fy, fz, label);
      wx += fx;
      wy += fy;
      wz += fz;
    }
  }
}

double Sensor::WeightingPotential(const double x, const double y,
                                  const double z, const std::string &label) {
  double v = 0.;
  // Add up contributions from all components.
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label) {
      v += std::max(electrode.comp->WeightingPotential(x, y, z, label), 0.);
    }
  }
  return v;
}

double Sensor::DelayedWeightingPotential(const double x, const double y,
                                         const double z, const double t,
                                         const std::string &label) {
  double v = 0.;
  // Add up contributions from all components.
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label) {
      v += electrode.comp->DelayedWeightingPotential(x, y, z, t, label);
    }
  }
  return v;
}

Medium *Sensor::GetMedium(const double x, const double y, const double z) {
  for (const auto &cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    Medium *medium = std::get<0>(cmp)->GetMedium(x, y, z);
    if (medium) return medium;
  }
  return nullptr;
}

bool Sensor::SetArea(const bool verbose) {
  std::lock_guard<std::mutex> guard(m_mutex);
  if (!GetBoundingBox(m_xMinUser, m_yMinUser, m_zMinUser, m_xMaxUser,
                      m_yMaxUser, m_zMaxUser)) {
    std::cerr << m_className << "::SetArea: Bounding box is not known.\n";
    return false;
  }

  if (verbose || m_debug) {
    std::cout << m_className << "::SetArea:\n"
              << "    " << m_xMinUser << " < x [cm] < " << m_xMaxUser << "\n"
              << "    " << m_yMinUser << " < y [cm] < " << m_yMaxUser << "\n"
              << "    " << m_zMinUser << " < z [cm] < " << m_zMaxUser << "\n";
  }
  if (std::isinf(m_xMinUser) || std::isinf(m_xMaxUser)) {
    std::cerr << m_className << "::SetArea: Warning. Infinite x-range.\n";
  }
  if (std::isinf(m_yMinUser) || std::isinf(m_yMaxUser)) {
    std::cerr << m_className << "::SetArea: Warning. Infinite y-range.\n";
  }
  if (std::isinf(m_zMinUser) || std::isinf(m_zMaxUser)) {
    std::cerr << m_className << "::SetArea: Warning. Infinite z-range.\n";
  }
  m_hasUserArea = true;
  return true;
}

bool Sensor::SetArea(const double xmin, const double ymin, const double zmin,
                     const double xmax, const double ymax, const double zmax) {
  std::lock_guard<std::mutex> guard(m_mutex);
  if (fabs(xmax - xmin) < Small || fabs(ymax - ymin) < Small ||
      fabs(zmax - zmin) < Small) {
    std::cerr << m_className << "::SetArea: Invalid range.\n";
    return false;
  }

  m_xMinUser = std::min(xmin, xmax);
  m_yMinUser = std::min(ymin, ymax);
  m_zMinUser = std::min(zmin, zmax);
  m_xMaxUser = std::max(xmax, xmin);
  m_yMaxUser = std::max(ymax, ymin);
  m_zMaxUser = std::max(zmax, zmin);

  m_hasUserArea = true;
  return true;
}

bool Sensor::GetArea(double &xmin, double &ymin, double &zmin, double &xmax,
                     double &ymax, double &zmax) {
  if (m_hasUserArea) {
    xmin = m_xMinUser;
    ymin = m_yMinUser;
    zmin = m_zMinUser;
    xmax = m_xMaxUser;
    ymax = m_yMaxUser;
    zmax = m_zMaxUser;
    return true;
  }

  // User area bounds are not (yet) defined.
  // Get the bounding box of the sensor.
  if (!SetArea()) return false;

  xmin = m_xMinUser;
  ymin = m_yMinUser;
  zmin = m_zMinUser;
  xmax = m_xMaxUser;
  ymax = m_yMaxUser;
  zmax = m_zMaxUser;

  return true;
}

bool Sensor::IsInArea(const double x, const double y, const double z) {
  if (!m_hasUserArea) {
    if (!SetArea()) {
      std::cerr << m_className << "::IsInArea: User area could not be set.\n";
      return false;
    }
    m_hasUserArea = true;
  }

  if (x >= m_xMinUser && x <= m_xMaxUser && y >= m_yMinUser &&
      y <= m_yMaxUser && z >= m_zMinUser && z <= m_zMaxUser) {
    return true;
  }

  if (m_debug) {
    std::cout << m_className << "::IsInArea: (" << x << ", " << y << ", " << z
              << ") "
              << " is outside.\n";
  }
  return false;
}

bool Sensor::IsInside(const double x, const double y, const double z) {
  double ex = 0., ey = 0., ez = 0.;
  Medium *medium = nullptr;
  int status = 0;
  ElectricField(x, y, z, ex, ey, ez, medium, status);
  if (status != 0 || !medium) return false;

  return true;
}

bool Sensor::CrossedWire(const double x0, const double y0, const double z0,
                         const double x1, const double y1, const double z1,
                         double &xc, double &yc, double &zc, const bool centre,
                         double &rc) {
  for (const auto &cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    if (std::get<0>(cmp)->CrossedWire(x0, y0, z0, x1, y1, z1, xc, yc, zc,
                                      centre, rc)) {
      return true;
    }
  }
  return false;
}

bool Sensor::InTrapRadius(const double q0, const double x0, const double y0,
                          double z0, double &xw, double &yw, double &rw) {
  for (const auto &cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    if (std::get<0>(cmp)->InTrapRadius(q0, x0, y0, z0, xw, yw, rw)) {
      return true;
    }
  }
  return false;
}

bool Sensor::CrossedPlane(const double x0, const double y0, const double z0,
                          const double x1, const double y1, const double z1,
                          double &xc, double &yc, double &zc) {
  for (const auto &cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    if (std::get<0>(cmp)->CrossedPlane(x0, y0, z0, x1, y1, z1, xc, yc, zc)) {
      return true;
    }
  }
  return false;
}

double Sensor::StepSizeHint() {
  double dmin = std::numeric_limits<double>::max();
  for (const auto &cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    const double d = std::get<0>(cmp)->StepSizeHint();
    if (d > 0.) dmin = std::min(dmin, d);
  }
  return dmin < std::numeric_limits<double>::max() ? dmin : -1.;
}

double Sensor::IntegrateFluxLine(const double x0, const double y0,
                                 const double z0, const double x1,
                                 const double y1, const double z1,
                                 const double xp, const double yp,
                                 const double zp, const std::size_t nI,
                                 const int isign) {
  double q = 0.;
  for (const auto &cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    q += std::get<0>(cmp)->IntegrateFluxLine(x0, y0, z0, x1, y1, z1, xp, yp, zp,
                                             nI, isign);
  }
  return q;
}

Component *Sensor::GetComponent(const std::size_t i) {
  if (i >= m_components.size()) {
    std::cerr << m_className << "::GetComponent: Index out of range.\n";
    return nullptr;
  };
  return std::get<0>(m_components[i]);
}

void Sensor::EnableComponent(const std::size_t i, const bool on) {
  if (i >= m_components.size()) {
    std::cerr << m_className << "::EnableComponent: Index out of range.\n";
    return;
  };
  std::get<1>(m_components[i]) = on;
}

void Sensor::EnableMagneticField(const std::size_t i, const bool on) {
  if (i >= m_components.size()) {
    std::cerr << m_className << "::EnableMagneticField: Index out of range.\n";
    return;
  };
  std::get<2>(m_components[i]) = on;
}

bool Sensor::HasMagneticField() const {
  for (const auto &cmp : m_components) {
    if (!std::get<1>(cmp) || !std::get<2>(cmp)) continue;
    if (std::get<0>(cmp)->HasMagneticField()) return true;
  }
  return false;
}

void Sensor::AddElectrode(Component *cmp, const std::string &label) {
  if (!cmp) {
    std::cerr << m_className << "::AddElectrode: Null pointer.\n";
    return;
  }
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label) {
      std::cout << m_className << "::AddElectrode:\n"
                << "    Warning: An electrode with label \"" << label
                << "\" exists already. Weighting fields will be summed up.\n";
      break;
    }
  }

  Electrode electrode;
  electrode.comp = cmp;
  electrode.label = label;
  electrode.signal.assign(m_nTimeBins, 0.);
  electrode.electronSignal.assign(m_nTimeBins, 0.);
  electrode.ionSignal.assign(m_nTimeBins, 0.);
  electrode.delayedSignal.assign(m_nTimeBins, 0.);
  electrode.delayedElectronSignal.assign(m_nTimeBins, 0.);
  electrode.delayedIonSignal.assign(m_nTimeBins, 0.);
  m_electrodes.push_back(std::move(electrode));
  std::cout << m_className << "::AddElectrode:\n"
            << "    Added readout electrode \"" << label << "\".\n"
            << "    All signals are reset.\n";
  ClearSignal();
}

void Sensor::ClearElectrodes() {
  std::lock_guard<std::mutex> guard(m_mutex);
  m_electrodes.clear();
}

void Sensor::Clear() {
  std::lock_guard<std::mutex> guard(m_mutex);
  m_components.clear();
  m_electrodes.clear();
  m_nTimeBins = 200;
  m_tStart = 0.;
  m_tStep = 10.;
  m_nEvents = 0;
  m_hasUserArea = false;
  m_fTransfer = nullptr;
  m_shaper = nullptr;
  m_fTransferTab.clear();
  m_fTransferSq = -1.;
  m_fTransferFFT.clear();
}

bool Sensor::GetVoltageRange(double &vmin, double &vmax) {
  // We don't know the range yet.
  bool set = false;
  // Loop over the components.
  for (const auto &cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    double umin = 0., umax = 0.;
    if (!std::get<0>(cmp)->GetVoltageRange(umin, umax)) continue;
    if (set) {
      vmin = std::min(umin, vmin);
      vmax = std::max(umax, vmax);
    } else {
      vmin = umin;
      vmax = umax;
      set = true;
    }
  }

  // Warn if we still don't know the range.
  if (!set) {
    std::cerr << m_className << "::GetVoltageRange:\n"
              << "    Sensor voltage range not known.\n";
    vmin = vmax = 0.;
    return false;
  }

  if (m_debug) {
    std::cout << m_className << "::GetVoltageRange: " << vmin << " < V < "
              << vmax << ".\n";
  }
  return true;
}

void Sensor::ClearSignal() {
  for (auto &electrode : m_electrodes) {
    electrode.charge = 0.;
    electrode.signal.assign(m_nTimeBins, 0.);
    electrode.delayedSignal.assign(m_nTimeBins, 0.);
    electrode.electronSignal.assign(m_nTimeBins, 0.);
    electrode.ionSignal.assign(m_nTimeBins, 0.);
    electrode.delayedElectronSignal.assign(m_nTimeBins, 0.);
    electrode.delayedIonSignal.assign(m_nTimeBins, 0.);
    electrode.integrated = false;
  }
  m_nEvents = 0;
}

void Sensor::SetDelayedSignalTimes(const std::vector<double> &ts) {
  if (!std::is_sorted(ts.begin(), ts.end())) {
    std::cerr << m_className << "::SetDelayedSignalTimes:\n"
              << "    Times are not in ascending order.\n";
    return;
  }
  m_delayedSignalTimes = ts;
}

void Sensor::AddSignalWeightingPotential(
    const double q, const std::vector<double> &ts,
    const std::vector<std::array<double, 3>> &xs) {
  std::vector<double> qs(ts.size(), 1.);
  AddSignalWeightingPotential(q, ts, xs, qs);
}

void Sensor::AddSignalWeightingPotential(
    const double q, const std::vector<double> &ts,
    const std::vector<std::array<double, 3>> &xs,
    const std::vector<double> &qs) {
  const size_t ns = ts.size();
  if (ns < 2) return;
  if (xs.size() != ns || qs.size() != ns) {
    std::cerr << m_className << "::AddSignalWeightingPotential:\n"
              << "    Mismatch in vector sizes.\n";
    return;
  }
  if (m_debug) std::cout << m_className << "::AddSignalWeightingPotential: ";

  std::vector<int> bins(ns);
  const double invBinSize = 1. / m_tStep;
  for (size_t i = 0; i < ns; ++i) {
    bins[i] = int((ts[i] - m_tStart) * invBinSize);
  }
  std::vector<double> qm(ns - 1);
  for (size_t i = 0; i < ns - 1; ++i) {
    qm[i] = q * 0.5 * (qs[i] + qs[i + 1]);
  }
  const bool electron = q < 0;

  for (auto &electrode : m_electrodes) {
    const std::string &lbl = electrode.label;
    const auto cmp = electrode.comp;
    if (m_debug) std::cout << "  Electrode " << electrode.label << ":\n";
    // Compute the prompt weighting potentials at each point on the drift line.
    std::vector<double> wp(ns, 0.);
    for (size_t i = 0; i < ns; ++i) {
      wp[i] = cmp->WeightingPotential(xs[i][0], xs[i][1], xs[i][2], lbl);
    }
    // Loop over the drift line segments.
    for (size_t i = 0; i < ns - 1; ++i) {
      // Skip segments outside the time window.
      if (bins[i] >= (int)m_nTimeBins || bins[i + 1] < 0) continue;
      if (wp[i] < -0.5 || wp[i + 1] < -0.5) continue;
      // Compute the induced charge.
      const double charge = qm[i] * (wp[i + 1] - wp[i]);
      if (bins[i] == bins[i + 1]) {
        // Segment is confined within one signal bin.
        FillBin(electrode, bins[i], charge, electron, false);
        continue;
      }
      // Segment extends over more than one time bin.
      const double dt = ts[i + 1] - ts[i];
      if (dt < Small) continue;
      const double invdt = 1. / dt;
      double t0 = ts[i];
      double t1 = m_tStart + (bins[i] + 1) * m_tStep;
      for (int j = bins[i]; j <= bins[i + 1]; ++j) {
        const double f = (t1 - t0) * invdt;
        if (j >= 0 && j < (int)m_nTimeBins) {
          FillBin(electrode, j, f * charge, electron, false);
        }
        t0 = t1;
        t1 = std::min(t0 + m_tStep, ts[i + 1]);
      }
    }
  }

  if (m_nEvents <= 0) m_nEvents = 1;

  if (!m_delayedSignal) return;

  // Calculate the signals for each electrode.
  for (auto &electrode : m_electrodes) {
    const std::string &lbl = electrode.label;
    const auto cmp = electrode.comp;
    const auto &dtimes = cmp->DelayedSignalTimes(lbl);
    if (dtimes.empty()) continue;
    const size_t nt = dtimes.size();
    std::vector<double> dwp0(nt, 0.);
    std::vector<double> dwp1(nt, 0.);
    cmp->DelayedWeightingPotentials(xs[0][0], xs[0][1], xs[0][2], lbl, dwp0);
    for (size_t i = 0; i < ns - 1; ++i) {
      cmp->DelayedWeightingPotentials(xs[i + 1][0], xs[i + 1][1], xs[i + 1][2],
                                      lbl, dwp1);
      double tPrev = ts[i];
      int binPrev = bins[i];
      double chargePrev = 0.;
      for (size_t j = 0; j < nt; ++j) {
        const double t = ts[i] + dtimes[j];
        //   if (t < ts[i + 1]) continue;
        const double charge = qm[i] * (dwp1[j] - dwp0[j]);
        const double delta = charge - chargePrev;
        const int bin = int((t - m_tStart) * invBinSize);
        const double dt = t - tPrev;
        if (dt < Small) continue;
        const double invdt = 1. / dt;
        double t0 = tPrev;
        double t1 = m_tStart + (binPrev + 1) * m_tStep;
        for (int k = binPrev; k <= bin; ++k) {
          const double f = (t1 - t0) * invdt;
          if (k >= 0 && k < (int)m_nTimeBins) {
            FillBin(electrode, k, f * delta, electron, true);
          }
          t0 = t1;
          t1 = std::min(t0 + m_tStep, t);
        }
        tPrev = t;
        binPrev = bin;
        chargePrev = charge;
      }
      dwp0.swap(dwp1);
    }
  }
}

void Sensor::AddSignalWeightingField(
    const double q, const std::vector<double> &ts,
    const std::vector<std::array<double, 3>> &xs,
    const bool integrateWeightingField) {
  const size_t ns = ts.size();
  if (ns < 2) return;
  if (xs.size() != ns) {
    std::cerr << m_className << "::AddSignalWeightingField:\n"
              << "    Mismatch in size of time and coordinate vectors.\n";
    return;
  }
  if (m_debug) std::cout << m_className << "::AddSignalWeightingField: ";

  std::vector<int> bins(ns);
  const double invBinSize = 1. / m_tStep;
  for (size_t i = 0; i < ns; ++i) {
    bins[i] = int((ts[i] - m_tStart) * invBinSize);
  }
  const bool electron = q < 0;

  // Compute the average velocity over each step.
  std::vector<std::array<double, 3>> vs(ns - 1);
  for (size_t i = 0; i < ns - 1; ++i) {
    vs[i].fill(0.);
    const double dt = ts[i + 1] - ts[i];
    if (dt < Small) {
      if (m_debug) std::cout << "Time step too small.\n";
      continue;
    }
    const double invdt = 1. / dt;
    vs[i][0] = (xs[i + 1][0] - xs[i][0]) * invdt;
    vs[i][1] = (xs[i + 1][1] - xs[i][1]) * invdt;
    vs[i][2] = (xs[i + 1][2] - xs[i][2]) * invdt;
  }

  // Abscissae and weights for 6-point Gaussian integration
  constexpr size_t nG = 6;
  auto tG = Numerics::GaussLegendreNodes6();
  auto wG = Numerics::GaussLegendreWeights6();
  std::array<double, nG> sG;
  for (size_t i = 0; i < nG; ++i) sG[i] = 0.5 * (1. + tG[i]);

  for (auto &electrode : m_electrodes) {
    const std::string &lbl = electrode.label;
    const auto cmp = electrode.comp;
    if (m_debug) std::cout << "  Electrode " << electrode.label << ":\n";
    for (size_t i = 0; i < ns - 1; ++i) {
      const double dt = ts[i + 1] - ts[i];
      if (dt < Small) continue;
      const double x0 = xs[i][0];
      const double y0 = xs[i][1];
      const double z0 = xs[i][2];
      const double dx = xs[i + 1][0] - x0;
      const double dy = xs[i + 1][1] - y0;
      const double dz = xs[i + 1][2] - z0;
      // Compute the weighting field.
      double wx = 0., wy = 0., wz = 0.;
      if (integrateWeightingField) {
        for (size_t j = 0; j < nG; ++j) {
          const double x = x0 + sG[j] * dx;
          const double y = y0 + sG[j] * dy;
          const double z = z0 + sG[j] * dz;
          double fx = 0., fy = 0., fz = 0.;
          cmp->WeightingField(x, y, z, fx, fy, fz, lbl);
          wx += wG[j] * fx;
          wy += wG[j] * fy;
          wz += wG[j] * fz;
        }
        wx *= 0.5;
        wy *= 0.5;
        wz *= 0.5;
      } else {
        cmp->WeightingField(x0 + 0.5 * dx, y0 + 0.5 * dy, z0 + 0.5 * dz, wx, wy,
                            wz, lbl);
      }
      if (m_debug) {
        std::cout << "    Weighting field: (" << wx << ", " << wy << ", " << wz
                  << ")\n";
      }
      // Calculate the induced current.
      double current = -q * (wx * vs[i][0] + wy * vs[i][1] + wz * vs[i][2]);
      if (bins[i] == bins[i + 1]) {
        // Segment is confined within one signal bin.
        FillBin(electrode, bins[i], current * dt, electron, false);
        continue;
      }
      // Segment extends over more than one time bin.
      double t0 = ts[i];
      double t1 = m_tStart + (bins[i] + 1) * m_tStep;
      for (int j = bins[i]; j <= bins[i + 1]; ++j) {
        if (j >= 0 && j < (int)m_nTimeBins) {
          FillBin(electrode, j, current * (t1 - t0), electron, false);
        }
        t0 = t1;
        t1 = std::min(t0 + m_tStep, ts[i + 1]);
      }
    }
  }

  if (m_nEvents <= 0) m_nEvents = 1;

  if (!m_delayedSignal) return;

  for (auto &electrode : m_electrodes) {
    const std::string &lbl = electrode.label;
    const auto cmp = electrode.comp;
    const auto &dtimes = cmp->DelayedSignalTimes(lbl);
    if (dtimes.empty()) continue;
    const size_t nt = dtimes.size();
    std::vector<double> td(nt, 0.);
    std::vector<double> id(nt, 0.);
    for (size_t i = 0; i < ns - 1; ++i) {
      const double dx = xs[i + 1][0] - xs[i][0];
      const double dy = xs[i + 1][1] - xs[i][1];
      const double dz = xs[i + 1][2] - xs[i][2];
      const double dt = ts[i + 1] - ts[i];
      const double invdt = 1. / dt;
      for (size_t k = 0; k < nt; ++k) {
        td[k] = ts[i] + dtimes[k];
        const double step = std::min(dtimes[k], dt);
        const double scale = step * invdt;
        double sum = 0.;
        for (size_t j = 0; j < 6; ++j) {
          const double t = dtimes[k] - sG[j] * step;
          const double s = sG[j] * scale;
          const double x = xs[i][0] + s * dx;
          const double y = xs[i][1] + s * dy;
          const double z = xs[i][2] + s * dz;
          // Calculate the delayed weighting field.
          double wx = 0., wy = 0., wz = 0.;
          cmp->DelayedWeightingField(x, y, z, t, wx, wy, wz, lbl);
          sum += (wx * vs[i][0] + wy * vs[i][1] + wz * vs[i][2]) * wG[j];
        }
        id[k] = -q * 0.5 * sum * step;
      }
      FillSignal(electrode, q, td, id, m_nAvgDelayedSignal, true);
    }
  }
}

void Sensor::AddSignalWeightingField(
    const double q, const std::vector<double> &ts,
    const std::vector<std::array<double, 3>> &xs,
    const std::vector<std::array<double, 3>> &vs, const std::vector<double> &ns,
    const int navg) {
  // Don't do anything if there are no points on the signal.
  if (ts.size() < 2) return;
  if (ts.size() != xs.size() || ts.size() != vs.size()) {
    std::cerr << m_className
              << "::AddSignalWeightingField: Mismatch in vector size.\n";
    return;
  }
  const bool aval = ns.size() == ts.size();
  const size_t nPoints = ts.size();
  if (m_debug) {
    std::cout << m_className << "::AddSignalWeightingField: Adding a "
              << nPoints << "-vector (charge " << q << ").\n";
  }

  if (m_nEvents <= 0) m_nEvents = 1;
  for (auto &electrode : m_electrodes) {
    const std::string &lbl = electrode.label;
    const auto cmp = electrode.comp;
    std::vector<double> signal(nPoints, 0.);
    for (size_t i = 0; i < nPoints; ++i) {
      // Calculate the weighting field at this point.
      double wx = 0., wy = 0., wz = 0.;
      cmp->WeightingField(xs[i][0], xs[i][1], xs[i][2], wx, wy, wz, lbl);
      // Calculate the induced current at this point.
      signal[i] = -q * (vs[i][0] * wx + vs[i][1] * wy + vs[i][2] * wz);
      if (aval) signal[i] *= ns[i];
    }
    FillSignal(electrode, q, ts, signal, navg);
  }

  if (!m_delayedSignal) return;
  // Locations and weights for 6-point Gaussian integration
  constexpr size_t nG = 6;
  auto tG = Numerics::GaussLegendreNodes6();
  auto wG = Numerics::GaussLegendreWeights6();
  std::array<double, nG> sG;
  for (size_t i = 0; i < nG; ++i) sG[i] = 0.5 * (1. + tG[i]);

  // Calculate the delayed signals for each electrode.
  for (auto &electrode : m_electrodes) {
    const std::string &lbl = electrode.label;
    const auto cmp = electrode.comp;
    const auto &dtimes = cmp->DelayedSignalTimes(lbl);
    if (dtimes.empty()) continue;
    const size_t nt = dtimes.size();
    for (size_t k = 0; k < nPoints - 1; ++k) {
      const double t0 = ts[k];
      const double t1 = ts[k + 1];
      const double dt = t1 - t0;
      if (dt < Small) continue;
      const double invdt = 1. / dt;
      const auto &x0 = xs[k];
      const auto &x1 = xs[k + 1];
      const auto &v = vs[k];
      std::vector<double> td(nt);
      for (size_t i = 0; i < nt; ++i) {
        td[i] = t0 + dtimes[i];
      }
      std::vector<double> id(nt, 0.);
      for (size_t i = 0; i < nt; ++i) {
        // Integrate over the drift line segment.
        const double step = std::min(dtimes[i], dt);
        const double scale = step * invdt;
        const double dx = scale * (x1[0] - x0[0]);
        const double dy = scale * (x1[1] - x0[1]);
        const double dz = scale * (x1[2] - x0[2]);
        double sum = 0.;
        for (size_t j = 0; j < nG; ++j) {
          const double t = dtimes[i] - sG[j] * step;
          const double x = x0[0] + sG[j] * dx;
          const double y = x0[1] + sG[j] * dy;
          const double z = x0[2] + sG[j] * dz;
          // Calculate the delayed weighting field.
          double wx = 0., wy = 0., wz = 0.;
          cmp->DelayedWeightingField(x, y, z, t, wx, wy, wz, lbl);
          sum += (wx * v[0] + wy * v[1] + wz * v[2]) * wG[j];
        }
        id[i] = -q * 0.5 * sum * step;
      }
      FillSignal(electrode, q, td, id, m_nAvgDelayedSignal, true);
    }
  }
}

void Sensor::FillSignal(Electrode &electrode, const double q,
                        const std::vector<double> &ts,
                        const std::vector<double> &is, const int navg,
                        const bool delayed) {
  const bool electron = q < 0.;
  // Interpolation order.
  constexpr std::size_t k = 1;
  for (std::size_t i = 0; i < m_nTimeBins; ++i) {
    const double t0 = m_tStart + i * m_tStep;
    const double t1 = t0 + m_tStep;
    if (ts.front() > t1) continue;
    if (ts.back() < t0) break;
    // Integration over this bin.
    const double tmin = std::max(ts.front(), t0);
    const double tmax = std::min(ts.back(), t1);
    double sum = 0.;
    if (navg <= 0) {
      sum += (tmax - tmin) * Interpolate(is, ts, 0.5 * (tmin + tmax), k);
    } else {
      const double h = 0.5 * (tmax - tmin) / navg;
      for (int j = -navg; j <= navg; ++j) {
        const int jj = j + navg;
        const double t = t0 + jj * h;
        if (t < ts.front() || t > ts.back()) continue;
        if (j == -navg || j == navg) {
          sum += Interpolate(is, ts, t, k);
        } else if (jj == 2 * (jj / 2)) {
          sum += 2 * Interpolate(is, ts, t, k);
        } else {
          sum += 4 * Interpolate(is, ts, t, k);
        }
      }
      sum *= h / 3.;
    }
    // Add the result to the signal.
    FillBin(electrode, i, sum, electron, delayed);
  }
}

void Sensor::AddInducedCharge(const double q, const double x0, const double y0,
                              const double z0, const double x1, const double y1,
                              const double z1) {
  if (m_debug) std::cout << m_className << "::AddInducedCharge:\n";
  for (auto &electrode : m_electrodes) {
    // Calculate the weighting potential at the starting point.
    auto cmp = electrode.comp;
    const double w0 = cmp->WeightingPotential(x0, y0, z0, electrode.label);
    // Calculate the weighting potential at the end point.
    const double w1 = cmp->WeightingPotential(x1, y1, z1, electrode.label);
    if (w0 > -0.5 && w1 > -0.5) {
      electrode.charge += q * (w1 - w0);
    }
    if (m_debug) {
      std::cout << "  Electrode " << electrode.label << ":\n"
                << "    Weighting potential at (" << x0 << ", " << y0 << ", "
                << z0 << "): " << w0 << "\n"
                << "    Weighting potential at (" << x1 << ", " << y1 << ", "
                << z1 << "): " << w1 << "\n"
                << "    Induced charge: " << electrode.charge << "\n";
    }
  }
}

void Sensor::SetTimeWindow(const double tstart, const double tstep,
                           const std::size_t nsteps) {
  m_tStart = tstart;
  if (tstep <= 0.) {
    std::cerr << m_className << "::SetTimeWindow: Start time out of range.\n";
  } else {
    m_tStep = tstep;
  }

  if (nsteps == 0) {
    std::cerr << m_className << "::SetTimeWindow: Invalid number of bins.\n";
  } else {
    m_nTimeBins = nsteps;
  }

  if (m_debug) {
    std::cout << m_className << "::SetTimeWindow: " << m_tStart
              << " < t [ns] < " << m_tStart + m_nTimeBins * m_tStep << "\n"
              << "    Step size: " << m_tStep << " ns\n";
  }

  std::cout << m_className << "::SetTimeWindow: Resetting all signals.\n";
  for (auto &electrode : m_electrodes) {
    electrode.signal.assign(m_nTimeBins, 0.);
    electrode.electronSignal.assign(m_nTimeBins, 0.);
    electrode.ionSignal.assign(m_nTimeBins, 0.);
    electrode.delayedSignal.assign(m_nTimeBins, 0.);
    electrode.delayedElectronSignal.assign(m_nTimeBins, 0.);
    electrode.delayedIonSignal.assign(m_nTimeBins, 0.);
    electrode.integrated = false;
  }
  m_nEvents = 0;
  // Reset the cached FFT of the transfer function
  // because it depends on the number of time bins.
  m_fTransferFFT.clear();
}

double Sensor::GetElectronSignal(const std::string &label,
                                 const std::size_t bin) {
  if (m_nEvents == 0) return 0.;
  if (bin >= m_nTimeBins) return 0.;
  double sig = 0.;
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label) sig += electrode.electronSignal[bin];
  }
  return ElementaryCharge * sig / (m_nEvents * m_tStep);
}

double Sensor::GetIonSignal(const std::string &label, const std::size_t bin) {
  if (m_nEvents == 0) return 0.;
  if (bin >= m_nTimeBins) return 0.;
  double sig = 0.;
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label) sig += electrode.ionSignal[bin];
  }
  return ElementaryCharge * sig / (m_nEvents * m_tStep);
}

double Sensor::GetDelayedElectronSignal(const std::string &label,
                                        const std::size_t bin) {
  if (m_nEvents == 0) return 0.;
  if (bin >= m_nTimeBins) return 0.;
  double sig = 0.;
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label) sig += electrode.delayedElectronSignal[bin];
  }
  return ElementaryCharge * sig / (m_nEvents * m_tStep);
}

double Sensor::GetDelayedIonSignal(const std::string &label,
                                   const std::size_t bin) {
  if (m_nEvents == 0) return 0.;
  if (bin >= m_nTimeBins) return 0.;
  double sig = 0.;
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label) sig += electrode.delayedIonSignal[bin];
  }
  return ElementaryCharge * sig / (m_nEvents * m_tStep);
}

void Sensor::SetSignal(const std::string &label, const std::size_t bin,
                       const double signal) {
  if (bin >= m_nTimeBins) return;
  if (m_nEvents == 0) m_nEvents = 1;
  for (auto &electrode : m_electrodes) {
    if (electrode.label == label) {
      electrode.signal[bin] = m_nEvents * m_tStep * signal / ElementaryCharge;
      break;
    }
  }
}

void Sensor::SetSignal(const std::string &label, const std::vector<double> &ts,
                       const std::vector<double> &is) {
  constexpr double q = -1.;
  constexpr int navg = 0;
  if (m_nEvents == 0) m_nEvents = 1;
  for (auto &electrode : m_electrodes) {
    if (electrode.label == label) {
      FillSignal(electrode, q, ts, is, navg, false);
      break;
    }
  }
}

double Sensor::GetSignal(const std::string &label, const std::size_t bin) {
  if (m_nEvents == 0) return 0.;
  if (bin >= m_nTimeBins) return 0.;
  double sig = 0.;
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label) sig += electrode.signal[bin];
  }
  return ElementaryCharge * sig / (m_nEvents * m_tStep);
}

double Sensor::GetSignal(const std::string &label, const std::size_t bin,
                         const int comp) {
  if (m_nEvents == 0) return 0.;
  if (bin >= m_nTimeBins) return 0.;
  double sig = 0.;
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label) {
      switch (comp) {
        case 1: {
          sig += electrode.signal[bin] - electrode.delayedSignal[bin];
          break;
        }
        case 2: {
          sig += electrode.delayedSignal[bin];
          break;
        }
        default:
          sig += electrode.signal[bin];
      }
    }
  }
  return ElementaryCharge * sig / (m_nEvents * m_tStep);
}

double Sensor::GetPromptSignal(const std::string &label,
                               const std::size_t bin) {
  if (m_nEvents == 0) return 0.;
  if (bin >= m_nTimeBins) return 0.;
  double sig = 0.;
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label)
      sig += electrode.signal[bin] - electrode.delayedSignal[bin];
  }
  return ElementaryCharge * sig / (m_nEvents * m_tStep);
}

double Sensor::GetDelayedSignal(const std::string &label,
                                const std::size_t bin) {
  if (m_nEvents == 0) return 0.;
  if (bin >= m_nTimeBins) return 0.;
  double sig = 0.;
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label) sig += electrode.delayedSignal[bin];
  }
  return ElementaryCharge * sig / (m_nEvents * m_tStep);
}

double Sensor::GetInducedCharge(const std::string &label) {
  if (m_nEvents == 0) return 0.;
  double charge = 0.;
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label) charge += electrode.charge;
  }

  return charge / m_nEvents;
}

void Sensor::SetTransferFunction(std::function<double(double)> f) {
  if (!f) {
    std::cerr << m_className << "::SetTransferFunction: Empty function.\n";
    return;
  }
  m_fTransfer = f;
  m_shaper = nullptr;
  m_fTransferTab.clear();
  m_fTransferSq = -1.;
  m_fTransferFFT.clear();
}

void Sensor::SetTransferFunction(const std::vector<double> &times,
                                 const std::vector<double> &values) {
  if (times.empty() || values.empty()) {
    std::cerr << m_className << "::SetTransferFunction: Empty vector.\n";
    return;
  } else if (times.size() != values.size()) {
    std::cerr << m_className << "::SetTransferFunction:\n"
              << "    Time and value vectors must have same size.\n";
    return;
  }
  const auto n = times.size();
  m_fTransferTab.clear();
  for (std::size_t i = 0; i < n; ++i) {
    m_fTransferTab.emplace_back(std::make_pair(times[i], values[i]));
  }
  std::sort(m_fTransferTab.begin(), m_fTransferTab.end());
  m_fTransfer = nullptr;
  m_shaper = nullptr;
  m_fTransferSq = -1.;
  m_fTransferFFT.clear();
}

void Sensor::SetTransferFunction(Shaper &shaper) {
  m_shaper = &shaper;
  m_fTransfer = nullptr;
  m_fTransferTab.clear();
  m_fTransferSq = -1.;
  m_fTransferFFT.clear();
}

void Sensor::PlotTransferFunction() {
  const std::string name = ViewBase::FindUnusedCanvasName("cTransferFunction");
  std::vector<double> t;
  std::vector<double> f;
  for (std::size_t i = 0; i < m_nTimeBins; ++i) {
    // Positive time part.
    t.push_back(i * m_tStep);
    f.push_back(GetTransferFunction(i * m_tStep));
  }
  if (t.empty()) return;
  double fmin = *std::min_element(f.begin(), f.end());
  double fmax = *std::max_element(f.begin(), f.end());
  double df = fmax - fmin;
  if (fabs(df) < 1.e-6) {
    fmin -= 1.;
    fmax += 1.;
  } else {
    fmax += 0.1 * df;
    if (fmin < 0.) fmin -= 0.1 * df;
  }

  TCanvas *cf = new TCanvas(name.c_str(), "Transfer Function");
  cf->SetGridx();
  cf->SetGridy();
  cf->DrawFrame(0., fmin, m_nTimeBins * m_tStep, fmax,
                ";time [ns]; transfer function");
  TGraph graph;
  graph.SetLineWidth(4);
  graph.SetLineColor(kBlue + 2);
  graph.DrawGraph(t.size(), t.data(), f.data(), "l");
  gPad->Update();
}

double Sensor::InterpolateTransferFunctionTable(const double t) const {
  if (m_fTransferTab.empty()) return 0.;
  // Don't extrapolate beyond the range defined in the table.
  if (t < m_fTransferTab.front().first || t > m_fTransferTab.back().first) {
    return 0.;
  }
  // Find the proper interval in the table.
  const auto begin = m_fTransferTab.cbegin();
  const auto end = m_fTransferTab.cend();
  const auto it1 = std::upper_bound(begin, end, std::make_pair(t, 0.));
  if (it1 == end) return 0.;
  if (it1 == begin) return m_fTransferTab.front().second;
  const auto it0 = std::prev(it1);
  const double t0 = (*it0).first;
  const double t1 = (*it1).first;
  const double f = t0 == t1 ? 0. : (t - t0) / (t1 - t0);
  // Linear interpolation.
  return (*it0).second * (1. - f) + (*it1).second * f;
}

double Sensor::GetTransferFunction(const double t) {
  if (m_fTransfer) {
    return m_fTransfer(t);
  } else if (m_shaper) {
    return m_shaper->Shape(t);
  }
  return InterpolateTransferFunctionTable(t);
}

void Sensor::PrintTransferFunction() {
  std::cout << m_className << "::PrintTransferFunction:\n";
  if (m_fTransfer) {
    std::cout << "    User-defined function.";
  } else if (m_shaper) {
    std::string shaperType = "Unknown";
    if (m_shaper->IsUnipolar()) {
      shaperType = "Unipolar";
    } else if (m_shaper->IsBipolar()) {
      shaperType = "Bipolar";
    }
    std::size_t n = 1;
    double tp = 0.;
    m_shaper->GetParameters(n, tp);
    std::printf("    %s shaper with order %lu and %5.1f ns peaking time.\n",
                shaperType.c_str(), n, tp);
  } else if (!m_fTransferTab.empty()) {
    std::cout << "    Table with " << m_fTransferTab.size() << " entries.\n";
  } else {
    std::cout << "    No transfer function set.\n";
    return;
  }
  std::cout << "      Time [ns]    Transfer function\n";
  const double dt = m_nTimeBins * m_tStep / 10.;
  for (size_t i = 0; i < 10; ++i) {
    const double t = m_tStart + (i + 0.5) * dt;
    const double f = GetTransferFunction(t);
    std::printf("    %10.3f      %10.5f\n", t, f);
  }
}

bool Sensor::ConvoluteSignal(const std::string &label, const bool fft) {
  if (!m_fTransfer && !m_shaper && m_fTransferTab.empty()) {
    std::cerr << m_className << "::ConvoluteSignal: "
              << "Transfer function not set.\n";
    return false;
  }
  if (m_nEvents == 0) {
    std::cerr << m_className << "::ConvoluteSignal: No signals present.\n";
    return false;
  }

  if (fft) return ConvoluteSignalFFT(label);
  std::vector<double> cnvTab;
  MakeTransferFunctionTable(cnvTab);
  // Loop over all electrodes.
  for (auto &electrode : m_electrodes) {
    if (label != electrode.label) continue;
    ConvoluteSignal(electrode, cnvTab);
    return true;
  }
  return false;
}

bool Sensor::ConvoluteSignals(const bool fft) {
  if (!m_fTransfer && !m_shaper && m_fTransferTab.empty()) {
    std::cerr << m_className << "::ConvoluteSignals: "
              << "Transfer function not set.\n";
    return false;
  }
  if (m_nEvents == 0) {
    std::cerr << m_className << "::ConvoluteSignals: No signals present.\n";
    return false;
  }

  if (fft) return ConvoluteSignalFFT();
  std::vector<double> cnvTab;
  MakeTransferFunctionTable(cnvTab);
  // Loop over all electrodes.
  for (auto &electrode : m_electrodes) ConvoluteSignal(electrode, cnvTab);
  return true;
}

void Sensor::MakeTransferFunctionTable(std::vector<double> &cnvTab) {
  // Set the range where the transfer function is valid.
  constexpr double cnvMin = 0.;
  constexpr double cnvMax = 1.e10;

  cnvTab.assign(2 * m_nTimeBins - 1, 0.);
  const std::size_t offset = m_nTimeBins - 1;
  // Evaluate the transfer function.
  for (std::size_t i = 0; i < m_nTimeBins; ++i) {
    // Negative time part.
    double t = (-int(i)) * m_tStep;
    if (t < cnvMin || t > cnvMax) {
      cnvTab[offset - i] = 0.;
    } else {
      cnvTab[offset - i] = GetTransferFunction(t);
    }
    if (i == 0) continue;
    // Positive time part.
    t = i * m_tStep;
    if (t < cnvMin || t > cnvMax) {
      cnvTab[offset + i] = 0.;
    } else {
      cnvTab[offset + i] = GetTransferFunction(t);
    }
  }
}

void Sensor::ConvoluteSignal(Electrode &electrode,
                             const std::vector<double> &tab) {
  // Do the convolution.
  std::vector<double> tmpSignal(m_nTimeBins, 0.);
  std::vector<double> tmpSignalDelayed(m_nTimeBins, 0.);
  const std::size_t offset = m_nTimeBins - 1;
  for (std::size_t j = 0; j < m_nTimeBins; ++j) {
    tmpSignal[j] = tmpSignalDelayed[j] = 0.;
    for (std::size_t k = 0; k < m_nTimeBins; ++k) {
      tmpSignal[j] += m_tStep * tab[offset + j - k] * electrode.signal[k];
      tmpSignalDelayed[j] +=
          m_tStep * tab[offset + j - k] * electrode.delayedSignal[k];
    }
  }
  electrode.signal.swap(tmpSignal);
  electrode.delayedSignal.swap(tmpSignalDelayed);
  electrode.integrated = true;
}

bool Sensor::ConvoluteSignalFFT() {
  // Number of bins must be a power of 2.
  const std::size_t nn = exp2(ceil(log2(m_nTimeBins)));

  if (!m_cacheTransferFunction || m_fTransferFFT.size() != 2 * (nn + 1)) {
    // (Re-)compute the FFT of the transfer function.
    m_fTransferFFT.assign(2 * (nn + 1), 0.);
    for (std::size_t i = 0; i < m_nTimeBins; ++i) {
      m_fTransferFFT[2 * i + 1] = GetTransferFunction(i * m_tStep);
    }
    FFT(m_fTransferFFT, false, nn);
  }

  for (auto &electrode : m_electrodes) {
    ConvoluteSignalFFT(electrode, m_fTransferFFT, nn);
  }
  return true;
}

bool Sensor::ConvoluteSignalFFT(const std::string &label) {
  // Number of bins must be a power of 2.
  const std::size_t nn = exp2(ceil(log2(m_nTimeBins)));

  if (!m_cacheTransferFunction || m_fTransferFFT.size() != 2 * (nn + 1)) {
    // (Re-)compute the FFT of the transfer function.
    m_fTransferFFT.assign(2 * (nn + 1), 0.);
    for (std::size_t i = 0; i < m_nTimeBins; ++i) {
      m_fTransferFFT[2 * i + 1] = GetTransferFunction(i * m_tStep);
    }
    FFT(m_fTransferFFT, false, nn);
  }

  for (auto &electrode : m_electrodes) {
    if (label != electrode.label) continue;
    ConvoluteSignalFFT(electrode, m_fTransferFFT, nn);
    return true;
  }
  return false;
}

void Sensor::ConvoluteSignalFFT(Electrode &electrode,
                                const std::vector<double> &tab,
                                const std::size_t nn) {
  std::vector<double> g(2 * (nn + 1), 0.);
  for (std::size_t i = 0; i < m_nTimeBins; ++i) {
    g[2 * i + 1] = electrode.signal[i];
  }
  FFT(g, false, nn);
  for (std::size_t i = 0; i < nn; ++i) {
    const double fr = tab[2 * i + 1];
    const double fi = tab[2 * i + 2];
    const double gr = g[2 * i + 1];
    const double gi = g[2 * i + 2];
    g[2 * i + 1] = fr * gr - fi * gi;
    g[2 * i + 2] = fr * gi + gr * fi;
  }
  FFT(g, true, nn);
  const double scale = m_tStep / nn;
  for (std::size_t i = 0; i < m_nTimeBins; ++i) {
    electrode.signal[i] = scale * g[2 * i + 1];
  }
  electrode.integrated = true;
}

bool Sensor::IntegrateSignals() {
  if (m_nEvents == 0) {
    std::cerr << m_className << "::IntegrateSignals: No signals present.\n";
    return false;
  }

  for (auto &electrode : m_electrodes) IntegrateSignal(electrode);
  return true;
}

bool Sensor::IntegrateSignal(const std::string &label) {
  if (m_nEvents == 0) {
    std::cerr << m_className << "::IntegrateSignal: No signals present.\n";
    return false;
  }

  for (auto &electrode : m_electrodes) {
    if (label != electrode.label) continue;
    IntegrateSignal(electrode);
    return true;
  }
  std::cerr << m_className << "::IntegrateSignal: Electrode " << label
            << " not found.\n";
  return false;
}

void Sensor::IntegrateSignal(Electrode &electrode) {
  for (std::size_t j = 0; j < m_nTimeBins; ++j) {
    electrode.signal[j] *= m_tStep;
    electrode.electronSignal[j] *= m_tStep;
    electrode.ionSignal[j] *= m_tStep;
    electrode.delayedSignal[j] *= m_tStep;
    if (j > 0) {
      electrode.signal[j] += electrode.signal[j - 1];
      electrode.electronSignal[j] += electrode.electronSignal[j - 1];
      electrode.ionSignal[j] += electrode.ionSignal[j - 1];
      electrode.delayedSignal[j] += electrode.delayedSignal[j - 1];
    }
  }
  electrode.integrated = true;
}

bool Sensor::IsIntegrated(const std::string &label) const {
  for (const auto &electrode : m_electrodes) {
    if (electrode.label == label) return electrode.integrated;
  }
  return false;
}

bool Sensor::DelayAndSubtractFraction(const double td, const double f) {
  const int offset = int(td / m_tStep);
  for (auto &electrode : m_electrodes) {
    std::vector<double> signal1(m_nTimeBins, 0.);
    std::vector<double> signal2(m_nTimeBins, 0.);
    for (std::size_t j = 0; j < m_nTimeBins; ++j) {
      signal2[j] = f * electrode.signal[j];
      const int bin = j - offset;
      if (bin < 0 || bin >= (int)m_nTimeBins) continue;
      signal1[j] = electrode.signal[bin];
    }
    for (std::size_t j = 0; j < m_nTimeBins; ++j) {
      electrode.signal[j] = signal1[j] - signal2[j];
    }
  }
  return true;
}

void Sensor::SetNoiseFunction(double (*f)(double t)) {
  if (!f) {
    std::cerr << m_className << "::SetNoiseFunction: Null pointer.\n";
    return;
  }
  m_fNoise = f;
}

void Sensor::AddNoise(const bool total, const bool electron, const bool ion) {
  if (!m_fNoise) {
    std::cerr << m_className << "::AddNoise: Noise function not set.\n";
    return;
  }
  if (m_nEvents == 0) m_nEvents = 1;

  for (auto &electrode : m_electrodes) {
    double t = m_tStart + 0.5 * m_tStep;
    for (std::size_t j = 0; j < m_nTimeBins; ++j) {
      const double noise = m_fNoise(t);
      if (total) electrode.signal[j] += noise;
      if (electron) electrode.electronSignal[j] += noise;
      if (ion) electrode.ionSignal[j] += noise;
      t += m_tStep;
    }
  }
}

void Sensor::AddWhiteNoise(const std::string &label, const double enc,
                           const bool poisson, const double q0) {
  if (!m_fTransfer && !m_shaper && m_fTransferTab.empty()) {
    std::cerr << m_className << "::AddWhiteNoise: Transfer function not set.\n";
    return;
  }
  if (m_nEvents == 0) m_nEvents = 1;

  const double f2 = TransferFunctionSq();
  if (f2 < 0.) {
    std::cerr << m_className << "::AddWhiteNoise:\n"
              << "  Could not calculate transfer function integral.\n";
    return;
  }

  if (poisson) {
    // Frequency of random delta pulses to model noise.
    const double nu = (enc * enc / (q0 * q0)) / f2;
    // Average number of delta pulses.
    const double avg = nu * m_tStep * m_nTimeBins;
    // Sample the number of pulses.
    for (auto &electrode : m_electrodes) {
      if (label != electrode.label) continue;
      const int nPulses = RndmPoisson(avg);
      for (int j = 0; j < nPulses; ++j) {
        const int bin = static_cast<int>(m_nTimeBins * RndmUniform());
        electrode.signal[bin] += q0;
      }
      const double offset = q0 * nu * m_tStep;
      for (std::size_t j = 0; j < m_nTimeBins; ++j) {
        electrode.signal[j] -= offset;
      }
      break;
    }
  } else {
    // Gaussian approximation.
    const double sigma = enc * sqrt(m_tStep / f2);
    for (auto &electrode : m_electrodes) {
      if (label != electrode.label) continue;
      for (std::size_t j = 0; j < m_nTimeBins; ++j) {
        electrode.signal[j] += RndmGaussian(0., sigma);
      }
      break;
    }
  }
}

void Sensor::AddWhiteNoise(const double enc, const bool poisson,
                           const double q0) {
  if (!m_fTransfer && !m_shaper && m_fTransferTab.empty()) {
    std::cerr << m_className << "::AddWhiteNoise: Transfer function not set.\n";
    return;
  }
  if (m_nEvents == 0) m_nEvents = 1;

  const double f2 = TransferFunctionSq();
  if (f2 < 0.) {
    std::cerr << m_className << "::AddWhiteNoise:\n"
              << "  Could not calculate transfer function integral.\n";
    return;
  }

  if (poisson) {
    // Frequency of random delta pulses to model noise.
    const double nu = (enc * enc / (q0 * q0)) / f2;
    // Average number of delta pulses.
    const double avg = nu * m_tStep * m_nTimeBins;
    // Sample the number of pulses.
    for (auto &electrode : m_electrodes) {
      const int nPulses = RndmPoisson(avg);
      for (int j = 0; j < nPulses; ++j) {
        const int bin = static_cast<int>(m_nTimeBins * RndmUniform());
        electrode.signal[bin] += q0;
      }
      const double offset = q0 * nu * m_tStep;
      for (std::size_t j = 0; j < m_nTimeBins; ++j) {
        electrode.signal[j] -= offset;
      }
    }
  } else {
    // Gaussian approximation.
    const double sigma = enc * sqrt(m_tStep / f2);
    for (auto &electrode : m_electrodes) {
      for (std::size_t j = 0; j < m_nTimeBins; ++j) {
        electrode.signal[j] += RndmGaussian(0., sigma);
      }
    }
  }
}

double Sensor::TransferFunctionSq() {
  if (m_fTransferSq >= 0.) return m_fTransferSq;
  double integral = -1.;
  if (m_fTransfer) {
    std::function<double(double)> fsq = [this](double x) {
      const double y = m_fTransfer(x);
      return y * y;
    };
    constexpr double epsrel = 1.e-8;
    double err = 0.;
    std::size_t stat = 0;
    Numerics::QUADPACK::qagi(fsq, 0., 1, 0., epsrel, integral, err, stat);
    // Find the peak value.
    std::size_t imax = 0;
    double ymax = m_fTransfer(0.);
    for (std::size_t i = 0; i < m_nTimeBins; ++i) {
      const double y = m_fTransfer(m_tStep * (i + 0.5));
      if (y > ymax) {
        ymax = y;
        imax = i;
      }
    }
    double tmax = m_tStep * imax;
    for (std::size_t i = 0; i < 10; ++i) {
      const double y = m_fTransfer(tmax);
      if (y > ymax) ymax = y;
      tmax += 0.1 * m_tStep;
    }
    if (fabs(ymax) > Garfield::Small) {
      const double scale = 1. / (ymax * ymax);
      integral *= scale;
    }
  } else if (m_shaper) {
    integral = m_shaper->TransferFuncSq();
  } else {
    integral = Trapezoid2(m_fTransferTab);
  }
  if (m_cacheTransferFunction) m_fTransferSq = integral;
  return integral;
}

bool Sensor::ComputeThresholdCrossings(const double thr,
                                       const std::string &label, int &n) {
  // Reset the list of threshold crossings.
  m_thresholdCrossings.clear();
  m_thresholdLevel = thr;

  // Set the interpolation order.
  int iOrder = 1;

  if (m_nEvents == 0) {
    std::cerr << m_className << "::ComputeThresholdCrossings: "
              << "No signals present.\n";
    return false;
  }
  // Compute the total signal.
  std::vector<double> signal(m_nTimeBins, 0.);
  // Loop over the electrodes.
  bool foundLabel = false;
  for (const auto &electrode : m_electrodes) {
    if (electrode.label != label) continue;
    foundLabel = true;
    if (!electrode.integrated) {
      std::cerr << m_className << "::ComputeThresholdCrossings:\n    "
                << "Warning: signal on electrode " << label
                << " has not been integrated/convoluted.\n";
    }
    for (std::size_t i = 0; i < m_nTimeBins; ++i) {
      signal[i] += electrode.signal[i];
    }
  }
  if (!foundLabel) {
    std::cerr << m_className << "::ComputeThresholdCrossings: Electrode "
              << label << " not found.\n";
    return false;
  }
  const double scale = ElementaryCharge / (m_nEvents * m_tStep);
  for (std::size_t i = 0; i < m_nTimeBins; ++i) signal[i] *= scale;

  // Establish the range.
  const double vMin = *std::min_element(std::begin(signal), std::end(signal));
  const double vMax = *std::max_element(std::begin(signal), std::end(signal));
  if (m_debug) std::cout << m_className << "::ComputeThresholdCrossings:\n";
  if (thr < vMin && thr > vMax) {
    if (m_debug) {
      std::cout << "    Threshold outside the range [" << vMin << ", " << vMax
                << "]\n";
    }
    return true;
  }

  // Check both rising and falling edges.
  constexpr std::array<int, 2> directions = {1, -1};
  for (const auto dir : directions) {
    const bool up = dir > 0;
    if (m_debug) {
      if (up) {
        std::cout << "  Hunting for rising edges.\n";
      } else {
        std::cout << "  Hunting for falling edges.\n";
      }
    }
    // Initialise the vectors.
    std::vector<double> ts = {m_tStart + 0.5 * m_tStep};
    std::vector<double> vs = {signal[0]};
    // Scan the signal.
    for (std::size_t i = 1; i < m_nTimeBins; ++i) {
      // Compute the vector element.
      const double tNew = m_tStart + (i + 0.5) * m_tStep;
      const double vNew = signal[i];
      // If still increasing or decreasing, add to the vector.
      if ((up && vNew > vs.back()) || (!up && vNew < vs.back())) {
        ts.push_back(tNew);
        vs.push_back(vNew);
        continue;
      }
      // Otherwise see whether we crossed the threshold level.
      if ((vs[0] - thr) * (thr - vs.back()) >= 0. && ts.size() > 1 &&
          ((up && vs.back() > vs[0]) || (!up && vs.back() < vs[0]))) {
        // Compute the crossing time.
        double tcr = Numerics::Divdif(ts, vs, ts.size(), thr, iOrder);
        m_thresholdCrossings.emplace_back(std::make_pair(tcr, up));
        ts = {tNew};
        vs = {vNew};
      } else {
        // No crossing, simply reset the vector.
        ts = {tNew};
        vs = {vNew};
      }
    }
    // Check the final vector.
    if ((vs[0] - thr) * (thr - vs.back()) >= 0. && ts.size() > 1 &&
        ((up && vs.back() > vs[0]) || (!up && vs.back() < vs[0]))) {
      const double tcr = Numerics::Divdif(ts, vs, ts.size(), thr, iOrder);
      m_thresholdCrossings.emplace_back(std::make_pair(tcr, up));
    }
  }
  n = m_thresholdCrossings.size();

  if (m_debug) {
    std::cout << "  Found " << n << " crossings.\n";
    if (n > 0) std::cout << "      Time  [ns]    Direction\n";
    for (const auto &crossing : m_thresholdCrossings) {
      std::cout << "      " << crossing.first << "      ";
      if (crossing.second) {
        std::cout << "rising\n";
      } else {
        std::cout << "falling\n";
      }
    }
  }
  // Seems to have worked.
  return true;
}

bool Sensor::GetThresholdCrossing(const std::size_t i, double &time,
                                  double &level, bool &rise) const {
  level = m_thresholdLevel;

  if (i >= m_thresholdCrossings.size()) {
    std::cerr << m_className << "::GetThresholdCrossing: Index out of range.\n";
    time = m_tStart + m_nTimeBins * m_tStep;
    return false;
  }

  time = m_thresholdCrossings[i].first;
  rise = m_thresholdCrossings[i].second;
  return true;
}

bool Sensor::GetBoundingBox(double &xmin, double &ymin, double &zmin,
                            double &xmax, double &ymax, double &zmax) {
  // We don't know the range yet
  bool set = false;
  // Loop over the fields
  double x0, y0, z0, x1, y1, z1;
  for (const auto &cmp : m_components) {
    if (!std::get<1>(cmp)) continue;
    if (!std::get<0>(cmp)->GetBoundingBox(x0, y0, z0, x1, y1, z1)) continue;
    if (set) {
      if (x0 < xmin) xmin = x0;
      if (y0 < ymin) ymin = y0;
      if (z0 < zmin) zmin = z0;
      if (x1 > xmax) xmax = x1;
      if (y1 > ymax) ymax = y1;
      if (z1 > zmax) zmax = z1;
    } else {
      xmin = x0;
      ymin = y0;
      zmin = z0;
      xmax = x1;
      ymax = y1;
      zmax = z1;
      set = true;
    }
  }

  // Warn if we still don't know the range
  if (!set) {
    std::cerr << m_className << "::GetBoundingBox:\n"
              << "    Sensor bounding box not known.\n";
    xmin = ymin = zmin = 0.;
    xmax = ymax = zmax = 0.;
    return false;
  }

  if (m_debug) {
    std::cout << m_className << "::GetBoundingBox:\n"
              << "    " << xmin << " < x [cm] < " << xmax << "\n"
              << "    " << ymin << " < y [cm] < " << ymax << "\n"
              << "    " << zmin << " < z [cm] < " << zmax << "\n";
  }
  return true;
}

void Sensor::FFT(std::vector<double> &data, const bool inverse, const int nn) {
  // Replaces data[1..2*nn] by its discrete fourier transform
  // or replaces data[1..2*nn] by nn times its inverse discrete
  // fourier transform.
  // nn MUST be an integer power of 2 (this is not checked for!).

  const int n = 2 * nn;
  // Bit reversal.
  int j = 1;
  for (int i = 1; i < n; i += 2) {
    if (j > i) {
      // Exchange the two complex numbers.
      std::swap(data[j], data[i]);
      std::swap(data[j + 1], data[i + 1]);
    }
    int m = nn;
    while (m >= 2 && j > m) {
      j -= m;
      m >>= 1;
    }
    j += m;
  }

  const int isign = inverse ? -1 : 1;
  int mmax = 2;
  while (n > mmax) {
    const int step = 2 * mmax;
    const double theta = isign * TwoPi / mmax;
    double wtemp = sin(0.5 * theta);
    const double wpr = -2. * wtemp * wtemp;
    const double wpi = sin(theta);
    double wr = 1.;
    double wi = 0.;
    for (int m = 1; m < mmax; m += 2) {
      for (int i = m; i <= n; i += step) {
        j = i + mmax;
        double tr = wr * data[j] - wi * data[j + 1];
        double ti = wr * data[j + 1] + wi * data[j];
        data[j] = data[i] - tr;
        data[j + 1] = data[i + 1] - ti;
        data[i] += tr;
        data[i + 1] += ti;
      }
      wr = (wtemp = wr) * wpr - wi * wpi + wr;
      wi = wi * wpr + wtemp * wpi + wi;
    }
    mmax = step;
  }
}

void Sensor::PlotSignal(const std::string &label, TPad *pad,
                        const std::string optTotal, const std::string optPrompt,
                        const std::string optDelayed) {
  ViewSignal view(this);
  if (pad) view.SetCanvas(pad);
  view.PlotSignal(label, optTotal, optPrompt, optDelayed);
}

void Sensor::ExportSignal(const std::string &label, const std::string &name,
                          const bool chargeCarriers) const {
  const double scale = ElementaryCharge / (m_nEvents * m_tStep);
  for (const auto &electrode : m_electrodes) {
    if (electrode.label != label) continue;

    const std::string quantity = electrode.integrated ? "Charge" : "Signal";
    const std::string unit = electrode.integrated ? " [fC]" : " [fC/ns]";
    std::ofstream myfile;
    std::string filename = name + ".csv";
    myfile.open(filename);
    if (!electrode.integrated) {
      myfile << "The cumulative induced charge.\n";
    } else {
      myfile << "The induced signal.\n";
    }
    myfile << "Time [ns]"
           << ",Total Prompt" << unit << ",Total Delayed" << unit << ", Total "
           << quantity << unit;
    if (chargeCarriers) {
      myfile << ",Electron Prompt" << unit << ",Electron Delayed" << unit
             << ",Electron " << quantity << unit << ",Ion Prompt" << unit
             << ",Ion Delayed" << unit << ",Ion " << quantity << unit;
    }
    myfile << "\n";
    myfile << std::setprecision(std::numeric_limits<long double>::digits10 + 1);
    for (std::size_t i = 0; i < m_nTimeBins; i++) {
      myfile << m_tStart + i * m_tStep << ","
             << scale * (electrode.signal[i] - electrode.delayedSignal[i])
             << "," << scale * electrode.delayedSignal[i] << ","
             << scale * electrode.signal[i];
      if (!chargeCarriers) {
        myfile << "\n";
        continue;
      }
      myfile << ","
             << scale * (electrode.electronSignal[i] -
                         electrode.delayedElectronSignal[i])
             << "," << scale * electrode.delayedElectronSignal[i] << ","
             << scale * electrode.electronSignal[i] << ","
             << scale * (electrode.ionSignal[i] - electrode.delayedIonSignal[i])
             << "," << scale * electrode.delayedIonSignal[i] << ","
             << scale * electrode.ionSignal[i] << "\n";
    }
    myfile.close();
    std::cout << m_className << "::ExportSignal: File '" << name
              << ".csv' exported.\n";
  }
}

double Sensor::GetTotalInducedCharge(const std::string &label) {
  for (const auto &electrode : m_electrodes) {
    if (electrode.label != label) continue;
    if (!electrode.integrated || m_nEvents == 0) return 0.;
    return ElementaryCharge * electrode.signal.back() / (m_nEvents * m_tStep);
  }
  return 0.;
}

#ifndef USEGPU
double Sensor::CreateGPUTransferObject(SensorGPU *& /*sensor_gpu*/) {
  return 0;
}
#endif
}  // namespace Garfield
