#ifndef __SORTINGBENCHMARK_H__
#define __SORTINGBENCHMARK_H__

#include <chrono>
#include <iostream>
#include <random>
#include <string>

#include "benchmarkresult.hpp"
#include "configure.hpp"
#include "integer.hpp"
#include "list.hpp"

class SortingBenchmark {
 private:
  List<Integer, ListConfigure::ARRAYSIZE> originalList;
  List<Integer, ListConfigure::ARRAYSIZE> workingList;
  List<BenchMarkResult, ListConfigure::NumberAlgorithms> results;

  template <typename F>
  std::chrono::duration<double, std::milli> measureTime(F&&);

 public:
  SortingBenchmark();
  SortingBenchmark(
      const List<Integer, ListConfigure::ARRAYSIZE>&,
      const List<Integer, ListConfigure::ARRAYSIZE>&,
      const List<BenchMarkResult, ListConfigure::NumberAlgorithms>&);
  SortingBenchmark(const SortingBenchmark&);

  void generateRandomData(const int& = RandomConfigure::minimunRand,
                          const int& = RandomConfigure::maximunRand);

  void resetWorkingList();
  void clearResults();

  List<Integer, ListConfigure::ARRAYSIZE>& getOriginalList();
  List<Integer, ListConfigure::ARRAYSIZE>& getWorkingList();
  List<BenchMarkResult, ListConfigure::NumberAlgorithms>& getResults();

  // BenchMarck Individual
  template <typename SortFunc>
  BenchMarkResult runSingleBenchmark(const std::string&, SortFunc);

  void runAllBenchmarks();

  std::string getResultsTable() const;
  std::string getSingleTable(const BenchMarkResult&);

  SortingBenchmark& operator=(const SortingBenchmark&);
};

template <typename F>
std::chrono::duration<double, std::milli> SortingBenchmark::measureTime(
    F&& sortFunction) {
  auto start = std::chrono::high_resolution_clock::now();
  sortFunction();
  auto end = std::chrono::high_resolution_clock::now();
  return end - start;
}

template <typename SortFunc>
BenchMarkResult SortingBenchmark::runSingleBenchmark(
    const std::string& algorithmName,
    SortFunc sortFunc) {
  resetWorkingList();
  auto duration = this->measureTime([&]() { sortFunc(this->workingList); });
  BenchMarkResult result(algorithmName, duration);
  try {
    this->results.insertElement(result, this->results.getLastPosition() + 1);
  } catch (const DataContainersExceptions::MemoryDeficiency&
               ex) {  // Si el historial de resultados está lleno, lo vaciamos y
                      // añadimos el resultado
    this->clearResults();
    this->results.insertElement(result, this->results.getLastPosition() + 1);
  }
  return result;
}
#endif  // __SORTINGBENCHMARK_H__