/**
 * Solution to https://open.kattis.com/problems/cordonbleu using Hungarian
 * algorithm.
 */

#include <cassert>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
#if 0
/**
 * Sets a = min(a, b)
 * @return true if b < a
 */
template <class T> bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }

/**
 * Given J jobs and W workers (J <= W), computes the minimum cost to assign each
 * prefix of jobs to distinct workers.
 *
 * @tparam T a type large enough to represent integers on the order of J *
 * max(|C|)
 * @param C a matrix of dimensions JxW such that C[j][w] = cost to assign j-th
 * job to w-th worker (possibly negative)
 *
 * @return a vector of length J, with the j-th entry equaling the minimum cost
 * to assign the first (j+1) jobs to distinct workers
 */
template <class T> vector<T> hungarian(const vector<vector<T>> &C) {
    const int J = (int)size(C), W = (int)size(C[0]);
    assert(J <= W);
    // job[w] = job assigned to w-th worker, or -1 if no job assigned
    // note: a W-th worker was added for convenience
    vector<int> job(W + 1, -1);
    vector<T> ys(J), yt(W + 1);  // potentials
    // -yt[W] will equal the sum of all deltas
    vector<T> answers;
    const T inf = numeric_limits<T>::max();
    for (int j_cur = 0; j_cur < J; ++j_cur) {  // assign j_cur-th job
        int w_cur = W;
        job[w_cur] = j_cur;
        // min reduced cost over edges from Z to worker w
        vector<T> min_to(W + 1, inf);
        vector<int> prv(W + 1, -1);  // previous worker on alternating path
        vector<bool> in_Z(W + 1);    // whether worker is in Z
        while (job[w_cur] != -1) {   // runs at most j_cur + 1 times
            in_Z[w_cur] = true;
            const int j = job[w_cur];
            T delta = inf;
            int w_next;
            for (int w = 0; w < W; ++w) {
                if (!in_Z[w]) {
                    if (ckmin(min_to[w], C[j][w] - ys[j] - yt[w]))
                        prv[w] = w_cur;
                    if (ckmin(delta, min_to[w])) w_next = w;
                }
            }
            // delta will always be nonnegative,
            // except possibly during the first time this loop runs
            // if any entries of C[j_cur] are negative
            for (int w = 0; w <= W; ++w) {
                if (in_Z[w]) ys[job[w]] += delta, yt[w] -= delta;
                else min_to[w] -= delta;
            }
            w_cur = w_next;
        }
        // update assignments along alternating path
        for (int w; w_cur != W; w_cur = w) job[w_cur] = job[w = prv[w_cur]];
        answers.push_back(-yt[W]);
    }
    return answers;
}

/**
 * Sanity check: https://en.wikipedia.org/wiki/Hungarian_algorithm#Example
 * First job (5):
 *   clean bathroom: Bob -> 5
 * First + second jobs (9):
 *   clean bathroom: Bob -> 5
 *   sweep floors: Alice -> 4
 * First + second + third jobs (15):
 *   clean bathroom: Alice -> 8
 *   sweep floors: Carol -> 4
 *   wash windows: Bob -> 3
 */
void sanity_check_hungarian() {
    vector<vector<int>> costs{{8, 5, 9}, {4, 2, 4}, {7, 3, 8}};
    assert((hungarian(costs) == vector<int>{5, 9, 15}));
    cerr << "Sanity check passed.\n";
}

// solves https://open.kattis.com/problems/cordonbleu
void cordon_bleu() {
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> B(N), C(M);
    vector<pair<int, int>> bottles(N), couriers(M);
    for (auto &b : bottles) cin >> b.first >> b.second;
    for (auto &c : couriers) cin >> c.first >> c.second;
    pair<int, int> rest;
    cin >> rest.first >> rest.second;
    vector<vector<int>> costs(N, vector<int>(N + M - 1));
    auto dist = [&](pair<int, int> x, pair<int, int> y) {
        return abs(x.first - y.first) + abs(x.second - y.second);
    };
    for (int b = 0; b < N; ++b) {
        for (int c = 0; c < M; ++c) {  // courier -> bottle -> restaurant
            costs[b][c] =
                dist(couriers[c], bottles[b]) + dist(bottles[b], rest);
        }
        for (int _ = 0; _ < N - 1; ++_) {  // restaurant -> bottle -> restaurant
            costs[b][_ + M] = 2 * dist(bottles[b], rest);
        }
    }
    cout << hungarian(costs).back() << "\n";
}

int main() {
    sanity_check_hungarian();
    cordon_bleu();
}
#else
template <class T> vector<T> hungarian(const vector<vector<T>> &C) {
    const int J = (int)size(C), W = (int)size(C[0]);
    assert(J <= W);
    // job[w] = job assigned to w-th worker, or -1 if no job assigned
    // note: a W-th worker was added for convenience
    vector<int> job(W + 1, -1);
    vector<T> h(W);  // Johnson potentials
    vector<T> answers;
    T ans_cur = 0;
    const T inf = numeric_limits<T>::max();
    // assign j_cur-th job using Dijkstra with potentials
    for (int j_cur = 0; j_cur < J; ++j_cur) {
        int w_cur = W;  // unvisited worker with minimum distance
        job[w_cur] = j_cur;
        vector<T> dist(W + 1, inf);  // Johnson-reduced distances
        dist[W] = 0;
        vector<bool> vis(W + 1);     // whether visited yet
        vector<int> prv(W + 1, -1);  // previous worker on shortest path
        while (job[w_cur] != -1) {   // Dijkstra step: pop min worker from heap
            T min_dist = inf;
            vis[w_cur] = true;
            int w_next = -1;  // next unvisited worker with minimum distance
            // consider extending shortest path by w_cur -> job[w_cur] -> w
            for (int w = 0; w < W; ++w) {
                if (!vis[w]) {
                    // sum of reduced edge weights w_cur -> job[w_cur] -> w
                    T edge = C[job[w_cur]][w] - h[w];
                    if (w_cur != W) {
                        edge -= C[job[w_cur]][w_cur] - h[w_cur];
                        assert(edge >= 0);  // consequence of Johnson potentials
                    }
                    if (ckmin(dist[w], dist[w_cur] + edge)) prv[w] = w_cur;
                    if (ckmin(min_dist, dist[w])) w_next = w;
                }
            }
            w_cur = w_next;
        }
        for (int w = 0; w < W; ++w) {  // update potentials
            ckmin(dist[w], dist[w_cur]);
            h[w] += dist[w];
        }
        ans_cur += h[w_cur];
        for (int w; w_cur != W; w_cur = w) job[w_cur] = job[w = prv[w_cur]];
        answers.push_back(ans_cur);
    }
    return answers;
}
#endif
