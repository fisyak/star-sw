#include <TH3.h>
#include <TRandom3.h>
#include "TMath.h"
#include "TFile.h"
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cmath>
#if !defined(__CINT__) && !defined(__CLING__) && ! defined(__MAKECINT__)

#include <tuple>
struct Voxel {
  int ix, iy, iz;
  double content;
};
static TH3F *h = 0;
struct Region3D {
  std::vector<Voxel> voxels;
  double totalContent = 0.0;
  double mean = 0.0;
  double sigma = 0.0;
  
  std::pair<double, double> MuSigma() const {
    double mu = 0;
    double sigma = 0;
    int    N = 0;
    double X = 0, X2 = 0;
    for (auto v : voxels) {
      N++;
      X += v.content;
      X2 += v.content*v.content;
    }
    if (N) {
      mu = X/N;
      X2 /= N;
      sigma = TMath::Sqrt(X2 - mu*mu);
    }
    return {mu,sigma};
  }
  void Print() const {
    int ix1 = 999, ix2 = -1;
    int iy1 = 999, iy2 = -1;
    int iz1 = 999, iz2 = -1;
    for (auto v : voxels) {
      ix1 = TMath::Min(ix1, v.ix);
      ix2 = TMath::Max(ix2, v.ix);
      iy1 = TMath::Min(iy1, v.iy);
      iy2 = TMath::Max(iy2, v.iy);
      iz1 = TMath::Min(iz1, v.iz);
      iz2 = TMath::Max(iz2, v.iz);
    }
    const std::pair<double, double> ms = MuSigma();
    std::cout
      << " | nVoxels = " << voxels.size()
      << " | content = " << totalContent
      << " | mu = " << ms.first << " +- " << ms.second
      << "  [" << ix1 << "," << ix2 << "] " 
      << ", [" << iy1 << "," << iy2 << "] " 
      << ", [" << iz1 << "," << iz2 << "] ("
      << h->GetXaxis()->GetBinLowEdge(ix1) << "," << h->GetXaxis()->GetBinUpEdge(ix2) << ","
      << h->GetYaxis()->GetBinLowEdge(iy1) << "," << h->GetYaxis()->GetBinUpEdge(iy2) << ","
      << h->GetZaxis()->GetBinLowEdge(iz1) << "," << h->GetZaxis()->GetBinUpEdge(iz2) << ")"
      << endl;
  }
};

bool Inside(const TH3* h, int ix, int iy, int iz)
{
  return ix >= 1 && ix <= h->GetNbinsX() &&
    iy >= 1 && iy <= h->GetNbinsY() &&
    iz >= 1 && iz <= h->GetNbinsZ();
}

std::vector<std::tuple<int,int,int>> NeighborOffsets6()
{
  return {
    {+1,0,0}, {-1,0,0},
		{0,+1,0}, {0,-1,0},
			    {0,0,+1}, {0,0,-1}
  };
}

std::vector<Region3D> MergeVoxelsEqualContent(TH3* h,
                                              double targetContent,
                                              double minVoxelContent = 1.0)
{
  static int _debug = 0;
  const int nx = h->GetNbinsX();
  const int ny = h->GetNbinsY();
  const int nz = h->GetNbinsZ();
  
  auto Index = [ny, nz](int ix, int iy, int iz) {
    return ((ix * (ny + 1)) + iy) * (nz + 1) + iz;
  };
  
  std::vector<char> assigned((nx + 1) * (ny + 1) * (nz + 1), 0);
  auto neighbors = NeighborOffsets6();
  std::vector<Voxel> allVoxels;
  for (int ix = 1; ix <= nx; ++ix) {
    for (int iy = 1; iy <= ny; ++iy) {
      for (int iz = 1; iz <= nz; ++iz) {
	double c = h->GetBinContent(ix, iy, iz);
	if (c >= minVoxelContent) {
	  allVoxels.push_back({ix, iy, iz, c});
	}
      }
    }
  }
  
  // Start from highest-content voxels first
  std::sort(allVoxels.begin(), allVoxels.end(),
	    [](const Voxel& a, const Voxel& b) {
	      return a.content > b.content;
	    });
  
  std::vector<Region3D> regions;
  
  for (const auto& seed : allVoxels) {
    int indx = Index(seed.ix, seed.iy, seed.iz);
    if (assigned[indx]) continue;
    
    Region3D region;
    std::queue<Voxel> frontier;
    
    frontier.push(seed);
    assigned[indx] = 1;
    
    while (!frontier.empty()) {
      Voxel v = frontier.front();
      frontier.pop();
      
      double c =  h->GetBinContent(v.ix, v.iy, v.iz);
      if (c < minVoxelContent) continue;
      
      // If adding this voxel would overshoot too much,
      // still allow it if region is empty, otherwise skip further growth only if already close
      if (!region.voxels.empty()) {
#if 0
	auto ms = region.MuSigma();
	if (TMath::Abs(ms.first - c) > minVoxelContent) continue;
#else
	double newTotal = region.totalContent + c;
	double oldDiff = std::fabs(region.totalContent - targetContent);
	double newDiff = std::fabs(newTotal - targetContent);
	
	if (region.totalContent >= 0.8 * targetContent && newDiff > oldDiff) {
	  continue;
	}
#endif
      }
      
      region.voxels.push_back(v);
      region.totalContent += c;
      if (_debug) region.Print();
#if 1
      if (region.totalContent >= targetContent) {
	continue;
      }
#endif
      std::vector<Voxel> candidates;
      auto ms = region.MuSigma();
      for (const auto& off : neighbors) {
	int dx, dy, dz;
	std::tie(dx, dy, dz) = off;
	
	int jx = v.ix + dx;
	int jy = v.iy + dy;
	int jz = v.iz + dz;
	
	if (!Inside(h, jx, jy, jz)) continue;
	int jndx = Index(jx, jy, jz);
	if (assigned[jndx]) continue;
	
	double cc = h->GetBinContent(jx, jy, jz);
	if (cc < minVoxelContent) continue;
	if (cc < 0.1*ms.first ) continue;
	candidates.push_back({jx, jy, jz, cc});
      }
      if (! candidates.size()) continue;
      // Prefer larger neighboring voxels first
      std::sort(candidates.begin(), candidates.end(),
		[](const Voxel& a, const Voxel& b) {
		  return a.content > b.content;
		});
      
      for (const auto& cand : candidates) {
	int idx = Index(cand.ix, cand.iy, cand.iz);
	if (!assigned[idx]) {
	  assigned[idx] = 1;
	  frontier.push(cand);
	}
      }
    }
    
    if (!region.voxels.empty()) {
      if (_debug) region.Print();
      regions.push_back(region);
    }
  }
  
  return regions;
}
#endif
void merge_voxels_equal_content()
{
#if 0
  auto h = new TH3D("h", "3D voxel merging;X;Y;Z", 20, 0, 20, 20, 0, 20, 20, 0, 20);
  h->Sumw2();
  
  TRandom3 rng(12345);
  
  for (int i = 0; i < 4000; ++i) {
    h->Fill(rng.Gaus(6, 1.8), rng.Gaus(7, 1.5), rng.Gaus(8, 1.2));
  }
  
  for (int i = 0; i < 3500; ++i) {
    h->Fill(rng.Gaus(14, 1.7), rng.Gaus(13, 1.8), rng.Gaus(11, 1.6));
  }
  
  for (int i = 0; i < 400; ++i) {
    h->Fill(rng.Uniform(0, 20), rng.Uniform(0, 20), rng.Uniform(0, 20));
  }
#else
  TH3F *No = (TH3F *) gDirectory->Get("No");
  if (! No) return;
  TH3F *RadlI = (TH3F *) gDirectory->Get("RadlI_FSTW");
  h  = new TH3F(*No);
  h->SetName("ratio");
  h->Reset();
  TH1D *val = new TH1D("val","val",200,0.,1.0);
  
  int x0 = 1, y0 = 1, z0 = 1;
  int x1 = h->GetXaxis()->GetNbins();
  int y1 = h->GetYaxis()->GetNbins();
  int z1 = h->GetZaxis()->GetNbins();
  for (int ix = x0; ix <= x1; ++ix) {
    for (int iy = y0; iy <= y1; ++iy) {
      for (int iz = z0; iz <= z1; ++iz) {
	double c = RadlI->GetBinContent(ix, iy, iz);
	if (c <= 0.0) continue;
	double n = No->GetBinContent(ix, iy, iz);
	if (n < 2) continue;
	double av = c/n;
#if 0
	double e = h->GetBinError(ix, iy, iz);
	double err2 = e*e/n - av*av;
#endif
	h->SetBinContent(ix,iy,iz,av);
#if 0
	h->SetBinError(ix,iy,iz,TMath::Sqrt(err2));
#endif
	val->Fill(av);
      }
    }
  }
#endif
  double total = h->Integral();
  int desiredRegions = 25;
  double target = total / desiredRegions;
  //  double_t target = 1e-2;
  
  auto regions = MergeVoxelsEqualContent(h, target, 1e-2);
  std::cout << "Total content = " << total << "\n";
  std::cout << "Target per region = " << target << "\n";
  std::cout << "Found " << regions.size() << " merged regions\n\n";
  
  for (size_t i = 0; i < regions.size(); ++i) {
    const auto& r = regions[i];
    if (r.voxels.size() < 2) continue;
    std::cout  << "Region " << i;
    r.Print();
  }
}
/*
root.exe [4] .x merge_voxels_equal_content.C+
Info in <TUnixSystem::ACLiC>: creating shared library /gpfs/mnt/gpfs01/star/subsys-tpc/fisyak/STAR/packages/TFG/StarDb/AgiGeometry/hold/.al98_x8664_gcc11/merge_voxels_equal_content_C.so
Total content = 17501.1
Target per region = 700.046
Found 452 merged regions

Region 0 | nVoxels = 6036 | content = 700.052 | mu = 0.115979 +- 0.132191  [7,31] , [456,482] , [10,52] (-1.7,-0.45,27.75,29.1,-12.5,9)
Region 1 | nVoxels = 9316 | content = 700.058 | mu = 0.0751458 +- 0.0958121  [7,36] , [230,270] , [35,68] (-1.7,-0.2,16.45,18.5,0,17)
Region 2 | nVoxels = 6892 | content = 700.055 | mu = 0.101575 +- 0.119237  [14,36] , [224,252] , [2,43] (-1.35,-0.2,16.15,17.6,-16.5,4.5)
Region 3 | nVoxels = 16960 | content = 700.045 | mu = 0.0412763 +- 0.0470667  [10,36] , [200,272] , [13,68] (-1.55,-0.2,14.95,18.6,-11,17)
Region 4 | nVoxels = 16164 | content = 700.048 | mu = 0.0433091 +- 0.0453846  [7,36] , [214,288] , [1,40] (-1.7,-0.2,15.65,19.4,-17,3)
Region 5 | nVoxels = 9169 | content = 700.075 | mu = 0.0763524 +- 0.0885023  [7,31] , [445,495] , [21,68] (-1.7,-0.45,27.2,29.75,-7,17)
Region 6 | nVoxels = 13083 | content = 700.077 | mu = 0.0535104 +- 0.0616109  [7,31] , [423,503] , [1,37] (-1.7,-0.45,26.1,30.15,-17,1.5)
Region 7 | nVoxels = 8115 | content = 700.057 | mu = 0.086267 +- 0.0615369  [1,70] , [497,558] , [48,68] (-2,1.5,29.8,32.9,6.5,17)
Region 8 | nVoxels = 8060 | content = 700.044 | mu = 0.0868541 +- 0.0818557  [7,27] , [259,371] , [42,68] (-1.7,-0.65,17.9,23.55,3.5,17)
Region 9 | nVoxels = 9691 | content = 700.044 | mu = 0.0722366 +- 0.0724889  [7,27] , [277,377] , [1,33] (-1.7,-0.65,18.8,23.85,-17,-0.5)
Region 10 | nVoxels = 12370 | content = 700.09 | mu = 0.0565958 +- 0.0451538  [1,27] , [454,526] , [21,68] (-2,-0.65,27.65,31.3,-7,17)
Region 11 | nVoxels = 252 | content = 25.2615 | mu = 0.100244 +- 0.0711587  [60,70] , [548,558] , [58,64] (0.95,1.5,32.35,32.9,11.5,15)
Region 12 | nVoxels = 12019 | content = 700.059 | mu = 0.058246 +- 0.0556056  [7,27] , [360,462] , [29,68] (-1.7,-0.65,22.95,28.1,-3,17)
Region 13 | nVoxels = 2375 | content = 265.502 | mu = 0.11179 +- 0.075965  [14,27] , [367,429] , [5,8] (-1.35,-0.65,23.3,26.45,-15,-13)
Region 14 | nVoxels = 5 | content = 0.818591 | mu = 0.163718 +- 0.125872  [22,24] , [462,462] , [20,22] (-0.95,-0.8,28.05,28.1,-7.5,-6)
Region 15 | nVoxels = 2 | content = 0.245764 | mu = 0.122882 +- 0.0928566  [25,25] , [462,462] , [22,23] (-0.8,-0.75,28.05,28.1,-6.5,-5.5)
Region 16 | nVoxels = 19640 | content = 700.058 | mu = 0.0356445 +- 0.0108499  [7,16] , [363,461] , [1,68] (-1.7,-1.2,23.1,28.05,-17,17)
Region 19 | nVoxels = 9312 | content = 700.057 | mu = 0.075178 +- 0.040746  [1,16] , [489,547] , [1,40] (-2,-1.2,29.4,32.35,-17,3)
Region 20 | nVoxels = 6376 | content = 700.072 | mu = 0.109798 +- 0.0114487  [1,8] , [536,570] , [5,45] (-2,-1.6,31.75,33.5,-15,5.5)
Region 21 | nVoxels = 6303 | content = 699.997 | mu = 0.111058 +- 0.00630393  [1,8] , [518,570] , [32,64] (-2,-1.6,30.85,33.5,-1.5,15)
Region 22 | nVoxels = 149 | content = 16.5292 | mu = 0.110934 +- 0.00333808  [1,8] , [563,570] , [57,64] (-2,-1.6,33.1,33.5,11,15)
Region 23 | nVoxels = 1003 | content = 112.017 | mu = 0.111682 +- 0.0026073  [1,8] , [559,570] , [20,47] (-2,-1.6,32.9,33.5,-7.5,6.5)
Region 25 | nVoxels = 19941 | content = 700.049 | mu = 0.035106 +- 0.0158638  [27,36] , [43,139] , [7,68] (-0.7,-0.2,7.1,11.95,-14,17)
Region 26 | nVoxels = 20372 | content = 700.059 | mu = 0.0343638 +- 0.0150695  [27,36] , [60,186] , [1,56] (-0.7,-0.2,7.95,14.3,-17,11)
Region 27 | nVoxels = 20727 | content = 700.057 | mu = 0.0337751 +- 0.0149418  [9,36] , [120,226] , [1,68] (-1.6,-0.2,10.95,16.3,-17,17)
Region 28 | nVoxels = 19997 | content = 700.049 | mu = 0.0350077 +- 0.0152134  [27,36] , [1,70] , [1,68] (-0.7,-0.2,5,8.5,-17,17)
Region 30 | nVoxels = 4824 | content = 157.611 | mu = 0.0326722 +- 0.0127639  [27,36] , [13,75] , [18,68] (-0.7,-0.2,5.6,8.75,-8.5,17)
Region 31 | nVoxels = 21566 | content = 700.051 | mu = 0.0324609 +- 0.00897574  [7,36] , [172,287] , [1,68] (-1.7,-0.2,13.55,19.35,-17,17)
Region 32 | nVoxels = 19661 | content = 700.059 | mu = 0.0356065 +- 0.00844153  [7,16] , [274,367] , [1,68] (-1.7,-1.2,18.65,23.35,-17,17)
Region 33 | nVoxels = 5537 | content = 188.382 | mu = 0.0340224 +- 0.00849688  [7,16] , [256,324] , [23,68] (-1.7,-1.2,17.75,21.2,-6,17)
Region 34 | nVoxels = 4806 | content = 164.066 | mu = 0.0341378 +- 0.00886774  [7,16] , [353,408] , [34,68] (-1.7,-1.2,22.6,25.4,-0.5,17)
Region 35 | nVoxels = 1666 | content = 57.6042 | mu = 0.0345763 +- 0.00943548  [7,16] , [360,391] , [1,24] (-1.7,-1.2,22.95,24.55,-17,-5)
Region 36 | nVoxels = 791 | content = 25.7468 | mu = 0.0325497 +- 0.00861903  [7,16] , [272,301] , [1,22] (-1.7,-1.2,18.55,20.05,-17,-6)
Region 37 | nVoxels = 8533 | content = 255.835 | mu = 0.0299818 +- 0.014451  [8,35] , [260,542] , [15,48] (-1.65,-0.25,17.95,32.1,-10,7)
Region 39 | nVoxels = 2 | content = 0.0851938 | mu = 0.0425969 +- 0.00100941  [7,7] , [460,460] , [62,63] (-1.7,-1.65,27.95,28,13.5,14.5)
Region 40 | nVoxels = 2 | content = 0.0531413 | mu = 0.0265706 +- 0.0150361  [19,19] , [228,228] , [35,36] (-1.1,-1.05,16.35,16.4,0,1)
Region 43 | nVoxels = 2216 | content = 61.2204 | mu = 0.0276265 +- 0.00775697  [22,35] , [246,286] , [44,68] (-0.95,-0.25,17.25,19.3,4.5,17)
Region 44 | nVoxels = 250 | content = 6.31786 | mu = 0.0252714 +- 0.00890031  [29,35] , [265,286] , [1,10] (-0.6,-0.25,18.2,19.3,-17,-12)
Region 47 | nVoxels = 72 | content = 2.02704 | mu = 0.0281533 +- 0.00703351  [29,35] , [235,244] , [66,68] (-0.6,-0.25,16.7,17.2,15.5,17)
Region 49 | nVoxels = 97 | content = 2.53159 | mu = 0.0260988 +- 0.0076834  [9,16] , [534,543] , [65,68] (-1.6,-1.2,31.65,32.15,15,17)
Region 52 | nVoxels = 89 | content = 2.45987 | mu = 0.027639 +- 0.00708501  [8,16] , [459,467] , [62,68] (-1.65,-1.2,27.9,28.35,13.5,17)
Region 54 | nVoxels = 27 | content = 0.697039 | mu = 0.0258162 +- 0.00891736  [29,34] , [221,227] , [66,68] (-0.6,-0.3,16,16.35,15.5,17)
Region 55 | nVoxels = 47 | content = 1.17078 | mu = 0.0249101 +- 0.00945599  [27,31] , [61,70] , [1,2] (-0.7,-0.45,8,8.5,-17,-16)
Region 56 | nVoxels = 191 | content = 4.69524 | mu = 0.0245824 +- 0.00801  [9,16] , [529,543] , [1,6] (-1.6,-1.2,31.4,32.15,-17,-14)
Region 92 | nVoxels = 8 | content = 0.200869 | mu = 0.0251086 +- 0.00600614  [15,16] , [515,516] , [38,41] (-1.3,-1.2,30.7,30.8,1.5,3.5)
Region 96 | nVoxels = 2 | content = 0.0420357 | mu = 0.0210178 +- 0.00900764  [14,14] , [506,507] , [59,59] (-1.35,-1.3,30.25,30.35,12,12.5)
Region 99 | nVoxels = 25 | content = 0.422666 | mu = 0.0169066 +- 0.00311013  [12,16] , [329,337] , [68,68] (-1.45,-1.2,21.4,21.85,16.5,17)
Region 103 | nVoxels = 2 | content = 0.0404994 | mu = 0.0202497 +- 0.00892643  [12,13] , [283,283] , [15,15] (-1.45,-1.35,19.1,19.15,-10,-9.5)
Region 104 | nVoxels = 6 | content = 0.119476 | mu = 0.0199126 +- 0.00487751  [14,14] , [234,235] , [34,37] (-1.35,-1.3,16.65,16.75,-0.5,1.5)
Region 106 | nVoxels = 2 | content = 0.0377763 | mu = 0.0188881 +- 0.0070005  [21,22] , [463,463] , [18,18] (-1,-0.9,28.1,28.15,-8.5,-8)
Region 110 | nVoxels = 341 | content = 7.11048 | mu = 0.0208519 +- 0.00430575  [15,31] , [486,500] , [53,55] (-1.3,-0.45,29.25,30,9,10.5)
Region 111 | nVoxels = 674 | content = 14.195 | mu = 0.0210608 +- 0.0043282  [15,31] , [483,500] , [14,16] (-1.3,-0.45,29.1,30,-10.5,-9)
Region 115 | nVoxels = 4 | content = 0.0546123 | mu = 0.0136531 +- 0.00404404  [16,16] , [381,384] , [8,8] (-1.25,-1.2,24,24.2,-13.5,-13)
Region 118 | nVoxels = 2 | content = 0.0299119 | mu = 0.0149559 +- 0.00446054  [14,14] , [249,250] , [10,10] (-1.35,-1.3,17.4,17.5,-12.5,-12)
Region 120 | nVoxels = 2 | content = 0.0305577 | mu = 0.0152789 +- 0.00351129  [18,18] , [241,241] , [31,32] (-1.15,-1.1,17,17.05,-2,-1)
Region 121 | nVoxels = 2 | content = 0.033859 | mu = 0.0169295 +- 0.00146505  [15,15] , [468,468] , [31,32] (-1.3,-1.25,28.35,28.4,-2,-1)
Region 122 | nVoxels = 2 | content = 0.0304192 | mu = 0.0152096 +- 0.00226526  [16,16] , [390,391] , [64,64] (-1.25,-1.2,24.45,24.55,14.5,15)
Region 132 | nVoxels = 11 | content = 0.146403 | mu = 0.0133093 +- 0.00144833  [13,16] , [305,309] , [53,53] (-1.4,-1.2,20.2,20.45,9,9.5)
Region 136 | nVoxels = 11 | content = 0.130664 | mu = 0.0118785 +- 0.00140529  [15,16] , [533,538] , [68,68] (-1.3,-1.2,31.6,31.9,16.5,17)
*/
