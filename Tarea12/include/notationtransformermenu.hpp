#ifndef __NOTATIONTRANSFORMERMENU_H__
#define __NOTATIONTRANSFORMERMENU_H__

#include <iomanip>
#include <iostream>
#include <sstream>

#include "stringwrapped.hpp"
#include "list.hpp"
#include "notationtransformer.hpp"
#include "ownexceptions.hpp"

class NotationTransformerMenu {
 private:
  NotationTransformer& transformer;
  List<StringWrapper>& record;

  int readInteger(std::string, const int&, const int&);
  std::string windowHeader(const int&, const std::string&);
  void enterToContinue();
  bool handleOption(const std::string&);

  void makeTranformation();
  void showRecord();
  void deleteRecords();
  void exitScreen();

 public:
  NotationTransformerMenu();
  NotationTransformerMenu(NotationTransformer&, List<StringWrapper>&);
  NotationTransformerMenu(const NotationTransformerMenu&);

  void mainMenu();
};

#endif  // __NOTATIONTRANSFORMERMENU_H__