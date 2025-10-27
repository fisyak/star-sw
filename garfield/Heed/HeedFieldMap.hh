#ifndef G_HEED_FIELDMAP_H
#define G_HEED_FIELDMAP_H
#include <limits>

#include "Garfield/Exceptions.hh"
#include "Garfield/Medium.hh"
#include "wcpplib/clhep_units/WSystemOfUnits.h"
#include "wcpplib/geometry/vec.h"
#include "wcpplib/particle/fieldmap.h"

namespace Garfield {

class Sensor;
/// Retrieve electric and magnetic field from Sensor.

class HeedFieldMap : public Heed::fieldmap {
 public:
  HeedFieldMap() = default;
  HeedFieldMap(Sensor* sensor) { SetSensor(sensor); }
  void SetSensor(Sensor* sensor) {
    if (!sensor) throw Exception("Sensor* is nullptr");
    m_sensor = sensor;
  }
  void SetCentre(const double x, const double y, const double z) {
    m_x = x;
    m_y = y;
    m_z = z;
  }
  void UseEfield(const bool flag) { m_useEfield = flag; }
  void UseBfield(const bool flag) { m_useBfield = flag; }

  void evaluate(const Heed::point& pt, Heed::vec& efield, Heed::vec& bfield,
                double& mrange) const override {
    const double x = pt.v.x * conv + m_x;
    const double y = pt.v.y * conv + m_y;
    const double z = pt.v.z * conv + m_z;

    // Initialise the electric and magnetic field.
    efield.x = efield.y = efield.z = 0.;
    bfield.x = bfield.y = bfield.z = 0.;
    mrange = std::numeric_limits<double>::max();

    if (!m_sensor) {
      std::cerr << "HeedFieldMap::evaluate: Sensor not defined.\n";
      return;
    }

    if (m_useEfield) {
      double ex = 0., ey = 0., ez = 0.;
      int status = 0;
      Medium* m = nullptr;
      m_sensor->ElectricField(x, y, z, ex, ey, ez, m, status);
      constexpr double voltpercm = Heed::CLHEP::volt / Heed::CLHEP::cm;
      efield.x = ex * voltpercm;
      efield.y = ey * voltpercm;
      efield.z = ez * voltpercm;
    }

    if (m_useBfield) {
      double bx = 0., by = 0., bz = 0.;
      int status = 0;
      m_sensor->MagneticField(x, y, z, bx, by, bz, status);
      bfield.x = bx * Heed::CLHEP::tesla;
      bfield.y = by * Heed::CLHEP::tesla;
      bfield.z = bz * Heed::CLHEP::tesla;
    }
  }

  bool inside(const Heed::point& pt) const override {
    const double x = pt.v.x * conv + m_x;
    const double y = pt.v.y * conv + m_y;
    const double z = pt.v.z * conv + m_z;
    // Check if the point is inside the drift area.
    if (!m_sensor->IsInArea(x, y, z)) return false;
    // Check if the point is inside a medium.
    auto medium = m_sensor->GetMedium(x, y, z);
    return medium ? medium->IsIonisable() : false;
  }

 private:
  /// Conversion factor from mm to cm.
  static constexpr double conv = 1. / Heed::CLHEP::cm;

  // Centre of the geometry.
  double m_x = 0.;
  double m_y = 0.;
  double m_z = 0.;

  Sensor* m_sensor = nullptr;
  bool m_useEfield = false;
  bool m_useBfield = false;
};
}  // namespace Garfield

#endif
