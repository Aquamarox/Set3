#pragma once
#include <vector>
#include <string>
#include "ArrayGenerator.h"
#include <functional>

class SortTester {
public:
  explicit SortTester(size_t repetitions = 7);

  void RunStandardMergeTest(const ArrayGenerator &generator, const std::vector<size_t> &sizes, const std::string &outCsvPath, ArrayGenerator::Type genType, int valueMin, int valueMax) const;
  void RunHybridMergeInsertionTest(const ArrayGenerator &generator, const std::vector<size_t> &sizes, const std::vector<size_t> &thresholds, const std::string &outCsvPath, ArrayGenerator::Type genType, int valueMin, int valueMax) const;

private:
  size_t Repetitions;
  std::vector<long long> RunMultipleTrials(const std::vector<int> &arr, const std::function<void(std::vector<int> &)> &sortFunc) const;
  static long long ComputeMean(const std::vector<long long> &values);
  static long long ComputeMedian(std::vector<long long> values);
};
