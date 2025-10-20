#ifndef __PROCEDUREMENU_H__
#define __PROCEDUREMENU_H__

#include <sstream>
#include <string>

#include "basemenu.hpp"
#include "configure.hpp"
#include "list.hpp"
#include "ownexceptions.hpp"
#include "stringwrapped.hpp"

class ProcedureMenu : protected BaseMenu {
 private:
  List<StringWrapper, Configure::maximunIngredientSize>& process;
  std::string recipeName;

 public:
  ProcedureMenu();
  ProcedureMenu(List<StringWrapper, Configure::maximunIngredientSize>&,
                const std::string&);
  ProcedureMenu(const ProcedureMenu&);

  void mainMenu();
  void addProcedure();
  void deleteProcedure();
  void editProcedure();
};

#endif  // __PROCEDUREMENU_H__