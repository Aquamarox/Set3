#include "Sorts.h"
#include <vector>
#include <algorithm>

namespace Sorts {

static void Merge(std::vector<int> &A, std::vector<int> &temp, const size_t left, const size_t mid,
                  const size_t right) {
  size_t i = left;
  size_t j = mid + 1;
  size_t k = left;
  while (i <= mid && j <= right) {
    if (A[i] <= A[j]) {
      temp[k++] = A[i++];
    } else {
      temp[k++] = A[j++];
    }
  }
  while (i <= mid) {
    temp[k++] = A[i++];
  }
  while (j <= right) {
    temp[k++] = A[j++];
  }
  for (size_t idx = left; idx <= right; ++idx) {
    A[idx] = temp[idx];
  }
}

static void MergeSortRec(std::vector<int> &A, std::vector<int> &temp, const size_t left, const size_t right) {
  if (left >= right) {
    return;
  }
  const size_t mid = left + (right - left) / 2;
  MergeSortRec(A, temp, left, mid);
  MergeSortRec(A, temp, mid + 1, right);
  Merge(A, temp, left, mid, right);
}

void MergeSortStandard(std::vector<int> &A) {
  if (A.empty()) {
    return;
  }
  std::vector<int> temp;
  temp.resize(A.size());
  MergeSortRec(A, temp, 0, A.size() - 1);
}

void InsertionSort(std::vector<int> &A, const size_t left, const size_t right) {
  for (size_t i = left + 1; i <= right; ++i) {
    const int key = A[i];
    size_t j = i;
    while (j > left && A[j - 1] > key) {
      A[j] = A[j - 1];
      --j;
    }
    A[j] = key;
  }
}

static void MergeSortHybridRec(std::vector<int> &A, std::vector<int> &temp, const size_t left, const size_t right,
                               const size_t threshold) {
  if (left >= right) {
    return;
  }
  size_t segmentSize = right - left + 1;
  if (segmentSize <= threshold) {
    InsertionSort(A, left, right);
    return;
  }
  const size_t mid = left + (right - left) / 2;
  MergeSortHybridRec(A, temp, left, mid, threshold);
  MergeSortHybridRec(A, temp, mid + 1, right, threshold);
  Merge(A, temp, left, mid, right);
}

void MergeInsertionHybrid(std::vector<int> &A, const size_t threshold) {
  if (A.empty()) {
    return;
  }
  std::vector<int> temp;
  temp.resize(A.size());
  MergeSortHybridRec(A, temp, 0, A.size() - 1, threshold);
}

}  // namespace Sorts
