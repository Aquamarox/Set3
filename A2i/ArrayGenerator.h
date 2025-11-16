#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include <cstddef>

class ArrayGenerator {
 public:
  enum class Type { Random, Reverse, AlmostSorted };

  explicit ArrayGenerator(size_t seed = 5489u);

  std::vector<int> GenerateMaxArray(size_t maxSize, Type genType, int valueMin, int valueMax,
                                    double almostSortedSwapFraction = 0.001) const;
  static std::vector<int> GetPrefix(const std::vector<int> &source, size_t length);

 private:
  std::mt19937 Engine;
};
