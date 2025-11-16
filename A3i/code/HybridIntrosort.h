#ifndef HYBRIDINTROSORT_H
#define HYBRIDINTROSORT_H

#include <vector>

class HybridIntrosort {
 public:
  static void Sort(std::vector<int>& array);

 private:
  static void IntroSort(std::vector<int>& array, int left, int right, int depthLimit);
  static void InsertionSort(std::vector<int>& array, int left, int right);
  static void HeapSortRange(std::vector<int>& array, int left, int right);
  static void Heapify(std::vector<int>& array, int heapSize, int rootIndex, int offset);
  static int MedianOfThree(const std::vector<int>& array, int left, int right);
};

#endif
