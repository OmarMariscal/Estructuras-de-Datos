#ifndef __MENU_H__
#define __MENU_H__

#include <iostream>

#include "configure.hpp"
#include "ownexceptions.hpp"
#include "sortingbenchmark.hpp"

class Menu {
 private:
  SortingBenchmark& comparator;

  void enterToContinue();
  int readInteger(std::string, const int&, const int&);
  char readChar(const std::string&, const char*);
  bool handleOption(const char&);
  std::string windowHeader(const int&, const std::string&) const;

  void invalidOption();

  void mainMenu();

  void runSingleBenchmark(std::string);
  void runAllBenchmarks();

 public:
  Menu();
  Menu(SortingBenchmark&);
  Menu(const Menu&);
};

#endif  // __MENU_H__