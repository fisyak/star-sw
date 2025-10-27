#ifndef G_COMPONENT_TCAD_BASE_H
#define G_COMPONENT_TCAD_BASE_H

#include <array>
#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "Garfield/Component.hh"

namespace Garfield {

class Medium;
/// Interpolation in a field map created by Sentaurus Device.

template <std::size_t N>
class ComponentTcadBase : public Component {
 public:
  /// Default constructor
  ComponentTcadBase() = delete;
  /// Constructor
  ComponentTcadBase(const std::string& name) : Component(name) {
    m_regions.reserve(10);
    m_vertices.reserve(10000);
    m_elements.reserve(10000);
  }
  /// Destructor
  virtual ~ComponentTcadBase() = default;
  /// Set the medium to be associated to a given region.
  void SetMedium(const std::size_t index, Medium* medium);
  /// Set the medium to be associated to all regions with a given material.
  void SetMedium(const std::string& material, Medium* medium);

  /** Import mesh and field map from files.
   * \param gridfilename name of the .grd file containing the mesh
   * \param datafilename name of the .dat file containing the nodal solution
   */
  bool Initialise(const std::string& gridfilename,
                  const std::string& datafilename);

  /** Import field maps defining the prompt weighting field and potential.
    * \param datfile1 .dat file containing the field map at nominal bias.
    * \param datfile2 .dat file containing the field map for a configuration
                      with the potential at the electrode to be read out
                      increased by a small voltage dv.
    * \param dv increase in electrode potential between the two field maps.
    * \param label name of the electrode
    *
    * The field maps must use the same mesh as the drift field.
    */
  bool SetWeightingField(const std::string& datfile1,
                         const std::string& datfile2, const double dv,
                         const std::string& label);

  /// Import field maps defining the prompt weighting field and potential.
  bool SetWeightingPotential(const std::string& datfile1,
                             const std::string& datfile2, const double dv,
                             const std::string& label) {
    return SetWeightingField(datfile1, datfile2, dv, label);
  }
  /// Shift the maps of weighting field/potential for a given electrode
  /// with respect to the original mesh. If the electrode does not exist
  /// yet, a new one will be added to the list.
  bool SetWeightingFieldShift(const std::string& label, const double x,
                              const double y, const double z);
  /// Import time-dependent weighting potentials at t >= 0.
  bool SetDynamicWeightingPotential(const std::string& datfile1,
                                    const std::string& datfile2,
                                    const double dv, const double t,
                                    const std::string& label);
  /// Import time-dependent weighting fields at t >= 0.
  bool SetDynamicWeightingField(const std::string& datfile1,
                                const std::string& datfile2, const double dv,
                                const double t, const std::string& label);

  /// List all currently defined regions.
  void PrintRegions() const;
  /// Get the number of regions in the device.
  std::size_t GetNumberOfRegions() const { return m_regions.size(); }
  /// Get the name and "active volume" flag of a region.
  void GetRegion(const std::size_t ireg, std::string& name, bool& active) const;
  /// Make a region active ("driftable").
  void SetDriftRegion(const std::size_t ireg);
  /// Make a region inactive.
  void UnsetDriftRegion(const std::size_t ireg);

  std::size_t GetNumberOfElements() const override { return m_elements.size(); }
  bool GetElementNodes(const std::size_t i,
                       std::vector<std::size_t>& nodes) const override;
  bool GetElementRegion(const std::size_t i, std::size_t& region,
                        bool& active) const override;
  std::size_t GetNumberOfNodes() const override { return m_vertices.size(); }

  /// Switch use of the imported velocity map on/off.
  void EnableVelocityMap(const bool on);

  /// Get the number of donor states found in the map.
  std::size_t GetNumberOfDonors() { return m_donors.size(); }
  /// Get the number of acceptor states found in the map.
  std::size_t GetNumberOfAcceptors() { return m_acceptors.size(); }

  /** Set the properties of a donor-type defect state.
   * \param donorNumber index of the donor
   * \param exsec cross-section [cm2] for electrons
   * \param hxsec cross-section [cm2] for holes
   * \param concentration defect density [cm-3]
   */
  bool SetDonor(const std::size_t donorNumber, const double exsec,
                const double hxsec, const double concentration);
  /// Set the properties of an acceptor-type defect state.
  bool SetAcceptor(const std::size_t acceptorNumber, const double exsec,
                   const double hxsec, const double concentration);

  /// Use the imported impact ionisation map or not.
  void EnableAlphaMap(const bool on = true) { m_useAlphaMap = on; }

  /// Use the imported trapping map or not.
  void EnableTrapOccupationMap(const bool on = true);
  /// Use the imported lifetime map or not.
  void EnableLifetimeMap(const bool on = true);

  /// Get the electron mobility at a given point in the mesh.
  bool GetElectronMobility(const double x, const double y, const double z,
                           double& mob);
  /// Get the hole mobility at a given point in the mesh.
  bool GetHoleMobility(const double x, const double y, const double z,
                       double& mob);

  double ElectronLifetime(const double x, const double y, const double z);
  double HoleLifetime(const double x, const double y, const double z);

  void WeightingField(const double x, const double y, const double z,
                      double& wx, double& wy, double& wz,
                      const std::string& label) override;
  double WeightingPotential(const double x, const double y, const double z,
                            const std::string& label) override;
  const std::vector<double>& DelayedSignalTimes(
      const std::string& label) override {
    if (m_dwtp.count(label) > 0) return m_dwtp[label];
    static const std::vector<double> emptyVector;
    return emptyVector;
  }
  void DelayedWeightingField(const double x, const double y, const double z,
                             const double t, double& wx, double& wy, double& wz,
                             const std::string& label) override;
  double DelayedWeightingPotential(const double x, const double y,
                                   const double z, const double t,
                                   const std::string& label) override;

  bool GetVoltageRange(double& vmin, double& vmax) override;

  bool HasVelocityMap() const override {
    return m_useVelocityMap && !(m_eVelocity.empty() && m_hVelocity.empty());
  }
  bool ElectronVelocity(const double x, const double y, const double z,
                        double& vx, double& vy, double& vz) override;
  bool HoleVelocity(const double x, const double y, const double z, double& vx,
                    double& vy, double& vz) override;

  bool HasTownsendMap() const override {
    return m_useAlphaMap && !(m_eAlpha.empty() && m_hAlpha.empty());
  }
  bool HasAttachmentMap() const override {
    return ((m_useTrapOccMap || m_useLifetimeMap) &&
            !(m_eEta.empty() && m_hEta.empty()));
  }
  bool HasMobilityMap() const override {
    return !(m_eMobility.empty() && m_hMobility.empty());
  }
  bool ElectronAttachment(const double x, const double y, const double z,
                          double& eta) override;
  bool HoleAttachment(const double x, const double y, const double z,
                      double& eta) override;
  bool ElectronMobility(const double x, const double y, const double z,
                        double& mu) override;
  bool HoleMobility(const double x, const double y, const double z,
                    double& mu) override;

  bool ElectronTownsend(const double x, const double y, const double z,
                        double& alpha) override;
  bool HoleTownsend(const double x, const double y, const double z,
                    double& alpha) override;

 protected:
  // Max. number of vertices per element
  static constexpr std::size_t nMaxVertices{4};

  // Regions
  struct Region {
    // Name of the region (from Tcad)
    std::string name;
    // Material of the region (from Tcad)
    std::string material;
    // Flag indicating if the region is active (i. e. a drift medium)
    bool drift{false};
    // Medium object associated to the region
    Medium* medium{nullptr};
  };
  std::vector<Region> m_regions;

  // Vertex coordinates [cm].
  std::vector<std::array<double, N>> m_vertices;

  // Elements
  struct Element {
    // Indices of vertices
    std::size_t vertex[nMaxVertices]{0, 0, 0, 0};
    // Type of element
    // 0: Point
    // 1: Segment (line)
    // 2: Triangle
    // 3: Rectangle
    // 4: Polygon
    // 5: Tetrahedron
    // 6: Pyramid
    // 7: Prism
    // 8: Brick
    // 9: Tetrabrick
    // 10: Polyhedron
    // In 2D, types 1 - 3 are supported.
    // In 3D, only types 2 and 5 are supported.
    std::size_t type{0};
    // Associated region
    std::size_t region{0};
    // Bounding box
    std::array<float, N> bbMin;
    std::array<float, N> bbMax;
  };
  std::vector<Element> m_elements;

  // Potential [V] at each vertex.
  std::vector<double> m_epot;
  // Electric field [V / cm].
  std::vector<std::array<double, N>> m_efield;

  // Weighting field and potential at each vertex.
  std::map<std::string, std::vector<std::array<double, N>>> m_wfield;
  std::map<std::string, std::vector<double>> m_wpot;
  // Weighting field labels and offsets.
  std::map<std::string, std::vector<double>> m_wshift;

  // Delayed weighting field and potential.
  std::map<std::string, std::vector<std::vector<std::array<double, N>>>> m_dwf;
  std::map<std::string, std::vector<std::vector<double>>> m_dwp;
  // Times corresponding to the delayed weighting fields/potentials.
  std::map<std::string, std::vector<double>> m_dwtf;
  std::map<std::string, std::vector<double>> m_dwtp;

  // Velocities [cm / ns]
  std::vector<std::array<double, N>> m_eVelocity;
  std::vector<std::array<double, N>> m_hVelocity;
  // Mobilities [cm2 / (V ns)]
  std::vector<double> m_eMobility;
  std::vector<double> m_hMobility;
  // Impact ionisation coefficients [1 / cm]
  std::vector<double> m_eAlpha;
  std::vector<double> m_hAlpha;
  // Lifetimes [ns]
  std::vector<double> m_eLifetime;
  std::vector<double> m_hLifetime;
  // Trap occupations [dimensionless]
  std::vector<std::vector<float>> m_donorOcc;
  std::vector<std::vector<float>> m_acceptorOcc;
  // Attachment coefficients [1 / cm]
  std::vector<double> m_eEta;
  std::vector<double> m_hEta;

  struct Defect {
    // Electron cross-section
    double xsece{0.};
    // Hole cross-section
    double xsech{0.};
    // Concentration
    double conc{0.};
  };
  std::vector<Defect> m_donors;
  std::vector<Defect> m_acceptors;

  // Use velocity map or not.
  bool m_useVelocityMap{false};
  // Use trap occupation probability map or not.
  bool m_useTrapOccMap{false};
  // Use lifetime map or not.
  bool m_useLifetimeMap{false};
  // Use impact ionisation map or not.
  bool m_useAlphaMap{false};

  // Bounding box.
  std::array<double, 3> m_bbMin = {{0., 0., 0.}};
  std::array<double, 3> m_bbMax = {{0., 0., 0.}};

  // Voltage range
  double m_pMin{0.};
  double m_pMax{0.};

  void UpdatePeriodicity() override;

  void Cleanup();

  static std::size_t ElementVertices(const Element& element) {
    return std::min(element.type + 1, static_cast<std::size_t>(4));
  }
  virtual bool Interpolate(const double x, const double y, const double z,
                           const std::vector<double>& field, double& f) = 0;
  virtual bool Interpolate(const double x, const double y, const double z,
                           const std::vector<std::array<double, N>>& field,
                           double& fx, double& fy, double& fz) = 0;
  virtual void FillTree() = 0;

  std::size_t FindRegion(const std::string& name) const;
  void MapCoordinates(std::array<double, N>& x,
                      std::array<bool, N>& mirr) const;
  bool InBoundingBox(const std::array<double, N>& x) const {
    for (std::size_t i = 0; i < N; ++i) {
      if (x[i] < m_bbMin[i] || x[i] > m_bbMax[i]) return false;
    }
    return true;
  }
  void UpdateAttachment();
  void ComputeEtaFromLifetime();
  void ComputeEtaFromTraps();

  bool GetOffset(const std::string& label, double& dx, double& dy,
                 double& dz) const;
  bool LoadGrid(const std::string& gridfilename);
  bool LoadData(const std::string& datafilename);
  bool ReadDataset(std::ifstream& datafile, const std::string& dataset);
  bool LoadWeightingField(const std::string& datafilename,
                          std::vector<std::array<double, N>>& wf,
                          std::vector<double>& wp);
};
}  // namespace Garfield
#endif
