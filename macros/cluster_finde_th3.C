#include <TH3D.h>
#include <TRandom3.h>
#include <TMath.h>

#include <vector>
#include <queue>
#include <tuple>
#include <iostream>
#include <cmath>

struct Voxel {
    int ix, iy, iz;
};

struct Cluster3D {
    std::vector<Voxel> voxels;
    double sumContent = 0.0;
    double xw = 0.0;
    double yw = 0.0;
    double zw = 0.0;

    double xMean() const { return (sumContent > 0) ? xw / sumContent : 0.0; }
    double yMean() const { return (sumContent > 0) ? yw / sumContent : 0.0; }
    double zMean() const { return (sumContent > 0) ? zw / sumContent : 0.0; }
};

bool IsInside(const TH3D* h, int ix, int iy, int iz)
{
    return ix >= 1 && ix <= h->GetNbinsX() &&
           iy >= 1 && iy <= h->GetNbinsY() &&
           iz >= 1 && iz <= h->GetNbinsZ();
}

std::vector<std::tuple<int,int,int>> BuildNeighborOffsets(int connectivity)
{
    std::vector<std::tuple<int,int,int>> offsets;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dz = -1; dz <= 1; ++dz) {
                if (dx == 0 && dy == 0 && dz == 0) continue;

                int manhattan = std::abs(dx) + std::abs(dy) + std::abs(dz);

                if (connectivity == 6 && manhattan == 1) {
                    offsets.emplace_back(dx, dy, dz);
                }
                else if (connectivity == 26) {
                    offsets.emplace_back(dx, dy, dz);
                }
            }
        }
    }

    return offsets;
}

std::vector<Cluster3D> FindClustersTH3(TH3D* h, double threshold = 1.0, int connectivity = 6)
{
    int nx = h->GetNbinsX();
    int ny = h->GetNbinsY();
    int nz = h->GetNbinsZ();

    std::vector<char> visited((nx + 1) * (ny + 1) * (nz + 1), 0);

    auto Index = [ny, nz](int ix, int iy, int iz) {
        return ix * (ny + 1) * (nz + 1) + iy * (nz + 1) + iz;
    };

    auto neighbors = BuildNeighborOffsets(connectivity);
    std::vector<Cluster3D> clusters;

    for (int ix = 1; ix <= nx; ++ix) {
        for (int iy = 1; iy <= ny; ++iy) {
            for (int iz = 1; iz <= nz; ++iz) {
                if (visited[Index(ix, iy, iz)]) continue;

                double c = h->GetBinContent(ix, iy, iz);
                if (c < threshold) continue;

                Cluster3D cluster;
                std::queue<Voxel> q;
                q.push({ix, iy, iz});
                visited[Index(ix, iy, iz)] = 1;

                while (!q.empty()) {
                    Voxel v = q.front();
                    q.pop();


                    double content = h->GetBinContent(v.ix, v.iy, v.iz);
                    if (content < threshold) continue;

                    cluster.voxels.push_back(v);
                    cluster.sumContent += content;

                    double x = h->GetXaxis()->GetBinCenter(v.ix);
                    double y = h->GetYaxis()->GetBinCenter(v.iy);
                    double z = h->GetZaxis()->GetBinCenter(v.iz);

                    cluster.xw += content * x;
                    cluster.yw += content * y;
                    cluster.zw += content * z;

                    for (const auto& off : neighbors) {
                        int dx, dy, dz;
                        std::tie(dx, dy, dz) = off;

                        int jx = v.ix + dx;
                        int jy = v.iy + dy;
                        int jz = v.iz + dz;

                        if (!IsInside(h, jx, jy, jz)) continue;
                        if (visited[Index(jx, jy, jz)]) continue;

                        if (h->GetBinContent(jx, jy, jz) >= threshold) {
                            visited[Index(jx, jy, jz)] = 1;
                            q.push({jx, jy, jz});
                        }
                    }
                }

                if (!cluster.voxels.empty()) {
                    clusters.push_back(cluster);
                }
            }
        }
    }

    return clusters;
}

void cluster_finder_th3()
{
    auto h = new TH3D("h", "3D clusters;X;Y;Z", 30, 0, 30, 30, 0, 30, 30, 0, 30);
    h->Sumw2();

    TRandom3 rng(1234);

    // Cluster 1
    for (int i = 0; i < 2000; ++i) {
        h->Fill(rng.Gaus(8, 1.5), rng.Gaus(10, 1.3), rng.Gaus(12, 1.2));
    }

    // Cluster 2
    for (int i = 0; i < 1800; ++i) {
        h->Fill(rng.Gaus(20, 1.8), rng.Gaus(18, 1.4), rng.Gaus(16, 1.5));
    }

    // Noise
    for (int i = 0; i < 200; ++i) {
        h->Fill(rng.Uniform(0, 30), rng.Uniform(0, 30), rng.Uniform(0, 30));
    }

    double threshold = 3.0;
    int connectivity = 6;

    auto clusters = FindClustersTH3(h, threshold, connectivity);

    std::cout << "Found " << clusters.size() << " clusters\n";
    for (size_t i = 0; i < clusters.size(); ++i) {
        const auto& c = clusters[i];
        std::cout
            << "Cluster " << i
            << " | voxels = " << c.voxels.size()
            << " | sumContent = " << c.sumContent
            << " | centroid = ("
            << c.xMean() << ", "
            << c.yMean() << ", "
            << c.zMean() << ")\n";
    }
}
