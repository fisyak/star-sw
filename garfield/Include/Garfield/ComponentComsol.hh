#ifndef G_COMPONENT_COMSOL_H
#define G_COMPONENT_COMSOL_H

#include <cstddef>
#include <string>
#include <vector>

#include "Garfield/ComponentFieldMap.hh"

namespace Garfield {

/// Component for importing and interpolating Comsol field maps.

class ComponentComsol : public ComponentFieldMap {
 public:
  /// Default constructor.
  ComponentComsol();
  /// Constructor from file names.
  ComponentComsol(const std::string &mesh, const std::string &mplist,
                  const std::string &field, const std::string &unit = "m");
  /// Destructor.
  ~ComponentComsol() = default;

  void SetImportRange(const double xmin, const double xmax, const double ymin,
                      const double ymax, const double zmin, const double zmax) {
    // TODO: Must happen before initialise function
    m_range.set = true;
    m_range.xmin = xmin;
    m_range.ymin = ymin;
    m_range.zmin = zmin;

    m_range.xmax = xmax;
    m_range.ymax = ymax;
    m_range.zmax = zmax;
  }

  /** Import a field map.
   * \param header name of the file containing the list of nodes
   * \param mplist name of the file containing the material properties
   * \param field name of the file containing the potentials at the nodes
   * \param unit length unit
   */
  bool Initialise(const std::string &header = "mesh.mphtxt",
                  const std::string &mplist = "dielectrics.dat",
                  const std::string &field = "field.txt",
                  const std::string &unit = "m");

  /// Import the weighting potential maps.
  bool SetWeightingPotential(const std::string &file, const std::string &label);
  bool SetWeightingField(const std::string &file, const std::string &label) {
    return SetWeightingPotential(file, label);
  }
  /// Import the time-dependent weighting field maps.
  bool SetDynamicWeightingPotential(const std::string &file,
                                    const std::string &label);
  /// Set the time interval of the time-dependent weighting field.
  void SetTimeInterval(const double mint, const double maxt,
                       const double stept);
  /// Get times of time-sliced dynamic weighting field.
  void GetTimeInterval(std::vector<double> &delayedTimes) {
    delayedTimes = m_wdtimes;
  }

  /// Select material that will exclusivaly be imported based on its relative
  /// permitivity
  void SetImportMaterial(const double epsr = 1.) {
    m_materialSelect = true;
    m_epsr = epsr;
  }

#ifdef USEGPU
  /// Create and initialise GPU Transfer class
  double CreateGPUTransferObject(ComponentGPU *&comp_gpu) override;

#endif
 private:
  double m_unit{100.};
  bool m_timeset{false};
  static constexpr double MaxNodeDistance{1.e-8};

  bool m_materialSelect{false};
  double m_epsr{1.};

  bool GetTimeInterval(const std::string &file);

  struct Range {
    bool set{false};

    double xmin{0.};
    double xmax{0.};

    double ymin{0.};
    double ymax{0.};

    double zmin{0.};
    double zmax{0.};
  };

  Range m_range;

  bool CheckInRange(const double x, const double y, const double z) const {
    if (!m_range.set) return true;

    if (x < m_range.xmin || x > m_range.xmax || y < m_range.ymin ||
        y > m_range.ymax || z < m_range.zmin || z > m_range.zmax)
      return false;

    return true;
  }

  bool ElementInRange(const Element &element,
                      const std::vector<Node> &nodes) const {
    if (m_range.set) {
      for (std::size_t i = 0; i < 10; i++) {
        const Node &node = nodes[element.emap[i]];
        if (!CheckInRange(node.x, node.y, node.z)) return false;
      }
    }
    if (m_materialSelect && m_materials[element.matmap].eps != m_epsr)
      return false;
    return true;
  }
  bool LoadPotentials(const std::string &field, std::vector<double> &pot);
};
}  // namespace Garfield

#endif