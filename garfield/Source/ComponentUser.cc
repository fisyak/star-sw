#include "Garfield/ComponentUser.hh"

#include <TInterpreter.h>
#include <TROOT.h>

#include <algorithm>
#include <iostream>
#include <string>

#include "Garfield/Exceptions.hh"
#include "Garfield/Medium.hh"

namespace {

void RemoveSpecialCharacters(std::string& str) {
  str.erase(std::remove_if(
                str.begin(), str.end(),
                [](char c) { return std::isspace(c) || !std::isalnum(c); }),
            str.end());
}

void* MakeFieldFunction(const std::string& fname, const std::string& expression,
                        const bool wfield = false, const bool bfield = false,
                        const bool timeDependent = false) {
  std::string code =
      "std::function<void("
      "const double, const double, const double, ";
  if (timeDependent) code += "const double, ";
  code += "double&, double&, double&)> ";
  code += fname + " = [](const double x, const double y, const double z, ";
  if (timeDependent) code += "const double t, ";
  if (wfield && (expression.find("wx") != std::string::npos ||
                 expression.find("wy") != std::string::npos ||
                 expression.find("wz") != std::string::npos)) {
    code += "double& wx, double& wy, double& wz) {";
    code += "wx = wy = wz = 0.;";
  } else if (bfield) {
    code += "double& bx, double& by, double& bz) {";
    code += "bx = by = bz = 0.;";
  } else {
    code += "double& ex, double& ey, double& ez) {";
    code += "ex = ey = ez = 0.;";
  }
  code += expression + ";};";

  ROOT::GetROOT();
  TInterpreter::EErrorCode ecode;
  gInterpreter->ProcessLine(code.c_str(), &ecode);
  code = fname + ";";
  return (void*)gInterpreter->ProcessLine(code.c_str());
}

void* MakePotentialFunction(const std::string& fname,
                            const std::string& expression,
                            const bool timeDependent = false) {
  std::string code =
      "std::function<double("
      "const double, const double, const double";
  if (timeDependent) code += ", const double";
  code += ")> ";
  code += fname + " = [](const double x, const double y, const double z";
  if (timeDependent) code += ", const double t";
  code += ") {";
  if (expression.find("return") == std::string::npos) code += "return ";
  code += expression + ";};";

  ROOT::GetROOT();
  TInterpreter::EErrorCode ecode;
  gInterpreter->ProcessLine(code.c_str(), &ecode);
  code = fname + ";";
  return (void*)gInterpreter->ProcessLine(code.c_str());
}

}  // namespace

namespace Garfield {

ComponentUser::ComponentUser() : Component("User") {}

void ComponentUser::SetMedium(Medium* medium) {
  if (!medium) throw Exception("medium can't be nullptr");
  m_medium = medium;
}

void ComponentUser::ElectricField(const double x, const double y,
                                  const double z, double& ex, double& ey,
                                  double& ez, Medium*& m, int& status) {
  if (!m_efield) {
    ex = ey = ez = 0.;
    m = nullptr;
    status = -10;
    return;
  }

  m_efield(x, y, z, ex, ey, ez);
  m = GetMedium(x, y, z);
  if (!m) {
    if (m_debug) {
      std::cerr << m_className << "::ElectricField:\n    (" << x << ", " << y
                << ", " << z << ") is not inside a medium.\n";
    }
    status = -6;
    return;
  }

  status = m->IsDriftable() ? 0 : -5;
}

void ComponentUser::ElectricField(const double x, const double y,
                                  const double z, double& ex, double& ey,
                                  double& ez, double& v, Medium*& m,
                                  int& status) {
  if (!m_efield) {
    ex = ey = ez = v = 0.;
    m = nullptr;
    status = -10;
    return;
  }
  m_efield(x, y, z, ex, ey, ez);

  v = m_epot ? m_epot(x, y, z) : 0.;
  m = GetMedium(x, y, z);
  if (!m) {
    if (m_debug) {
      std::cerr << m_className << "::ElectricField:\n    (" << x << ", " << y
                << ", " << z << ") is not inside a medium.\n";
    }
    status = -6;
    return;
  }

  status = m->IsDriftable() ? 0 : -5;
}

bool ComponentUser::GetVoltageRange(double& vmin, double& vmax) {
  vmin = vmax = 0.;
  return false;
}

void ComponentUser::MagneticField(const double x, const double y,
                                  const double z, double& bx, double& by,
                                  double& bz, int& status) {
  if (!m_bfield) {
    Component::MagneticField(x, y, z, bx, by, bz, status);
    return;
  }
  m_bfield(x, y, z, bx, by, bz);
  status = 0;
}

void ComponentUser::WeightingField(const double x, const double y,
                                   const double z, double& wx, double& wy,
                                   double& wz, const std::string& label) {
  wx = wy = wz = 0.;
  if (m_wfield.count(label) > 0) {
    m_wfield[label](x, y, z, wx, wy, wz);
  }
}

double ComponentUser::WeightingPotential(const double x, const double y,
                                         const double z,
                                         const std::string& label) {
  double v = 0.;
  if (m_wpot.count(label) > 0) v = m_wpot[label](x, y, z);
  return v;
}

void ComponentUser::DelayedWeightingField(const double x, const double y,
                                          const double z, const double t,
                                          double& wx, double& wy, double& wz,
                                          const std::string& label) {
  wx = wy = wz = 0.;
  if (m_dwfield.count(label) > 0) {
    m_dwfield[label](x, y, z, t, wx, wy, wz);
  }
}

double ComponentUser::DelayedWeightingPotential(const double x, const double y,
                                                const double z, const double t,
                                                const std::string& label) {
  double v = 0.;
  if (m_dwpot.count(label) > 0) v = m_dwpot[label](x, y, z, t);
  return v;
}

bool ComponentUser::GetBoundingBox(double& xmin, double& ymin, double& zmin,
                                   double& xmax, double& ymax, double& zmax) {
  if (!m_hasArea) {
    return Component::GetBoundingBox(xmin, ymin, zmin, xmax, ymax, zmax);
  }
  xmin = m_xmin[0];
  ymin = m_xmin[1];
  zmin = m_xmin[2];
  xmax = m_xmax[0];
  ymax = m_xmax[1];
  zmax = m_xmax[2];
  return true;
}

bool ComponentUser::HasMagneticField() const {
  return m_bfield ? true : Component::HasMagneticField();
}

void ComponentUser::SetElectricField(
    std::function<void(const double, const double, const double, double&,
                       double&, double&)>
        f) {
  if (!f) {
    std::cerr << m_className << "::SetElectricField: Function is empty.\n";
    return;
  }
  m_efield = f;
  m_ready = true;
}

void ComponentUser::SetElectricField(const std::string& expression) {
  const std::string fname = "fComponentUserEfield";
  auto fPtr = MakeFieldFunction(fname, expression);
  if (!fPtr) {
    std::cerr << m_className << "::SetElectricField: "
              << "Could not convert the expression.\n";
    return;
  }
  typedef std::function<void(const double, const double, const double, double&,
                             double&, double&)>
      Fcn;
  Fcn& f = *((Fcn*)fPtr);
  m_efield = f;
  m_ready = true;
}

void ComponentUser::SetPotential(
    std::function<double(const double, const double, const double)> f) {
  if (!f) {
    std::cerr << m_className << "::SetPotential: Function is empty.\n";
    return;
  }
  m_epot = f;
}

void ComponentUser::SetPotential(const std::string& expression) {
  const std::string fname = "fComponentUserEpot";
  auto fPtr = MakePotentialFunction(fname, expression);
  if (!fPtr) {
    std::cerr << m_className << "::SetPotential: "
              << "Could not convert the expression.\n";
    return;
  }
  typedef std::function<double(const double, const double, const double)> Fcn;
  Fcn& f = *((Fcn*)fPtr);
  m_epot = f;
}

void ComponentUser::SetWeightingField(
    std::function<void(const double, const double, const double, double&,
                       double&, double&)>
        f,
    const std::string& label) {
  if (!f) {
    std::cerr << m_className << "::SetWeightingField: Function is empty.\n";
    return;
  }
  m_wfield[label] = f;
}

void ComponentUser::SetWeightingField(const std::string& expression,
                                      const std::string& label) {
  std::string fname = label;
  RemoveSpecialCharacters(fname);
  fname = "fComponentUserWfield" + fname;
  auto fPtr = MakeFieldFunction(fname, expression, true);
  if (!fPtr) {
    std::cerr << m_className << "::SetWeightingField: "
              << "Could not convert the expression.\n";
    return;
  }
  typedef std::function<void(const double, const double, const double, double&,
                             double&, double&)>
      Fcn;
  Fcn& f = *((Fcn*)fPtr);
  m_wfield[label] = f;
}

void ComponentUser::SetWeightingPotential(
    std::function<double(const double, const double, const double)> f,
    const std::string& label) {
  if (!f) {
    std::cerr << m_className << "::SetWeightingPotential: Function is empty.\n";
    return;
  }
  m_wpot[label] = f;
}

void ComponentUser::SetWeightingPotential(const std::string& expression,
                                          const std::string& label) {
  std::string fname = label;
  RemoveSpecialCharacters(fname);
  fname = "fComponentUserWpot" + fname;
  auto fPtr = MakePotentialFunction(fname, expression);
  if (!fPtr) {
    std::cerr << m_className << "::SetWeightingPotential: "
              << "Could not convert the expression.\n";
    return;
  }
  typedef std::function<double(const double, const double, const double)> Fcn;
  Fcn& f = *((Fcn*)fPtr);
  m_wpot[label] = f;
}

void ComponentUser::SetDelayedSignalTimes(const std::vector<double>& ts) {
  if (!std::is_sorted(ts.begin(), ts.end())) {
    std::cerr << m_className << "::SetDelayedSignalTimes:\n"
              << "    Times are not in ascending order.\n";
    return;
  }
  m_wdtimes = ts;
}

void ComponentUser::SetDelayedWeightingField(
    std::function<void(const double, const double, const double, const double,
                       double&, double&, double&)>
        f,
    const std::string& label) {
  if (!f) {
    std::cerr << m_className << "::SetDelayedWeightingField: "
              << "Function is empty.\n";
    return;
  }
  m_dwfield[label] = f;
}

void ComponentUser::SetDelayedWeightingField(const std::string& expression,
                                             const std::string& label) {
  std::string fname = label;
  RemoveSpecialCharacters(fname);
  fname = "fComponentUserDWfield" + fname;
  auto fPtr = MakeFieldFunction(fname, expression, true, false, true);
  if (!fPtr) {
    std::cerr << m_className << "::SetDelayedWeightingField: "
              << "Could not convert the expression.\n";
    return;
  }
  typedef std::function<void(const double, const double, const double,
                             const double, double&, double&, double&)>
      Fcn;
  Fcn& f = *((Fcn*)fPtr);
  m_dwfield[label] = f;
}

void ComponentUser::SetDelayedWeightingPotential(
    std::function<double(const double, const double, const double,
                         const double)>
        f,
    const std::string& label) {
  if (!f) {
    std::cerr << m_className << "::SetDelayedWeightingPotential: "
              << "Function is empty.\n";
    return;
  }
  m_dwpot[label] = f;
}

void ComponentUser::SetDelayedWeightingPotential(const std::string& expression,
                                                 const std::string& label) {
  std::string fname = label;
  RemoveSpecialCharacters(fname);
  fname = "fComponentUserDWpot" + fname;
  auto fPtr = MakePotentialFunction(fname, expression, true);
  if (!fPtr) {
    std::cerr << m_className << "::SetDelayedWeightingPotential: "
              << "Could not convert the expression.\n";
    return;
  }
  typedef std::function<double(const double, const double, const double,
                               const double)>
      Fcn;
  Fcn& f = *((Fcn*)fPtr);
  m_dwpot[label] = f;
}

void ComponentUser::SetMagneticField(
    std::function<void(const double, const double, const double, double&,
                       double&, double&)>
        f) {
  if (!f) {
    std::cerr << m_className << "::SetMagneticField: Function is empty.\n";
    return;
  }
  m_bfield = f;
}

void ComponentUser::SetMagneticField(const std::string& expression) {
  const std::string fname = "fComponentUserBfield";
  auto fPtr = MakeFieldFunction(fname, expression, false, true);
  if (!fPtr) {
    std::cerr << m_className << "::SetMagneticField: "
              << "Could not convert the expression.\n";
    return;
  }
  typedef std::function<void(const double, const double, const double, double&,
                             double&, double&)>
      Fcn;
  Fcn& f = *((Fcn*)fPtr);
  m_bfield = f;
}

void ComponentUser::SetArea(const double xmin, const double ymin,
                            const double zmin, const double xmax,
                            const double ymax, const double zmax) {
  m_xmin[0] = std::min(xmin, xmax);
  m_xmin[1] = std::min(ymin, ymax);
  m_xmin[2] = std::min(zmin, zmax);
  m_xmax[0] = std::max(xmin, xmax);
  m_xmax[1] = std::max(ymin, ymax);
  m_xmax[2] = std::max(zmin, zmax);
  m_hasArea = true;
}

void ComponentUser::UnsetArea() {
  m_xmin.fill(0.);
  m_xmax.fill(0.);
  m_hasArea = false;
}

void ComponentUser::Reset() {
  m_efield = nullptr;
  m_epot = nullptr;
  m_wfield.clear();
  m_wpot.clear();
  m_dwfield.clear();
  m_dwpot.clear();
  m_bfield = nullptr;
  m_ready = false;
  UnsetArea();
  m_medium = nullptr;
}

void ComponentUser::UpdatePeriodicity() {
  if (m_debug) {
    std::cerr << m_className << "::UpdatePeriodicity:\n"
              << "    Periodicities are not supported.\n";
  }
}
}  // namespace Garfield
