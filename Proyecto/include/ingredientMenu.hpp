#ifndef __INGREDIENTMENU_H__
#define __INGREDIENTMENU_H__

#include <sstream>
#include <string>

#include "basemenu.hpp"
#include "ingredient.hpp"
#include "list.hpp"

class IngredientMenu : protected BaseMenu {
 private:
  List<Ingredient, Configure::maximunIngredientSize>& ingredientList;
  std::string recipeName;

 public:
  void addIngredients();
  void deleteIngredients();
  void modifyIngredient();

  IngredientMenu();
  IngredientMenu(List<Ingredient, Configure::maximunIngredientSize>&,
                 const std::string&);
  IngredientMenu(const IngredientMenu&);

  void mainMenu();
};

#endif  // __INGREDIENTMENU_H__