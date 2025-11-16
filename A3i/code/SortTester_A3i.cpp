#include "SortTester_A3i.h"
#include "QuickSortRecursive.h"
#include "HybridIntrosort.h"
#include <fstream>
#include <random>
#include <algorithm>
#include <chrono>

void SortTester::RunAllTests() {
  std::vector<int> sizes;

  for (int s = 500; s <= 100000; s += 500) {
    sizes.push_back(s);
  }

  const std::vector<std::string> distributions{"random", "sorted", "reversed", "nearly_sorted", "few_unique"};

    for (const std::string& distribution : distributions) {
        for (const int size : sizes) {
        constexpr int runsPerCase = 5;
      std::vector<double> resultsQuick;
            std::vector<double> resultsHybrid;

            for (int run = 0; run < runsPerCase; ++run) {
                std::vector<int> data = GenerateData(size, distribution);
                std::vector<int> copyForHybrid = data;

                double tQuick = MeasureSort(data, [](std::vector<int>& a) { QuickSortRecursive::Sort(a); });
                double tHybrid = MeasureSort(copyForHybrid, [](std::vector<int>& a) { HybridIntrosort::Sort(a); });

                resultsQuick.push_back(tQuick);
                resultsHybrid.push_back(tHybrid);
            }

            const double avgQuick = Average(resultsQuick);
            const double avgHybrid = Average(resultsHybrid);

            AppendCsvLine(distribution, size, runsPerCase, avgQuick, avgHybrid);
        }
    }
}

double SortTester::MeasureSort(std::vector<int>& array, std::function<void(std::vector<int>&)> sortFunction) {
    const auto start = std::chrono::high_resolution_clock::now();
    sortFunction(array);
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}

std::vector<int> SortTester::GenerateData(const int size, const std::string& distribution) {
    std::vector<int> result(size);
    for (int i = 0; i < size; ++i) {
        result[i] = i;
    }

    std::mt19937 rng{std::random_device{}()};

    if (distribution == "random") {
        for (int i = 0; i < size; ++i) {
            std::uniform_int_distribution dist(0, size);
            result[i] = dist(rng);
        }
    } else if (distribution == "reversed") {
        std::ranges::reverse(result);
    } else if (distribution == "nearly_sorted") {
        for (int k = 0; k < std::max(1, size / 100); ++k) {
            const int i = std::uniform_int_distribution(0, size - 1)(rng);
            const int j = std::uniform_int_distribution(0, size - 1)(rng);
            std::swap(result[i], result[j]);
        }
    } else if (distribution == "few_unique") {
        const int distinct = std::max(2, size / 100);
        for (int i = 0; i < size; ++i) {
            result[i] = i % distinct;
        }
        std::ranges::shuffle(result, rng);
    }

    return result;
}

double SortTester::Average(const std::vector<double>& values) {
    double sum = 0.0;
    for (const double x : values) {
        sum += x;
    }
    return sum / static_cast<double>(values.size());
}

void SortTester::AppendCsvLine(const std::string& distribution, const int size, const int runs, const double avgQuick, const double avgHybrid) {
    std::ofstream out("introsort_results.csv", std::ios::app);
    if (!out.is_open()) {
        return;
    }
    out << distribution << ',' << size << ',' << runs << ',' << avgQuick << ',' << avgHybrid << '\n';
}
