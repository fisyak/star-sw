// clang-format off
#include "TetrahedralTreeGPU.h"
#include "GPUFunctions.h"
#include "Garfield/TetrahedralTree.hh"
// clang-format on

namespace Garfield {

// Determine which octant of the tree would contain 'point'
__device__ int TetrahedralTreeGPU::GetOctantContainingPoint(
    const Vec3& point) const {
  int oct = 0;
  if (point.x() >= m_origin.x()) oct |= 4;
  if (point.y() >= m_origin.y()) oct |= 2;
  if (point.z() >= m_origin.z()) oct |= 1;
  return oct;
}

__device__ bool TetrahedralTreeGPU::IsLeafNode() const {
  // We are a leaf if we have no children. Since we either have none, or
  // all eight, it is sufficient to just check the first.
  return children[0] == nullptr;
}

__device__ void TetrahedralTreeGPU::GetElementsInBlock(
    const Vec3& point, const int*& tet_list_elems, int& num_elems) const {
  const TetrahedralTreeGPU* octreeNode = GetBlockFromPoint(point);

  if (octreeNode) {
    tet_list_elems = octreeNode->elements;
    num_elems = octreeNode->numelements;
    return;
  }

  tet_list_elems = nullptr;
  num_elems = 0;
}

__device__ const TetrahedralTreeGPU* TetrahedralTreeGPU::GetBlockFromPoint(
    const Vec3& point) const {
  if (!(m_min.x() <= point.x() && point.x() <= m_max.x() &&
        m_min.y() <= point.y() && point.y() <= m_max.y() &&
        m_min.z() <= point.z() && point.z() <= m_max.z()))
    return nullptr;

  return GetBlockFromPointHelper(point);
}

__device__ const TetrahedralTreeGPU*
TetrahedralTreeGPU::GetBlockFromPointHelper(const Vec3& point) const {
  // If we're at a leaf node, it means, the point is inside this block
  if (IsLeafNode()) return this;
  // We are at the interior node, so check which child octant contains the
  // point
  int octant = GetOctantContainingPoint(point);
  return children[octant]->GetBlockFromPointHelper(point);
}

double TetrahedralTree::CreateGPUTransferObject(TetrahedralTreeGPU*& tree_gpu) {
  // create main TetrahedralTree GPU class
  checkCudaErrors(cudaMallocManaged(&tree_gpu, sizeof(TetrahedralTreeGPU)));
  double alloc{sizeof(TetrahedralTreeGPU)};

  // copy the elements
  tree_gpu->numelements = elements.size();
  if (elements.size() != 0) {
    alloc += CreateGPUArrayFromVector<int>(elements, tree_gpu->numelements,
                                           tree_gpu->elements);
  } else {
    tree_gpu->elements = nullptr;
  }

  // copy children
  for (int i = 0; i < 8; i++) {
    if (children[i]) {
      alloc += children[i]->CreateGPUTransferObject(tree_gpu->children[i]);
    } else {
      tree_gpu->children[i] = nullptr;
    }
  }

  // copy other vars
  tree_gpu->m_origin = Vec3{m_origin.x(), m_origin.y(), m_origin.z()};
  tree_gpu->m_halfDimension =
      Vec3{m_halfDimension.x(), m_halfDimension.y(), m_halfDimension.z()};
  tree_gpu->m_min = Vec3{m_min.x(), m_min.y(), m_min.z()};
  tree_gpu->m_max = Vec3{m_max.x(), m_max.y(), m_max.z()};

  return alloc;
}
}  // namespace Garfield