#ifndef __MENU_H__
#define __MENU_H__

#include "basemenu.hpp"
#include "avltree.hpp"
#include "integer.hpp"
#include "randnumgenerator.hpp"

class Menu : BaseMenu {
 private:
  AVLTree<Integer>& bST;

  bool warningOverWrite();
  bool handleOption(const std::string&);

  void fillTree();
  template <typename Route>
  void showRoute(const std::string&, Route);
  void showRange();
  void showHightSubTrees();
  void cleanTree();
  void exitScreen();

  void mainMenu();

 public:
  Menu();
  Menu(const Menu&);
  Menu(AVLTree<Integer>&);
};

// Método que toma como parámetro el toString del árbol
// Es genérica y podemos pasarle cualquier tipo de recorrido del árbol
// De esta manera, sintetizamos las tres funciones de recorrido en una sola.
template <typename Route>
void Menu::showRoute(const std::string& typeOfRoute, Route routeFunction) {
  this->cleanScreen();
  if (this->bST.isEmpty()) {
    this->errorMessage(
        "Aún no hay registros\nGenere valores aleatorios antes de imprimir una "
        "ruta");
    return;
  }

  cout << this->windowHeader("🛣️ RECORRIDO " + typeOfRoute + " DEL BST");
  cout << routeFunction();
  cout << this->divider("-");
  this->enterToContinue(false);
}

#endif  // __MENU_H__