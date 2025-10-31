#ifndef __INGREDIENTMENU_H__
#define __INGREDIENTMENU_H__

#include <string>
#include <sstream>

#include "simplelinkedlist.hpp"
#include "ingredient.hpp"
#include "basemenu.hpp"

class IngredientMenu : protected BaseMenu{
    private:
        SimpleLinkedList<Ingredient>& ingredientList;
        std::string recipeName;
    
    public:
        void addIngredients();
        void deleteIngredients();
        void modifyIngredient();
        
        IngredientMenu();
        IngredientMenu(SimpleLinkedList<Ingredient>&, const std::string&);
        IngredientMenu(const IngredientMenu&);

        void mainMenu();

};

#endif // __INGREDIENTMENU_H__