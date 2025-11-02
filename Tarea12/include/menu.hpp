#ifndef __MENU_H__
#define __MENU_H__

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

#include <basemenu.hpp>
#include "list.hpp"
#include "notationtransformer.hpp"
#include "ownexceptions.hpp"
#include "stringwrapped.hpp"

class Menu : BaseMenu {
 private:
  NotationTransformer& transformer;
  List<StringWrapper>& record;

  bool handleOption(const std::string&);

  void makeTranformation();
  void showRecord();
  void deleteRecords();
  void exitScreen();

 public:
  Menu();
  Menu(NotationTransformer&, List<StringWrapper>&);
  Menu(const Menu&);

  ~Menu();

  void mainMenu();
};

#endif  // __MENU_H__