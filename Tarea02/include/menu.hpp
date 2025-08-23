#ifndef __MENU_H__
#define __MENU_H__

#include <iostream>
#include <iomanip>

#include "utilities.hpp"
#include "inventory.hpp"

class Menu{
    private:
        Inventory inventory;

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

#endif // __MENU_H__