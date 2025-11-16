#include "ArrayGenerator.h"

ArrayGenerator::ArrayGenerator(const size_t seed) {
  Engine.seed(seed);
}

std::vector<int> ArrayGenerator::GenerateMaxArray(const size_t maxSize, const Type genType, const int valueMin,
                                                  const int valueMax, const double almostSortedSwapFraction) const {
  std::vector<int> result;
  result.resize(maxSize);

  if (genType == Type::Random) {
    std::uniform_int_distribution dist(valueMin, valueMax);
    for (size_t i = 0; i < maxSize; ++i) {
      result[i] = dist(const_cast<std::mt19937 &>(Engine));
    }
    return result;
  }

  if (genType == Type::Reverse) {
    for (size_t i = 0; i < maxSize; ++i) {
      result[i] = static_cast<int>(maxSize - i);
    }
    return result;
  }

  if (genType == Type::AlmostSorted) {
    for (size_t i = 0; i < maxSize; ++i) {
      result[i] = static_cast<int>(i);
    }
    size_t swaps = static_cast<size_t>(almostSortedSwapFraction * static_cast<double>(maxSize));
    if (swaps < 1) {
      swaps = 1;
    }
    std::uniform_int_distribution<size_t> distIndex(0, maxSize - 1);
    for (size_t k = 0; k < swaps; ++k) {
      const size_t i = distIndex(const_cast<std::mt19937 &>(Engine));
      const size_t j = distIndex(const_cast<std::mt19937 &>(Engine));
      std::swap(result[i], result[j]);
    }
    return result;
  }

  return result;
}

std::vector<int> ArrayGenerator::GetPrefix(const std::vector<int> &source, const size_t length) {
  std::vector<int> result;
  if (length > source.size()) {
    result = source;
    return result;
  }
  result.assign(source.begin(), source.begin() + static_cast<std::ptrdiff_t>(length));
  return result;
}
