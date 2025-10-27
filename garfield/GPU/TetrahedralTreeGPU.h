#ifndef TETRAHEDRAL_TREE_GPU_H
#define TETRAHEDRAL_TREE_GPU_H

#include <cstddef>

#include "GPUInterface.hh"
#include "Garfield/Vector.hh"

namespace Garfield {

using Vec3 = Vec3Impl<cuda_t>;

class TetrahedralTreeGPU {
 public:
  // Get all tetrahedra linked to a block corresponding to the given point
  __device__ void GetElementsInBlock(const Vec3& point,
                                     const int*& tet_list_elems,
                                     int& num_elems) const;

 private:
  // Physical centre of this tree node.
  Vec3 m_origin;
  // Half the width/height/depth of this tree node.
  Vec3 m_halfDimension;
  // Storing min and max points for convenience
  Vec3 m_min, m_max;

  // The tree has up to eight children and can additionally store
  // a list of mesh nodes and mesh elements.
  // Pointers to child octants.
  TetrahedralTreeGPU* children[8]{nullptr, nullptr, nullptr, nullptr,
                                  nullptr, nullptr, nullptr, nullptr};

  // Children follow a predictable pattern to make accesses simple.
  // Here, - means less than 'origin' in that dimension, + means greater than.
  // child:	0 1 2 3 4 5 6 7
  // x:     - - - - + + + +
  // y:     - - + + - - + +
  // z:     - + - + - + - +

  int* elements{nullptr};
  int numelements{0};

  static const std::size_t BlockCapacity{10};
  // Check if this tree node is a leaf or intermediate node.
  __device__ bool IsLeafNode() const;

  __device__ int GetOctantContainingPoint(const Vec3& point) const;
  // Get a block containing the input point
  __device__ const TetrahedralTreeGPU* GetBlockFromPoint(
      const Vec3& point) const;
  // A helper function used by the function above.
  // Called recursively on the child nodes.
  __device__ const TetrahedralTreeGPU* GetBlockFromPointHelper(
      const Vec3& point) const;

  friend class TetrahedralTree;
};

}  // namespace Garfield
#endif