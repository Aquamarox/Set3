#ifndef QUICKSORTRECURSIVE_H
#define QUICKSORTRECURSIVE_H

#include <vector>
#include <random>

class QuickSortRecursive {
 public:
  static void Sort(std::vector<int>& array);

 private:
  std::mt19937 rng{std::random_device{}()};

  void QuickSort(std::vector<int>& array, int left, int right);
  int RandomPivot(int left, int right);
};

#endif
