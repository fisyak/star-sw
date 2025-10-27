#ifndef G_COMPONENT_PP_H
#define G_COMPONENT_PP_H

#include <TF1.h>
#include <TF2.h>

#include <string>
#include <vector>

#include "Garfield/Component.hh"
#include "Garfield/ComponentGrid.hh"

namespace Garfield {

class Medium;
// class ComponentGrid;

/// Component for parallel-plate geometries.

class ComponentParallelPlate : public Component {
 public:
  /// Constructor
  ComponentParallelPlate();
  /// Destructor
  ~ComponentParallelPlate() = default;
  /// Setting the medium
  void SetMedium(Medium *medium);

  /** Define the geometry.
   * \param N amount of layers in the geometry, this includes the gas gaps
   *        \f$y\f$.
   * \param d thickness of the layers starting from the bottom to the
   *        top layer along \f$y\f$.
   * \param eps relative permittivities of the layers
   *        starting from the bottom to the top layer along \f$y\f$ .
   *        Here, the gas gaps having a value of 1.
   * \param sigmaIndex Indices of the resistive layers (optional).
   * \param V applied potential difference between the
   *        parallel plates.
   */
  void Setup(const std::size_t N, std::vector<double> eps,
             std::vector<double> d, const double V,
             std::vector<int> sigmaIndex = {});

  void ElectricField(const double x, const double y, const double z, double &ex,
                     double &ey, double &ez, Medium *&m, int &status) override;
  void ElectricField(const double x, const double y, const double z, double &ex,
                     double &ey, double &ez, double &v, Medium *&m,
                     int &status) override;
  using Component::ElectricField;
  double WeightingPotential(const double x, const double y, const double z,
                            const std::string &label) override;

  bool GetVoltageRange(double &vmin, double &vmax) override;

  /** Add a pixel electrode.
   * \param x,z position of the center of the electrode in the xz-plane.
   * \param lx width in the along \f$x\f$.
   * \param lz width in the along \f$z\f$.
   * \param label give name using a string.
   * \param fromAnode is \f$true\f$ is the electrode is the andode and
   * \f$false\f$ if it is the cathode.
   */
  void AddPixel(double x, double z, double lx, double lz,
                const std::string &label, bool fromAnode = true);
  /// Add strip electrode.
  void AddStrip(double z, double lz, const std::string &label,
                bool fromAnode = true);

  /// Add plane electrode, if you want to read the signal from the cathode set
  /// the second argument to false.
  void AddPlane(const std::string &label, bool fromAnode = true);

  /** Calculate time-dependent weighting potential on a grid.
   * \param xmin,ymin,zmin minimum value of the interval in the \f$x\f$-,
   * \f$y\f$- and \f$z\f$-direction. \param xmax,ymax,zmax maximum value of the
   * interval in the \f$x\f$-,\f$y\f$- and \f$z\f$-direction. \param
   * xsteps,ysteps,zsteps mumber of grid nodes in the \f$x\f$-,\f$y\f$- and
   * \f$z\f$-direction. \param label give name using a string.
   */
  void SetWeightingPotentialGrid(const double xmin, const double xmax,
                                 const double xsteps, const double ymin,
                                 const double ymax, const double ysteps,
                                 const double zmin, const double zmax,
                                 const double zsteps, const std::string &label);

  /// This will calculate all electrodes time-dependent weighting potential on
  /// the specified grid.
  void SetWeightingPotentialGrids(const double xmin, const double xmax,
                                  const double xsteps, const double ymin,
                                  const double ymax, const double ysteps,
                                  const double zmin, const double zmax,
                                  const double zsteps);

  /// This will load a previously calculated grid of time-dependent weighting
  /// potential values.
  void LoadWeightingPotentialGrid(const std::string &label);

  Medium *GetMedium(const double x, const double y, const double z) override;

  bool GetBoundingBox(double &xmin, double &ymin, double &zmin, double &xmax,
                      double &ymax, double &zmax) override;

  // Obtain the index of the layer at a given coordinate.
  int GetLayer(const double y) const {
    if (y < m_z[0]) return -1;
    for (int i = 1; i < m_N; i++) {
      if (y <= m_z[i]) return i;
    }
    return -1;
  }
  // Obtain the index and permittivity of the layer at a given coordinate.
  bool GetLayer(const double y, int &m, double &epsM) const {
    m = -1;
    if (y < m_z[0]) return false;
    for (int i = 1; i < m_N; i++) {
      if (y <= m_z[i]) {
        m = i;
        break;
      }
    }
    if (m == -1) return false;
    epsM = m_epsHolder[m - 1];
    return true;
  }
  // Obtain the relative permittivity of the layer with index m.
  double GetPermittivityFromLayer(int m) const { return m_epsHolder.at(m - 1); }
  // Obtain the z-coordinate bounds of layer m
  void getZBoundFromLayer(int m, double &zbottom, double &ztop) {
    ztop = m_z.at(m);
    zbottom = m_z.at(m - 1);
  }
  // Obtain number of layers
  int NumberOfLayers() { return m_N - 1; }
  // Get the indices of the gas gaps
  void IndexOfGasGaps(std::vector<int> &indexGasGap) {
    indexGasGap = {};
    for (int i = 1; i < m_N; i++) {
      if (!m_conductive[i]) indexGasGap.push_back(i);
    }
  }

  void SetIntegrationPrecision(const double eps) { m_precision = eps; }

  void SetIntegrationUpperbound(const double p) { m_upperBoundIntegration = p; }

  void DisablePotentialCalculationOutsideGasGap() {
    m_getPotentialInPlate = false;
  }

 private:
  double m_precision{1.e-12};
  static constexpr double m_Vw{1.};
  /// Voltage difference between the parallel plates.
  double m_V{0.};

  bool m_getPotentialInPlate{true};

  int m_N{0};  ///< Number of layers

  double m_upperBoundIntegration{30.};

  std::vector<double> m_eps;  ///< relative permittivity of each layer
  std::vector<double> m_epsHolder;
  std::vector<double> m_d;  ///< thickness of each layer
  std::vector<double> m_z;

  /// Flag whether a layer is conductive.
  std::vector<bool> m_conductive;

  TF2 m_hIntegrand;

  TF1 m_wpStripIntegral;  ///< Weighting potential integrand for strips
  TF2 m_wpPixelIntegral;  ///< Weighting potential integrand for pixels

  std::vector<std::vector<std::vector<int>>> m_sigmaMatrix;  // sigma_{i,j}^n,
                                                             // where n goes
                                                             // from 1 to N;
  std::vector<std::vector<std::vector<int>>> m_thetaMatrix;  // theta_{i,j}^n,
                                                             // where n goes
                                                             // from 1 to N;

  std::vector<std::vector<double>> m_cMatrix;  ///< c-matrixl.
  std::vector<std::vector<double>> m_vMatrix;  ///< v-matrixl.
  std::vector<std::vector<double>> m_gMatrix;  ///< g-matrixl.
  std::vector<std::vector<double>> m_wMatrix;  ///< w-matrixl.

  int m_currentLayer{0};  ///< Index of the current layer.
  double m_currentPosition{-1.};

  Medium *m_medium{nullptr};

  /// Structure that captures the information of the electrodes under study
  struct Electrode {
    std::string label;                    ///< Label.
    int ind{structureelectrode::NotSet};  ///< Readout group.
    double xpos{0.};
    double ypos{0.};  ///< Coordinates in x/y.
    double lx{0.};
    double ly{0.};  ///< Dimensions in the x-y plane.
    bool formAnode{true};
    bool m_usegrid{false};  ///< Enabling grid based calculations.
    ComponentGrid grid;     ///< grid object.
  };

  /// Possible readout groups
  enum structureelectrode { NotSet = -1, Plane, Strip, Pixel };

  // Vectors storing the readout electrodes.
  std::vector<std::string> m_readout;
  std::vector<Electrode> m_readout_p;

  // Functions that calculate the weighting potential
  double IntegratePromptPotential(const Electrode &el, const double x,
                                  const double y, const double z);

  void CalculateDynamicalWeightingPotential(const Electrode &el);

  double FindWeightingPotentialInGrid(Electrode &el, const double x,
                                      const double y, const double z);

  // Construct the sigma matrix needed to calculate the w, v, c and g
  // matrices
  bool Nsigma(int N, std::vector<std::vector<int>> &sigmaMatrix);

  // Construct the theta matrix needed to calculate the w, v, c and g
  // matrices
  bool Ntheta(int N, std::vector<std::vector<int>> &thetaMatrix,
              std::vector<std::vector<int>> &sigmaMatrix);

  // Construct the sigma and theta matrices.
  void constructGeometryMatrices(const int N);

  // Construct the w, v, c and g matrices needed for constructing
  // the weighting potentials equations.
  void constructGeometryFunction(const int N, const std::vector<double> &d);

  // Build function h needed for the integrand of the weighting potential of a
  // strip and pixel
  void setHIntegrand();

  // build integrand of weighting potential of a strip
  void setwpPixelIntegrand();

  // build integrand of weighting potential of a pixel
  void setwpStripIntegrand();

  // weighting field of a plane in layer with index "indexLayer"
  double constWEFieldLayer(const int indexLayer) {
    double invEz = 0;
    for (int i = 1; i <= m_N - 1; i++) {
      invEz += m_d[i - 1] / m_epsHolder[i - 1];
    }
    return 1 / (m_epsHolder[indexLayer - 1] * invEz);
  }

  // weighting potential of a plane
  double wpPlane(const double z) {
    int im = -1;
    double epsM = -1;
    if (!GetLayer(z, im, epsM)) return 0.;
    double v = 1 - (z - m_z[im - 1]) * constWEFieldLayer(im);
    for (int i = 1; i <= im - 1; i++) {
      v -= m_d[i - 1] * constWEFieldLayer(i);
    }

    return v;
  }

  // electric field in layer with index "indexLayer"
  double constEFieldLayer(const int indexLayer) {
    if (m_conductive[indexLayer]) return 0.;
    double invEz = 0;
    for (int i = 1; i <= m_N - 1; i++) {
      // TODO!
      if (m_conductive[indexLayer]) continue;
      invEz -= m_d[i - 1] / m_epsHolder[i - 1];
    }
    return m_V / (m_epsHolder[indexLayer - 1] * invEz);
  }

  // function to convert decimal to binary expressed in n digits.
  bool decToBinary(int n, std::vector<int> &binaryNum);

  // Rebuilds c, v, g and w matrix.
  void LayerUpdate(const double z, const int im, const double epsM) {
    if (z == m_currentPosition) return;

    m_currentPosition = z;

    if (im != m_currentLayer) {
      m_currentLayer = im;
      for (int i = 0; i < im - 1; i++) m_eps[i] = m_epsHolder[i];
      m_eps[im - 1] = epsM;
      m_eps[im] = epsM;
      for (int i = im + 1; i < m_N; i++) m_eps[i] = m_epsHolder[i - 1];
    }

    double diff1 = m_z[im] - z;
    double diff2 = z - m_z[im - 1];

    std::vector<double> d(m_N, 0.);
    for (int i = 0; i < im - 1; i++) d[i] = m_d[i];
    d[im - 1] = diff2;
    d[im] = diff1;
    for (int i = im + 1; i < m_N; i++) d[i] = m_d[i - 1];
    // TODO::Construct c and g matrices only for im != m_currentLayer.
    constructGeometryFunction(m_N, d);
  };

  void UpdatePeriodicity() override;
  void Reset() override;
};
}  // namespace Garfield
#endif
