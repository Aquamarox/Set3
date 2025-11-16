#ifndef SORTTESTER_A3I_H
#define SORTTESTER_A3I_H

#include <functional>
#include <vector>
#include <string>

class SortTester {
public:
  SortTester() = default;
 static void RunAllTests();

private:
  static double MeasureSort(std::vector<int>& array, std::function<void(std::vector<int>&)> sortFunction);
 static std::vector<int> GenerateData(int size, const std::string& distribution);
  static double Average(const std::vector<double>& values);
 static void AppendCsvLine(const std::string& distribution, int size, int runs, double avgQuick, double avgHybrid);
};

#endif
