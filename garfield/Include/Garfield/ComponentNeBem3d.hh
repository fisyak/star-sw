#ifndef G_COMPONENT_NEBEM_3D_H
#define G_COMPONENT_NEBEM_3D_H

#include <array>
#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "Garfield/Component.hh"
#include "Garfield/Solid.hh"

namespace Garfield {

class Medium;
/// Interface to neBEM.

class ComponentNeBem3d : public Component {
 public:
  /// Constructor
  ComponentNeBem3d();
  /// Destructor
  ~ComponentNeBem3d() = default;

  Medium* GetMedium(const double x, const double y, const double z) override;

  /// Add a plane at constant x.
  void AddPlaneX(const double x, const double voltage);
  /// Add a plane at constant y.
  void AddPlaneY(const double y, const double voltage);
  /// Add a plane at constant z.
  void AddPlaneZ(const double z, const double voltage);
  /// Get the number of equipotential planes at constant x.
  std::size_t GetNumberOfPlanesX() const;
  /// Get the number of equipotential planes at constant y.
  std::size_t GetNumberOfPlanesY() const;
  /// Get the number of equipotential planes at constant z.
  std::size_t GetNumberOfPlanesZ() const;
  /// Retrieve the parameters of a plane at constant x.
  bool GetPlaneX(const std::size_t i, double& x, double& v) const;
  /// Retrieve the parameters of a plane at constant y.
  bool GetPlaneY(const std::size_t i, double& y, double& v) const;
  /// Retrieve the parameters of a plane at constant z.
  bool GetPlaneZ(const std::size_t i, double& z, double& v) const;

  std::size_t GetNumberOfPrimitives() const { return m_primitives.size(); }
  bool GetPrimitive(const std::size_t i, double& a, double& b, double& c,
                    std::vector<double>& xv, std::vector<double>& yv,
                    std::vector<double>& zv, int& interface, double& v,
                    double& q, double& lambda) const;
  bool GetPrimitive(const std::size_t i, double& a, double& b, double& c,
                    std::vector<double>& xv, std::vector<double>& yv,
                    std::vector<double>& zv, int& vol1, int& vol2) const;
  bool GetVolume(const std::size_t vol, int& shape, int& material, double& eps,
                 double& potential, double& charge, int& bc);
  int GetVolume(const double x, const double y, const double z);

  std::size_t GetNumberOfElements() const override { return m_elements.size(); }
  bool GetElement(const std::size_t i, std::vector<double>& xv,
                  std::vector<double>& yv, std::vector<double>& zv,
                  int& interface, double& bc, double& lambda) const;

  /// Retrieve surface panels, remove contacts and cut polygons to rectangles
  /// and right-angle triangles.
  bool Initialise();

  /// Set the default value of the target linear size of the elements
  /// produced by neBEM's discretisation process.
  void SetTargetElementSize(const double length);
  /// Set the smallest and largest allowed number of elements along
  /// the lenght of a primitive.
  void SetMinMaxNumberOfElements(const std::size_t nmin,
                                 const std::size_t nmax);

  void SetNewModel(const std::size_t NewModel);
  void SetNewMesh(const std::size_t NewMesh);
  void SetNewBC(const std::size_t NewBC);
  void SetNewPP(const std::size_t NewPP);
  void SetModelOptions(const std::size_t NewModel, const std::size_t NewMesh,
                       const std::size_t NewBC, const std::size_t NewPP);

  /// Set storing options (OptStoreInflMatrix, OptStoreInvMatrix,
  /// OptStoreInvMatrix, OptStoreInvMatrix)
  /// OptStorePrimitives, OptStorePrimitives)
  /// OptStoreElements, OptStoreElements)
  /// OptFormattedFile, OptUnformattedFile)
  void SetStoreInflMatrix(const std::size_t OptStoreInflMatrix);
  void SetReadInflMatrix(const std::size_t OptReadInflMatrix);
  void SetStoreInvMatrix(const std::size_t OptStoreInvMatrix);
  void SetReadInvMatrix(const std::size_t OptReadInvMatrix);
  void SetStorePrimitives(const std::size_t OptStorePrimitives);
  void SetReadPrimitives(const std::size_t OptReadPrimitives);
  void SetStoreElements(const std::size_t OptStoreElements);
  void SetReadElements(const std::size_t OptReadElements);
  void SetFormattedFile(const std::size_t OptFormattedFile);
  void SetUnformattedFile(const std::size_t OptUnformattedFile);
  void SetStoreReadOptions(
      const std::size_t OptStoreInflMatrix, const std::size_t OptReadInflMatrix,
      const std::size_t OptStoreInvMatrix, const std::size_t OptReadInvMatrix,
      const std::size_t OptStorePrimitives, const std::size_t OptReadPrimitives,
      const std::size_t OptStoreElements, const std::size_t OptReadElements,
      const std::size_t OptFormattedFile, const std::size_t OptUnformattedFile);

  // Set whether an older model is to be re-used. Expects an inverted matrix
  // stored during an earlier computation that had identical model and mesh.
  // This execution considers only a change in the boundary conditions.
  void SetReuseModel(void);

  /// Other functions to be, are
  /// void SetPlotOptions(OptGnuplot=0, OptGnuplotPrimitives=0,
  /// OptGnuplotElements=0,
  /// OptPrimitiveFiles=0, OptElementFiles=0)

  // Functions that set computation details and constraints
  void SetSystemChargeZero(const std::size_t OptSystemChargeZero);
  void SetValidateSolution(const std::size_t OptValidateSolution);
  void SetForceValidation(const std::size_t OptForceValidation);
  void SetRepeatLHMatrix(const std::size_t OptRepeatLHMatrix);
  void SetComputeOptions(const std::size_t OptSystemChargeZero,
                         const std::size_t OptValidateSolution,
                         const std::size_t OptForceValidation,
                         const std::size_t OptRepeatLHMatrix);

  // Fast volume related information (physical potential and fields)
  void SetFastVolOptions(const std::size_t OptFastVol,
                         const std::size_t OptCreateFastPF,
                         const std::size_t OptReadFastPF);
  void SetFastVolVersion(const std::size_t VersionFV);
  void SetFastVolBlocks(const std::size_t NbBlocksFV);

  // Needs to include IdWtField information for each of these WtFld functions
  // Weighting potential and field related Fast volume information
  void SetWtFldFastVolOptions(const std::size_t IdWtField,
                              const std::size_t OptWtFldFastVol,
                              const std::size_t OptCreateWtFldFastPF,
                              const std::size_t OptReadWtFldFastPF);
  void SetWtFldFastVolVersion(const std::size_t IdWtField,
                              const std::size_t VersionWtFldFV);
  void SetWtFldFastVolBlocks(const std::size_t IdWtField,
                             const std::size_t NbBlocksWtFldFV);

  // Known charge options
  void SetKnownChargeOptions(const std::size_t OptKnownCharge);

  // Charging up options
  void SetChargingUpOptions(const std::size_t OptChargingUp);

  /// Invert the influence matrix using lower-upper (LU) decomposition.
  void UseLUInversion() { m_inversion = Inversion::LU; }
  /// Invert the influence matrix using singular value decomposition.
  void UseSVDInversion() { m_inversion = Inversion::SVD; }

  /// Set the parameters \f$n_x, n_y, n_z\f$ defining the number of periodic
  /// copies that neBEM will use when dealing with periodic configurations.
  /// neBEM will use \f$2 \times n + 1\f$ copies (default: \f$n = 5\f$).
  void SetPeriodicCopies(const std::size_t nx, const std::size_t ny,
                         const std::size_t nz);
  /// Retrieve the number of periodic copies used by neBEM.
  void GetPeriodicCopies(std::size_t& nx, std::size_t& ny,
                         std::size_t& nz) const {
    nx = m_nCopiesX;
    ny = m_nCopiesY;
    nz = m_nCopiesZ;
  }
  /// Set the periodic length [cm] in the x-direction.
  void SetPeriodicityX(const double s);
  /// Set the periodic length [cm] in the y-direction.
  void SetPeriodicityY(const double s);
  /// Set the periodic length [cm] in the z-direction.
  void SetPeriodicityZ(const double s);
  /// Set the periodic length [cm] in the x-direction.
  void SetMirrorPeriodicityX(const double s);
  /// Set the periodic length [cm] in the y-direction.
  void SetMirrorPeriodicityY(const double s);
  /// Set the periodic length [cm] in the z-direction.
  void SetMirrorPeriodicityZ(const double s);
  /// Get the periodic length in the x-direction.
  bool GetPeriodicityX(double& s) const;
  /// Get the periodic length in the y-direction.
  bool GetPeriodicityY(double& s) const;
  /// Get the periodic length in the z-direction.
  bool GetPeriodicityZ(double& s) const;

  /// Set the number of threads to be used by neBEM.
  void SetNumberOfThreads(const std::size_t n) { m_nThreads = n > 0 ? n : 1; }

  /// Set the number of repetitions after which primitive properties are used
  /// for the physical field.
  /// A negative value (default) implies all the elements are always evaluated.
  void SetPrimAfter(const int n) { m_primAfter = n; }

  /// Set the number of repetitions after which primitive properties are used
  /// for the weighting field.
  /// A negative value (default) implies all the elements are always evaluated.
  void SetWtFldPrimAfter(const int n) { m_wtFldPrimAfter = n; }

  /// Set option related to removal of primitives.
  void SetOptRmPrim(const std::size_t n) { m_optRmPrim = n; }

  void ElectricField(const double x, const double y, const double z, double& ex,
                     double& ey, double& ez, Medium*& m, int& status) override;
  void ElectricField(const double x, const double y, const double z, double& ex,
                     double& ey, double& ez, double& v, Medium*& m,
                     int& status) override;
  using Component::ElectricField;
  bool GetVoltageRange(double& vmin, double& vmax) override;

  void WeightingField(const double x, const double y, const double z,
                      double& wx, double& wy, double& wz,
                      const std::string& label) override;
  double WeightingPotential(const double x, const double y, const double z,
                            const std::string& label) override;

 protected:
  void Reset() override;
  void UpdatePeriodicity() override;

 private:
  struct Primitive {
    /// Perpendicular vector
    double a{0.};
    double b{0.};
    double c{0.};
    /// X-coordinates of vertices
    std::vector<double> xv;
    /// Y-coordinates of vertices
    std::vector<double> yv;
    /// Z-coordinates of vertices
    std::vector<double> zv;
    /// Interface type.
    int interface{0};
    /// Potential
    double v{0.};
    /// Charge
    double q{0.};
    /// Ratio of dielectric constants
    double lambda{0.};
    /// Target element size.
    double elementSize{0.};
    /// Volumes.
    int vol1{0};
    int vol2{0};
  };
  /// List of primitives.
  std::vector<Primitive> m_primitives;

  struct Element {
    /// Local origin.
    std::array<double, 3> origin;
    double lx{0.};
    double lz{0.};
    /// Area.
    double dA{0.};
    /// Direction cosines.
    std::array<std::array<double, 3>, 3> dcos;
    /// X-coordinates of vertices
    std::vector<double> xv;
    /// Y-coordinates of vertices
    std::vector<double> yv;
    /// Z-coordinates of vertices
    std::vector<double> zv;
    /// Interface type.
    int interface{0};
    /// Ratio of dielectric permittivities.
    double lambda{0.};
    /// Collocation point.
    std::array<double, 3> collocationPoint;
    /// Boundary condition.
    double bc{0.};
    /// Fixed charge density.
    double assigned{0.};
    /// Solution (accumulated charge).
    double solution{0.};
  };
  /// List of elements.
  std::vector<Element> m_elements;

  /// Plane existence.
  std::array<bool, 6> m_ynplan{{false, false, false, false, false, false}};
  /// Plane coordinates.
  std::array<double, 6> m_coplan{{0., 0., 0., 0., 0., 0.}};
  /// Plane potentials.
  std::array<double, 6> m_vtplan{{0., 0., 0., 0., 0., 0.}};

  // Model specifications
  std::size_t m_newModel{1};
  std::size_t m_newMesh{1};
  std::size_t m_newBC{1};
  std::size_t m_newPP{1};

  // Store and read options
  std::size_t m_optStoreInflMatrix{0};
  std::size_t m_optReadInflMatrix{0};
  std::size_t m_optStoreInvMatrix{1};
  std::size_t m_optReadInvMatrix{0};
  std::size_t m_optStorePrimitives{0};
  std::size_t m_optReadPrimitives{0};
  std::size_t m_optStoreElements{0};
  std::size_t m_optReadElements{0};
  std::size_t m_optStoreFormatted{1};
  std::size_t m_optStoreUnformatted{0};

  // Plot options
  // std::size_t m_optGnuplotPrimitives = 0;
  // std::size_t m_optGnuplotElements = 0;
  // std::size_t m_optPrimitiveFiles = 0;
  // std::size_t m_optElementFiles = 0;

  // Compute options
  std::size_t m_optSystemChargeZero{1};
  std::size_t m_optValidateSolution{1};
  std::size_t m_optForceValidation{0};
  std::size_t m_optRepeatLHMatrix{0};

  // Fast volume information (physical potential and fields)
  std::size_t m_optFastVol{0};
  std::size_t m_optCreateFastPF{0};
  std::size_t m_optReadFastPF{0};
  std::size_t m_versionFV{0};
  std::size_t m_nbBlocksFV{0};

  // Weighting potential and field related Fast volume information
  std::size_t m_idWtField{0};
  std::vector<std::size_t> m_optWtFldFastVol;
  std::vector<std::size_t> m_optCreateWtFldFastPF;
  std::vector<std::size_t> m_optReadWtFldFastPF;
  std::vector<std::size_t> m_versionWtFldFV;
  std::vector<std::size_t> m_nbBlocksWtFldFV;

  // Known charge options
  std::size_t m_optKnownCharge{0};

  // Charging up options
  std::size_t m_optChargingUp{0};

  // Number of threads to be used by neBEM.
  std::size_t m_nThreads{1};

  // Number of repetitions, after which only primitive properties are used.
  // a negative value implies elements are used always.
  int m_primAfter{-1};

  // Number of repetitions, after which only primitive properties are used
  // for weighting field calculations.
  // A negative value implies only elements are used.
  int m_wtFldPrimAfter{-1};

  // Option for removing primitives from a device geometry.
  // Zero implies none to be removed.
  std::size_t m_optRmPrim{0};

  static constexpr double MinDist{1.e-6};
  /// Target size of elements [cm].
  double m_targetElementSize{50.0e-4};
  /// Smallest number of elements produced along the axis of a primitive.
  std::size_t m_minNbElementsOnLength{1};
  /// Largest number of elements produced along the axis of a primitive.
  std::size_t m_maxNbElementsOnLength{100};
  /// Periodic lengths.
  std::array<double, 3> m_periodicLength{{0., 0., 0.}};
  /// Number of periodic copies along x.
  std::size_t m_nCopiesX{5};
  /// Number of periodic copies along y.
  std::size_t m_nCopiesY{5};
  /// Number of periodic copies along z.
  std::size_t m_nCopiesZ{5};

  enum class Inversion { LU = 0, SVD };
  Inversion m_inversion{Inversion::LU};

  /// Electrode labels and corresponding neBEM weighting field indices.
  std::map<std::string, int> m_wfields;

  void InitValues();
  /// Reduce panels to the basic period.
  void ShiftPanels(std::vector<Panel>& panels) const;
  /// Isolate the parts of polygon 1 that are not hidden by 2 and vice versa.
  bool EliminateOverlaps(const Panel& panel1, const Panel& panel2,
                         std::vector<Panel>& panelsOut,
                         std::vector<int>& itypo);

  bool TraceEnclosed(const std::vector<double>& xl1,
                     const std::vector<double>& yl1,
                     const std::vector<double>& xl2,
                     const std::vector<double>& yl2, const Panel& originalPanel,
                     std::vector<Panel>& newPanels) const;

  void TraceNonOverlap(
      const std::vector<double>& xp1, const std::vector<double>& yp1,
      const std::vector<double>& xl1, const std::vector<double>& yl1,
      const std::vector<double>& xl2, const std::vector<double>& yl2,
      const std::vector<int>& flags1, const std::vector<int>& flags2,
      const std::vector<int>& links1, const std::vector<int>& links2,
      std::vector<bool>& mark1, int ip1, const Panel& originalPanel,
      std::vector<Panel>& newPanels) const;

  void TraceOverlap(
      const std::vector<double>& xp1, const std::vector<double>& yp1,
      const std::vector<double>& xp2, const std::vector<double>& yp2,
      const std::vector<double>& xl1, const std::vector<double>& yl1,
      const std::vector<double>& xl2, const std::vector<double>& yl2,
      const std::vector<int>& flags1, const std::vector<int>& links1,
      const std::vector<int>& links2, std::vector<bool>& mark1, int ip1,
      int ip2, const Panel& originalPanel, std::vector<Panel>& newPanels) const;

  /// Split a polygon into rectangles and right-angled triangles.
  bool MakePrimitives(const Panel& panelIn,
                      std::vector<Panel>& panelsOut) const;

  /// Check whether a polygon contains parallel lines.
  /// If it does, split it in rectangular and non-rectangular parts.
  bool SplitTrapezium(const Panel panelIn, std::vector<Panel>& stack,
                      std::vector<Panel>& panelsOut, const double epsang) const;

  std::size_t NbOfSegments(const double length, const double target) const;
  bool DiscretizeWire(const Primitive& primitive, const double targetSize,
                      std::vector<Element>& elements) const;
  bool DiscretizeTriangle(const Primitive& primitive, const double targetSize,
                          std::vector<Element>& elements) const;
  bool DiscretizeRectangle(const Primitive& prim, const double targetSize,
                           std::vector<Element>& elements) const;
  int InterfaceType(const Solid::BoundaryCondition bc) const;
};

extern ComponentNeBem3d* gComponentNeBem3d;

}  // namespace Garfield

#endif
