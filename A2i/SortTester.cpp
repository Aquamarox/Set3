#include "SortTester.h"
#include "Sorts.h"
#include <chrono>
#include <fstream>
#include <algorithm>
#include <functional>
#include <numeric>

SortTester::SortTester(const size_t repetitions) : Repetitions(repetitions) {
}

std::vector<long long> SortTester::RunMultipleTrials(const std::vector<int> &arr,
                                                     const std::function<void(std::vector<int> &)> &sortFunc) const {
  std::vector<long long> results;
  results.reserve(Repetitions);
  for (size_t run = 0; run < Repetitions; ++run) {
    std::vector<int> copy = arr;
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(copy);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    results.push_back(msec);
  }
  return results;
}

long long SortTester::ComputeMean(const std::vector<long long> &values) {
  const long long sum = std::accumulate(values.begin(), values.end(), 0ll);
  return sum / static_cast<long long>(values.size());
}

long long SortTester::ComputeMedian(std::vector<long long> values) {
  std::ranges::sort(values);
  const size_t n = values.size();
  if (n % 2 == 1) {
    return values[n / 2];
  }
  return (values[n / 2 - 1] + values[n / 2]) / 2;
}

void SortTester::RunStandardMergeTest(const ArrayGenerator &generator, const std::vector<size_t> &sizes,
                                      const std::string &outCsvPath, const ArrayGenerator::Type genType, const int valueMin,
                                      const int valueMax) const {
  std::ofstream out(outCsvPath);
  out << "Size,MeanMs,MedianMs\n";
  constexpr size_t maxSize = 100000;
  const std::vector<int> maxArr = generator.GenerateMaxArray(maxSize, genType, valueMin, valueMax);

  for (const size_t size : sizes) {
    std::vector<int> arr = generator.GetPrefix(maxArr, size);
    auto results = RunMultipleTrials(arr, [](std::vector<int> &v) { Sorts::MergeSortStandard(v); });
    const long long mean = ComputeMean(results);
    const long long median = ComputeMedian(results);
    out << size << "," << mean << "," << median << "\n";
  }
  out.close();
}

void SortTester::RunHybridMergeInsertionTest(const ArrayGenerator &generator, const std::vector<size_t> &sizes,
                                             const std::vector<size_t> &thresholds, const std::string &outCsvPath,
                                             const ArrayGenerator::Type genType, const int valueMin, const int valueMax) const {
  std::ofstream out(outCsvPath);
  out << "Threshold,Size,MeanMs,MedianMs\n";
  constexpr size_t maxSize = 100000;
  const std::vector<int> maxArr = generator.GenerateMaxArray(maxSize, genType, valueMin, valueMax);

  for (size_t threshold : thresholds) {
    for (const size_t size : sizes) {
      std::vector<int> arr = generator.GetPrefix(maxArr, size);
      auto results =
          RunMultipleTrials(arr, [threshold](std::vector<int> &v) { Sorts::MergeInsertionHybrid(v, threshold); });
      const long long mean = ComputeMean(results);
      const long long median = ComputeMedian(results);
      out << threshold << "," << size << "," << mean << "," << median << "\n";
    }
  }
  out.close();
}
