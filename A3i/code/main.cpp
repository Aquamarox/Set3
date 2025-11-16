#include "SortTester_A3i.h"
#include <iostream>
#include <fstream>

int main() {
  std::ofstream out("introsort_results.csv", std::ios::trunc);
  out << "distribution,size,runs,avg_quick_ms,avg_hybrid_ms\n";
  out.close();

  SortTester tester;
  tester.RunAllTests();

  std::cout << "Done" << std::endl;
  return 0;
}
