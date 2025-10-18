#ifndef __MENU_H__
#define __MENU_H__

#include <string>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <thread>
#include <chrono>

#include "basemenu.hpp"
#include "ownexceptions.hpp"
#include "list.hpp"
#include "recipe.hpp"
#include "configure.hpp"
#include "ingredientMenu.hpp"
#include "proceduremenu.hpp"

class Menu : protected BaseMenu{
    private:
        List<Recipe>& recipeBook;
        std::string sortedBy = "id";
        bool modify = false;

        bool handleOption(const std::string&);
        void showStartupAnimation(int duration_ms = 2000,
                                bool showProgressBar = true,
                                const std::string& alumno = "Omar Mariscal",
                                const std::string& profesor = "Alfredo Gutiérrez",
                                const std::string& materia = " Estructuras de Datos",
                                const std::string& fecha = Date().toString()) const;

        void insertSortedDataByCategory(const Recipe&);

        //Pantallass
            //Pantallas Intermedias
            Recipe* searcher(const std::string&, int&);

            //Pantallas Principales
        void addRecipe();
        void deleteRecipe();
        void editRecipe();
        void showRecipes();
        void searchMenu();
        void sortRecipes();
        void saveToDisk();
        void readFromDisk();
        void exportRecipe();
        void exitMenu();
        void mainMenu() override;
    public:
        //Constructores
        Menu();
        Menu(const Menu&);
        Menu(List<Recipe>&, const std::string&, const bool&);
};


#endif // __MENU_H__