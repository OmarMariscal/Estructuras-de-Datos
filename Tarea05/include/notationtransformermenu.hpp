#ifndef __NOTATIONTRANSFORMERMENU_H__
#define __NOTATIONTRANSFORMERMENU_H__

#include <iomanip>
#include <iostream>
#include <sstream>

#include "list.hpp"
#include "notationtransformer.hpp"
#include "ownexceptions.hpp"

class NotationTransformerMenu {
 private:
  NotationTransformer& transformer;
  List<std::string>& record;

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
  NotationTransformerMenu(NotationTransformer&, List<std::string>&);
  NotationTransformerMenu(const NotationTransformerMenu&);

  void mainMenu();
};

#endif  // __NOTATIONTRANSFORMERMENU_H__