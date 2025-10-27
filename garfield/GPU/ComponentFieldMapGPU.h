#ifndef G_COMPONENT_FIELD_MAP_GPU_H
#define G_COMPONENT_FIELD_MAP_GPU_H

__device__ void WeightingField(const double x, const double y, const double z,
                               double& wx, double& wy, double& wz,
                               size_t label);

protected:
bool m_is3d{true};

enum class ElementType { Unknown = 0, Serendipity = 5, CurvedTetrahedron = 13 };
ElementType m_elementType{ElementType::CurvedTetrahedron};

// Elements
struct Element {
  // Nodes
  int emap[10]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  // Material
  std::size_t matmap{0};
};

Element* m_elements{nullptr};
int* m_elementIndices{nullptr};
int numElements{0};

bool* m_degenerate{nullptr};

cuda_t** m_bbMin{nullptr};
cuda_t** m_bbMax{nullptr};

cuda_t*** m_w12{nullptr};

// Nodes
struct Node {
  // Coordinates
  double x{0.};
  double y{0.};
  double z{0.};
};

Node* m_nodes{nullptr};
int numNodes{0};

// TODO GPU: m_dwpot not yet implemented
double* m_pot{nullptr};
int m_numpot{0};

// The number of weighting potentials
int m_num_wpots{0};
// The number of entries in each weighting potential
int* m_num_entries_wpot{nullptr};
double** m_wpot{nullptr};

// Materials
struct Material {
  // Permittivity
  double eps{0.};
  // Resistivity
  double ohm{0.};
  bool driftmedium{false};
  MediumGPU* medium{nullptr};
};

Material* m_materials{nullptr};
int numMaterials{0};

double m_mapmin[3]{0., 0., 0.};
double m_mapmax[3]{0., 0., 0.};
double m_mapamin[3]{0., 0., 0.};
double m_mapamax[3]{0., 0., 0.};

/// Compute the electric/weighting field.
__device__ int Field(const double x, const double y, const double z, double& fx,
                     double& fy, double& fz, int& iel, const double* potentials,
                     const int numPotentials) const;

/// Interpolate the field in a curved quadratic tetrahedron.
__device__ static void Field13(const double v[10], const double t[4],
                               double jac[4][4], const double det, double& ex,
                               double& ey, double& ez);

/// Find the element for a point in curved quadratic tetrahedra.
__device__ int FindElement13(const double x, const double y, const double z,
                             double& t1, double& t2, double& t3, double& t4,
                             double jac[4][4], double& det) const;

/// Move (xpos, ypos, zpos) to field map coordinates.
__device__ void MapCoordinates(double& xpos, double& ypos, double& zpos,
                               bool& xmirrored, bool& ymirrored,
                               bool& zmirrored, double& rcoordinate,
                               double& rotation) const;
/// Move (ex, ey, ez) to global coordinates.
__device__ void UnmapFields(double& ex, double& ey, double& ez,
                            const double xpos, const double ypos,
                            const double zpos, const bool xmirrored,
                            const bool ymirrored, const bool zmirrored,
                            const double rcoordinate,
                            const double rotation) const;

protected:
/// Scan for multiple elements that contain a point
bool m_checkMultipleElement{false};

// Tetrahedral tree
bool m_useTetrahedralTree{true};
TetrahedralTreeGPU* m_octree{nullptr};

/// Calculate local coordinates in linear tetrahedra.
__device__ void Coordinates12(const double x, const double y, const double z,
                              double& t1, double& t2, double& t3, double& t4,
                              const double xn[10], const double yn[10],
                              const double zn[10], const double w[4][3]) const;

/// Calculate local coordinates for curved quadratic tetrahedra.
__device__ int Coordinates13(const double x, const double y, const double z,
                             double& t1, double& t2, double& t3, double& t4,
                             double jac[4][4], double& det,

                             const double xn[10], const double yn[10],
                             const double zn[10], cuda_t** w) const;

/// Calculate Jacobian for curved quadratic tetrahedra.
__device__ static void Jacobian13(const double xn[10], const double yn[10],
                                  const double zn[10], const double fourt0,
                                  const double fourt1, const double fourt2,
                                  const double fourt3, double& det,
                                  double jac[4][4]);

#endif