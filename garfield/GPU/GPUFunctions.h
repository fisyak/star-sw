#ifndef G_GPUFUNCTIONS_H
#define G_GPUFUNCTIONS_H
#include <cstddef>
#include <vector>

#define checkCudaErrors(val) check_cuda((val), #val, __FILE__, __LINE__)

namespace Garfield {
void check_cuda(cudaError_t result, char const *const func,
                const char *const file, int const line);

template <typename SRC, typename DEST>
double CreateGPUObjectArrayFromVector(const std::vector<SRC> &vec_src,
                                      size_t &num, DEST &dest_arr) {
  double alloc{0};

  num = vec_src.size();
  checkCudaErrors(
      cudaMallocManaged(&(dest_arr), sizeof(DEST) * vec_src.size()));
  alloc += sizeof(DEST) * vec_src.size();

  for (std::size_t i = 0; i < vec_src.size(); i++) {
    alloc += vec_src[i]->CreateGPUTransferObject(dest_arr[i]);
  }

  return alloc;
}

template <typename T>
double CreateGPUArrayFromVector(const std::vector<T> &vec_src, int &num,
                                T *&dest_arr) {
  double alloc{0};

  num = vec_src.size();
  checkCudaErrors(cudaMallocManaged(&(dest_arr), sizeof(T) * vec_src.size()));
  alloc += sizeof(T) * vec_src.size();

  for (std::size_t i = 0; i < vec_src.size(); i++) {
    dest_arr[i] = vec_src[i];
  }

  return alloc;
}

template <typename T>
double CreateGPUArrayOfArraysFromVector(
    const std::vector<std::vector<T> > &vec_src, T **&dest_arr, int &num_idx,
    int *&idx_arr) {
  double alloc{0};
  checkCudaErrors(cudaMallocManaged(&(dest_arr), sizeof(T *) * vec_src.size()));
  alloc += sizeof(T *) * vec_src.size();
  checkCudaErrors(cudaMallocManaged(&idx_arr, sizeof(int) * vec_src.size()));
  alloc += sizeof(int) * vec_src.size();
  num_idx = vec_src.size();

  for (std::size_t i = 0; i < vec_src.size(); i++) {
    checkCudaErrors(
        cudaMallocManaged(&dest_arr[i], sizeof(T) * vec_src[i].size()));
    alloc += sizeof(T) * vec_src[i].size();
    for (std::size_t j = 0; j < vec_src[i].size(); j++) {
      dest_arr[i][j] = vec_src[i][j];
    }

    idx_arr[i] = vec_src[i].size();
  }

  return alloc;
}
}  // namespace Garfield

#endif
