#ifndef G_COMPONENT_GPU_H
#define G_COMPONENT_GPU_H

#include <cstdint>

#include "Garfield/Symmetry.hh"
#include "MediumGPU.h"
#include "TetrahedralTreeGPU.h"

namespace Garfield {

class ComponentGPU {
 public:
  __device__ void ElectricField(const cuda_t xin, const cuda_t yin,
                                const cuda_t zin, cuda_t& ex, cuda_t& ey,
                                cuda_t& ez, MediumGPU*& m, int& status);

  /// std::uint64_t has all the symmetries;
  Garfield::Symmetry m_symmetries;
  /// Triangle symmetric octant of imported map (0 < phi < Pi/4 --> octant 1).
  int m_triangleSymmetricOct = 0;
  /// Octants where |x| >= |y|
  const int m_triangleOctRules[4] = {1, 4, 5, 8};
  bool m_outsideCone{false};

// include parts from derived class due to big performance hit from using
// virtual methods
// TODO GPU TN: It isn't clear to me that we actually need (at least) the Ansys
// include - all the code is protected by an ifndef __GPUCOMPILE__, whereas it
// will be defined when these includes are made
// #include "Garfield/ComponentAnsys123.hh"
#include "ComponentFieldMapGPU.h"

  friend class ComponentAnsys123;
  friend class ComponentComsol;
  friend class ComponentElmer;
  friend class ComponentFieldMap;
  friend class Component;

  // enum to mimic polymorphism
  enum class ComponentType {
    Component = 0,
    ComponentFieldMap,
    ComponentAnsys123,
    ComponentComsol,
    ComponentElmer
  };

  ComponentType m_ComponentType{ComponentType::Component};

 protected:
  /// Ready for use?
  bool m_ready{false};
};

}  // namespace Garfield
#endif
