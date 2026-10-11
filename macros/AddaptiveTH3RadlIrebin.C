#include <TH3.h>
#include <TAxis.h>
#include <TMath.h>
#include "TRandom3.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <cmath>
#include <algorithm>
#include "TString.h"
#include "TFile.h"
#include "TMath.h"
struct Block3D {
  int x0, x1; // inclusive bin indices
  int y0, y1;
  int z0, z1;
  double content;
  double error2;
};

struct SplitCandidate {
  char axis;   // 'x', 'y', 'z'
  int split;   // split position: left block ends at split, right starts at split+1
  double imbalance;
  double leftContent;
  double rightContent;
  bool valid;

  SplitCandidate() : axis(0), split(-1), imbalance(0), leftContent(0), rightContent(0), valid(false) {}
};

class AdaptiveRebinner3D {
public:
  AdaptiveRebinner3D(TH3 * hNo,TH3* hist) : No(hNo), h(hist) {
    if (!h || ! No) {
      throw std::runtime_error("Null TH3 pointer passed to AdaptiveRebinner3D");
    }
  }
  
  std::vector<Block3D> PartitionByTarget(double targetContent,
					 int minBinsX = 1,
					 int minBinsY = 1,
					 int minBinsZ = 1,
					 double minBlockContent = 0.0)    {
    std::vector<Block3D> out;
    Recurse(1, h->GetNbinsX(),
	    1, h->GetNbinsY(),
	    1, h->GetNbinsZ(),
	    targetContent,
	    minBinsX, minBinsY, minBinsZ,
	    minBlockContent,
	    out);
    return out;
  }

  static void PrintBlocks(const TH3* h, const std::vector<Block3D>& blocks)    {
    std::cout << "Number of merged blocks: " << blocks.size() << "\n\n";
    for (size_t i = 0; i < blocks.size(); ++i) {
      const auto& b = blocks[i];
      
      double xlow = h->GetXaxis()->GetBinLowEdge(b.x0);
      double xup  = h->GetXaxis()->GetBinUpEdge(b.x1);
      double ylow = h->GetYaxis()->GetBinLowEdge(b.y0);
      double yup  = h->GetYaxis()->GetBinUpEdge(b.y1);
      double zlow = h->GetZaxis()->GetBinLowEdge(b.z0);
      double zup  = h->GetZaxis()->GetBinUpEdge(b.z1);
      
      std::cout
	<< "Block " << i
	<< " | bins x:[" << b.x0 << "," << b.x1 << "]"
	<< " y:[" << b.y0 << "," << b.y1 << "]"
	<< " z:[" << b.z0 << "," << b.z1 << "]"
	<< " | coords x:[" << xlow << "," << xup << "]"
	<< " y:[" << ylow << "," << yup << "]"
	<< " z:[" << zlow << "," << zup << "]"
	<< " | content=" << b.content
	<< " | error=" << std::sqrt(b.error2)
	<< "\n";
    }
  }

private:
  TH3* h, *No;
  
  std::pair<double, double> BlockSumError2(int x0, int x1, int y0, int y1, int z0, int z1) const {
    double sum = 0.0;
    double err2 = 0.0;
    double sigma = 0.0;
    double average = 0;
    int N = 0;
    for (int ix = x0; ix <= x1; ++ix) {
      for (int iy = y0; iy <= y1; ++iy) {
	for (int iz = z0; iz <= z1; ++iz) {
	  double c = h->GetBinContent(ix, iy, iz);
	  double n = No->GetBinContent(ix, iy, iz);
	  if (n < 2) continue;
	  N++;
	  double av = c/n;
	  double e = h->GetBinError(ix, iy, iz);
	  double aw2 = e*e/(n - 1);
	  sum += av;
	  err2 += aw2;
	}
      }
    }
    if (N > 0) {
      average = sum/N;
      err2 /= N;
      sigma = TMath::Sqrt(err2 - average*average);
    } else { 
      sum = 0;
      sigma = 0;
    }
    return {sigma, average}; 
  }
  
  SplitCandidate FindBestSplit(int x0, int x1, int y0, int y1, int z0, int z1,
			       int minBinsX, int minBinsY, int minBinsZ) const    {
    SplitCandidate best;
    
    auto totalPair = BlockSumError2(x0, x1, y0, y1, z0, z1);
    double total = totalPair.first;
    
    // Split along x
    if ((x1 - x0 + 1) >= 2 * minBinsX) {
      for (int s = x0 + minBinsX - 1; s <= x1 - minBinsX; ++s) {
	double left = BlockSumError2(x0, s, y0, y1, z0, z1).first;
	double right = total - left;
	double imbalance = std::fabs(left - right);
	
	if (!best.valid || imbalance < best.imbalance) {
	  best.axis = 'x';
	  best.split = s;
	  best.imbalance = imbalance;
	  best.leftContent = left;
	  best.rightContent = right;
	  best.valid = true;
	}
      }
    }

    // Split along y
    if ((y1 - y0 + 1) >= 2 * minBinsY) {
      for (int s = y0 + minBinsY - 1; s <= y1 - minBinsY; ++s) {
	double left = BlockSumError2(x0, x1, y0, s, z0, z1).first;
	double right = total - left;
	double imbalance = std::fabs(left - right);
	if (!best.valid || imbalance < best.imbalance) {
	  best.axis = 'y';
	  best.split = s;
	  best.imbalance = imbalance;
	  best.leftContent = left;
	  best.rightContent = right;
	  best.valid = true;
	}
      }
    }
    
    // Split along z
    if ((z1 - z0 + 1) >= 2 * minBinsZ) {
      for (int s = z0 + minBinsZ - 1; s <= z1 - minBinsZ; ++s) {
	double left = BlockSumError2(x0, x1, y0, y1, z0, s).first;
	double right = total - left;
	double imbalance = std::fabs(left - right);
	
	if (!best.valid || imbalance < best.imbalance) {
	  best.axis = 'z';
	  best.split = s;
	  best.imbalance = imbalance;
	  best.leftContent = left;
	  best.rightContent = right;
	  best.valid = true;
	}
      }
    }
    
    return best;
  }
  
  void Recurse(int x0, int x1, int y0, int y1, int z0, int z1,
	       double targetContent,
	       int minBinsX, int minBinsY, int minBinsZ,
	       double minBlockContent,
	       std::vector<Block3D>& out)
  {
    auto totalPair = BlockSumError2(x0, x1, y0, y1, z0, z1);
    double total = totalPair.first;
    double err2 = totalPair.second;
    
    // Stop conditions
    bool tooSmallToSplit =
      ((x1 - x0 + 1) < 2 * minBinsX) &&
      ((y1 - y0 + 1) < 2 * minBinsY) &&
      ((z1 - z0 + 1) < 2 * minBinsZ);
    
    if (total <= targetContent || total <= minBlockContent || tooSmallToSplit) {
      out.push_back({x0, x1, y0, y1, z0, z1, total, err2});
      return;
    }
    
    SplitCandidate best = FindBestSplit(x0, x1, y0, y1, z0, z1, minBinsX, minBinsY, minBinsZ);
    
    if (!best.valid) {
      out.push_back({x0, x1, y0, y1, z0, z1, total, err2});
      return;
    }
    
    if (best.axis == 'x') {
      Recurse(x0, best.split, y0, y1, z0, z1,
	      targetContent, minBinsX, minBinsY, minBinsZ, minBlockContent, out);
      Recurse(best.split + 1, x1, y0, y1, z0, z1,
	      targetContent, minBinsX, minBinsY, minBinsZ, minBlockContent, out);
    }
    else if (best.axis == 'y') {
      Recurse(x0, x1, y0, best.split, z0, z1,
	      targetContent, minBinsX, minBinsY, minBinsZ, minBlockContent, out);
      Recurse(x0, x1, best.split + 1, y1, z0, z1,
	      targetContent, minBinsX, minBinsY, minBinsZ, minBlockContent, out);
    }
    else {
      Recurse(x0, x1, y0, y1, z0, best.split,
	      targetContent, minBinsX, minBinsY, minBinsZ, minBlockContent, out);
      Recurse(x0, x1, y0, y1, best.split + 1, z1,
	      targetContent, minBinsX, minBinsY, minBinsZ, minBlockContent, out);
    }
  }
};

void AddaptiveTH3RadlIrebin(TString VolName ="FSTW", TString HistName = "RadlI") { 
  TH3F *No = (TH3F *) gDirectory->Get("No");
  if (! No) return;
  if (VolName != "") {HistName += "_"; HistName += VolName;}
  TH3F *Dens = (TH3F *) gDirectory->Get(HistName);
  double target = 1e-2;
  
  AdaptiveRebinner3D rebinner(No,Dens);
  auto blocks = rebinner.PartitionByTarget(
					   target,   // target content per merged block
					   1,        // min bins in X per child
					   1,        // min bins in Y per child
					   1,        // min bins in Z per child
					   0.0       // minimum content stop threshold
					   );
  
  AdaptiveRebinner3D::PrintBlocks(Dens, blocks);
  
  std::cout << "Requested target/block = " << target << "\n";
}
  
