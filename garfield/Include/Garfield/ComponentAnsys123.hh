#ifndef G_COMPONENT_ANSYS123_H
#define G_COMPONENT_ANSYS123_H

#include <string>
#include <vector>

#include "Garfield/ComponentFieldMap.hh"

namespace Garfield {

class ComponentGPU;
/// Component for importing and interpolating three-dimensional ANSYS field
/// maps.
class ComponentAnsys123 : public ComponentFieldMap {
 public:
  /// Constructor
  ComponentAnsys123();
  /// Destructor
  ~ComponentAnsys123() = default;

  /** Import a field map.
   * \param elist name of the file containing the list of elements
   * \param nlist name of the file containing the list of nodes
   * \param mplist name of the file containing the list of materials
   * \param prnsol name of the file containing the nodal solutions
   * \param unit length unit
   */
  bool Initialise(const std::string& elist = "ELIST.lis",
                  const std::string& nlist = "NLIST.lis",
                  const std::string& mplist = "MPLIST.lis",
                  const std::string& prnsol = "PRNSOL.lis",
                  const std::string& unit = "cm");

  /// Import weighting potentials.
  bool SetWeightingPotential(const std::string& prnsol,
                             const std::string& label) {
    return SetWeightingField(prnsol, label);
  }
  bool SetWeightingField(const std::string& prnsol, const std::string& label);

  /// Create and initialise GPU Transfer class
  double CreateGPUTransferObject(ComponentGPU*& comp_gpu) override;

 private:
  bool LoadPotentials(const std::string prnsol, std::vector<double>& pot);
};

}  // namespace Garfield
#endif
