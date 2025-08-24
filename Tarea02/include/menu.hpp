#ifndef __MENU_H__
#define __MENU_H__

#include <iomanip>  //Para hacer más estéticos las impresiones
#include <iostream>

#include "inventory.hpp"
#include "utilities.hpp"

class Menu {
 private:
  Inventory
      inventory;  // Tiene de parámetros un objeto de la clase inventario. Al
                  // tenerlo de atributo, facilita el acceso a sus métodos

  // Pantallas del Programa
  void mainMenu();
  void newProduct();
  void increaseStock();
  void decreaseStock();
  void checkInventory();
  void searchProduct();
  void exitScreen();

 public:
  Menu();
};

#endif  // __MENU_H__