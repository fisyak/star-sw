#include "Garfield/GeometryRoot.hh"

#include <TGeoBBox.h>

#include <iostream>

#include "Garfield/Exceptions.hh"
#include "Garfield/Medium.hh"

namespace Garfield {

GeometryRoot::GeometryRoot() : Geometry("GeometryRoot") {}

void GeometryRoot::SetGeometry(TGeoManager* geoman) {
  if (!geoman) throw Exception("geoman can't be null");
  m_geoManager = geoman;
  m_materials.clear();
}

void GeometryRoot::SetMedium(const std::size_t imat, Medium* medium) {
  if (!m_geoManager)
    throw Exception(
        (m_className + std::string("::SetMedium: ROOT geometry is not "
                                   "defined. Call SetGeometry first."))
            .c_str());
  if (!medium) throw Exception("medium can't be nullptr");
  TGeoMaterial* mat = m_geoManager->GetMaterial(imat);
  if (!mat) {
    std::cerr << m_className << "::SetMedium:\n"
              << "    ROOT material " << imat << " does not exist.\n";
    return;
  }

  std::string name(mat->GetName());

  // Check if this material has already been associated with a medium.
  if (m_materials.count(name) > 0) {
    std::cout << m_className << "::SetMedium:\n"
              << "    Replacing existing association of material " << name
              << " with medium " << medium->GetName() << ".\n";
  }
  m_materials[name] = medium;

  // Check if material properties match
  const double rho1 = mat->GetDensity();
  const double rho2 = medium->GetMassDensity();
  std::cout << m_className << "::SetMedium:\n"
            << "    ROOT material: " << name << "\n"
            << "      Density: " << rho1 << " g / cm3\n"
            << "    Medium: " << medium->GetName() << "\n"
            << "      Density: " << rho2 << " g / cm3\n";
  if (rho1 > 0 && fabs(rho1 - rho2) / rho1 > 0.01) {
    std::cout << "    WARNING: Densities differ by > 1%.\n";
  }
}

void GeometryRoot::SetMedium(const std::string& name, Medium* medium) {
  if (!m_geoManager)
    throw Exception(
        (m_className + std::string("::SetMedium: ROOT geometry is not "
                                   "defined. Call SetGeometry first."))
            .c_str());
  if (!medium) throw Exception("medium can't be nullptr");

  const int imat = m_geoManager->GetMaterialIndex(name.c_str());
  if (imat < 0) {
    std::cerr << m_className << "::SetMedium:\n"
              << "    ROOT material " << name << " does not exist.\n";
    return;
  }

  SetMedium(imat, medium);
}

Medium* GeometryRoot::GetMedium(const double x, const double y, const double z,
                                const bool /*tesselated*/) const {
  if (!m_geoManager) return nullptr;
  m_geoManager->SetCurrentPoint(x, y, z);
  if (m_geoManager->IsOutside()) return nullptr;
  TGeoNode* cnode = m_geoManager->GetCurrentNode();
  std::string name(cnode->GetMedium()->GetMaterial()->GetName());

  const auto it = m_materials.find(name);
  if (it == m_materials.end()) return nullptr;
  return it->second;
}

std::size_t GeometryRoot::GetNumberOfMaterials() {
  if (!m_geoManager)
    throw Exception("ROOT geometry is not defined. Call SetGeometry first");
  return m_geoManager->GetListOfMaterials()->GetEntries();
}

TGeoMaterial* GeometryRoot::GetMaterial(const std::size_t i) {
  if (!m_geoManager)
    throw Exception("ROOT geometry is not defined. Call SetGeometry first");
  return m_geoManager->GetMaterial(i);
}

TGeoMaterial* GeometryRoot::GetMaterial(const char* name) {
  if (!m_geoManager)
    throw Exception("ROOT geometry is not defined. Call SetGeometry first");
  return m_geoManager->GetMaterial(name);
}

bool GeometryRoot::IsInside(const double x, const double y, const double z,
                            const bool /*tesselated*/) const {
  if (!m_geoManager)
    throw Exception("ROOT geometry is not defined. Call SetGeometry first");
  m_geoManager->SetCurrentPoint(x, y, z);
  return !m_geoManager->IsOutside();
}

bool GeometryRoot::GetBoundingBox(double& xmin, double& ymin, double& zmin,
                                  double& xmax, double& ymax, double& zmax) {
  if (!m_geoManager)
    throw Exception("ROOT geometry is not defined. Call SetGeometry first");
  auto top = m_geoManager->GetTopVolume();
  if (!top) return false;
  if (!top->GetShape()) return false;
  TGeoBBox* box = (TGeoBBox*)m_geoManager->GetTopVolume()->GetShape();
  if (!box) return false;
  const double dx = box->GetDX();
  const double dy = box->GetDY();
  const double dz = box->GetDZ();
  const double ox = box->GetOrigin()[0];
  const double oy = box->GetOrigin()[1];
  const double oz = box->GetOrigin()[2];
  xmin = ox - dx;
  xmax = ox + dx;
  ymin = oy - dy;
  ymax = oy + dy;
  zmin = oz - dz;
  zmax = oz + dz;
  return true;
}

}  // namespace Garfield
