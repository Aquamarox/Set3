#include "ArrayGenerator.h"
#include "SortTester.h"
#include <vector>
#include <iostream>

int main()
{
  const ArrayGenerator generator(1234);
  const SortTester tester(7);

  std::vector<size_t> sizes;
  for (size_t s = 500; s <= 100000; s += 100) {
    sizes.push_back(s);
  }

  const std::vector<size_t> thresholds = {5, 10, 20, 30, 50};

  tester.RunStandardMergeTest(generator, sizes, "merge_standard_random.csv", ArrayGenerator::Type::Random, 0, 6000);
  tester.RunHybridMergeInsertionTest(generator, sizes, thresholds, "merge_hybrid_random.csv", ArrayGenerator::Type::Random, 0, 6000);

  tester.RunStandardMergeTest(generator, sizes, "merge_standard_reverse.csv", ArrayGenerator::Type::Reverse, 0, 6000);
  tester.RunHybridMergeInsertionTest(generator, sizes, thresholds, "merge_hybrid_reverse.csv", ArrayGenerator::Type::Reverse, 0, 6000);

  tester.RunStandardMergeTest(generator, sizes, "merge_standard_almost.csv", ArrayGenerator::Type::AlmostSorted, 0, 6000);
  tester.RunHybridMergeInsertionTest(generator, sizes, thresholds, "merge_hybrid_almost.csv", ArrayGenerator::Type::AlmostSorted, 0, 6000);

  std::cout << "Done" << std::endl;
  return 0;
}