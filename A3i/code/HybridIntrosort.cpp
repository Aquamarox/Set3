#include "HybridIntrosort.h"
#include <algorithm>
#include <cmath>

void HybridIntrosort::Sort(std::vector<int>& array) {
  HybridIntrosort instance;
  const int depthLimit = 2 * static_cast<int>(std::log2(std::max(1, static_cast<int>(array.size()))));
  instance.IntroSort(array, 0, static_cast<int>(array.size()) - 1, depthLimit);
}

void HybridIntrosort::IntroSort(std::vector<int>& array, const int left, const int right, const int depthLimit) {
  constexpr int insertionSortThreshold = 16;

  if (left >= right) {
    return;
  }
  const int size = right - left + 1;
  if (size <= insertionSortThreshold) {
    InsertionSort(array, left, right);
    return;
  }
  if (depthLimit == 0) {
    HeapSortRange(array, left, right);
    return;
  }

  const int pivotIndex = MedianOfThree(array, left, right);
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

  IntroSort(array, left, storeIndex - 1, depthLimit - 1);
  IntroSort(array, storeIndex + 1, right, depthLimit - 1);
}

void HybridIntrosort::InsertionSort(std::vector<int>& array, const int left, const int right) {
  for (int i = left + 1; i <= right; ++i) {
    const int key = array[i];
    int j = i - 1;
    while (j >= left && array[j] > key) {
      array[j + 1] = array[j];
      --j;
    }
    array[j + 1] = key;
  }
}

void HybridIntrosort::HeapSortRange(std::vector<int>& array, const int left, const int right) {
  const int length = right - left + 1;
  for (int i = left + (length / 2) - 1; i >= left; --i) {
    Heapify(array, length, i, left);
  }
  for (int i = right; i > left; --i) {
    std::swap(array[left], array[i]);
    Heapify(array, i - left, left, left);
  }
}

void HybridIntrosort::Heapify(std::vector<int>& array, const int heapSize, const int rootIndex, const int offset) {
  int largest = rootIndex;
  const int leftChild = offset + 2 * (rootIndex - offset) + 1;
  const int rightChild = offset + 2 * (rootIndex - offset) + 2;

  if (leftChild < offset + heapSize && array[leftChild] > array[largest]) {
    largest = leftChild;
  }
  if (rightChild < offset + heapSize && array[rightChild] > array[largest]) {
    largest = rightChild;
  }
  if (largest != rootIndex) {
    std::swap(array[rootIndex], array[largest]);
    Heapify(array, heapSize, largest, offset);
  }
}

int HybridIntrosort::MedianOfThree(const std::vector<int>& array, const int left, const int right) {
  const int mid = left + ((right - left) / 2);
  const int a = array[left];
  const int b = array[mid];
  int c = array[right];

  if ((a <= b && b <= c) || (c <= b && b <= a)) {
    return mid;
  }
  if ((b <= a && a <= c) || (c <= a && a <= b)) {
    return left;
  }
  return right;
}
