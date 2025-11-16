#include "QuickSortRecursive.h"
#include <algorithm>

void QuickSortRecursive::Sort(std::vector<int>& array) {
  QuickSortRecursive instance;
  instance.QuickSort(array, 0, static_cast<int>(array.size()) - 1);
}

void QuickSortRecursive::QuickSort(std::vector<int>& array, const int left, const int right) {
  if (left >= right) {
    return;
  }
  const int pivotIndex = RandomPivot(left, right);
  const int pivotValue = array[pivotIndex];
  std::swap(array[pivotIndex], array[right]);

  int storeIndex = left;
  for (int i = left; i <= right - 1; ++i) {
    if (array[i] < pivotValue) {
      std::swap(array[i], array[storeIndex]);
      ++storeIndex;
    }
  }
  std::swap(array[storeIndex], array[right]);

  QuickSort(array, left, storeIndex - 1);
  QuickSort(array, storeIndex + 1, right);
}

int QuickSortRecursive::RandomPivot(const int left, const int right) {
  std::uniform_int_distribution dist(left, right);
  return dist(rng);
}
