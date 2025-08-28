#ifndef __MENU_H__
#define __MENU_H__

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>

class Menu{
    public:
    void pedirNombre();

    std::string bannerToString() const;
    void invalidCategory();
    void invalidString();
    void recipeNotFoundMessage();

        //Primera pantalla
    void showStartupAnimation(int duration_ms = 2000,
                              bool showProgressBar = true,
                              const std::string& alumno = "",
                              const std::string& profesor = "",
                              const std::string& materia = "",
                              const std::string& fecha = "") const;
        //Enrutamiento de opcioens
        void handleMainChoise(const int&);

        void showAllRecipes();
        void showRecipes();

        void showRecipesForCategory();
        void addRecipes();

        void searchRecipesByName();
        void searchRecipesByCategory();
        void modifyRecipe();
        void deleteRecipeByName();
        void clearAllRecipes();
        void orderRecipes();
        void saveRecipes();
        void readRecipes();

        std::string mainMenu() const;
    public:
        Menu();

};


#endif // __MENU_H__