#include "heed++/code/EnTransfCS_BGM.h"

#include <cmath>

#include "heed++/code/BGMesh.h"
#include "wcpplib/util/FunNameStack.h"

namespace Heed {

EnTransfCS_BGM::EnTransfCS_BGM(double fparticle_mass, BGMesh* fmesh,
                               int fs_primary_electron, HeedMatterDef* fhmd,
                               long fparticle_charge)
    : particle_mass(fparticle_mass),
      particle_charge(fparticle_charge),
      s_primary_electron(fs_primary_electron),
      hmd(fhmd),
      mesh(fmesh) {
  const long q = mesh->q;
  etcs_bgm.resize(q);
  for (long n = 0; n < q; n++) {
    double bg = mesh->x[n];
    // gamma - 1
    double gamma_1 = std::sqrt(1.0 + (bg * bg)) - 1.0;
    etcs_bgm[n] = EnTransfCS(fparticle_mass, gamma_1, fs_primary_electron, fhmd,
                             fparticle_charge);
  }
}

}  // namespace Heed
