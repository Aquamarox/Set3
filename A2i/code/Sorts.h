#pragma once
#include <vector>
#include <cstddef>

namespace Sorts {

void InsertionSort(std::vector<int> &A, size_t left, size_t right);
void MergeSortStandard(std::vector<int> &A);
void MergeInsertionHybrid(std::vector<int> &A, size_t threshold);

}
