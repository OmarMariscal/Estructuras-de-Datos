#ifndef __MENU_H__
#define __MENU_H__

#include <string>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <thread>
#include <chrono>

#include "ownexceptions.hpp"
#include "list.hpp"
#include "recipe.hpp"
#include "configure.hpp"

class Menu{
    private:
        List<Recipe>& recipeBook;
        std::string sortedBy = "id";
        bool modify = false;

        //Métodos de Entrada para la Entrada de Datos:
        int readInteger(std::string, const int&, const int&);
        float readFloat(const std::string&, const float&, const float&);
        Name readName(std::string, const std::string& = "Ingrese el Nombre: ", const std::string& = "Ingrese el Apellido");
        std::string readLinePrompt(const std::string&, bool = false);
        char readChar(const std::string&, const std::string&);
        Category readCategory(const std::string&);
        std::string standarString(std::string);
        std::string clearColor(const std::string&);

        //Métodos Auxiliares
        void menuIngredints(List<Ingredient, Configure::maximunIngredientSize>*, const std::string&);
        void addIngredients(List<Ingredient, Configure::maximunIngredientSize>*, const std::string&);
        void deleteIngredients(List<Ingredient, Configure::maximunIngredientSize>*, const std::string&);
        void modifyIngredient(List<Ingredient, Configure::maximunIngredientSize>*, const std::string&);

        void menuPreocedure(List<StringWrapper, Configure::maximunIngredientSize>*, const std::string&);
        void addProcedure(List<StringWrapper, Configure::maximunIngredientSize>*, const std::string&);
        void deleteProcedure(List<StringWrapper, Configure::maximunIngredientSize>*, const std::string&);
        void modifyProcedure(List<StringWrapper, Configure::maximunIngredientSize>*, const std::string&);

        //Métodos Auxiliares
        void enterToContinue();
        std::string categoryToString(const Category&) const;
        void errorMessage(const std::string&, const int& = Configure::predeterminatedSizeWindows);
        bool handleOption(const std::string&);
        std::string windowHeader(const std::string&, const int& = Configure::predeterminatedSizeWindows,  const std::string& = "═") const;
        std::string divider( const std::string& = "═", const int& = Configure::predeterminatedSizeWindows) const;
        std::string insertColorText(std::string, std::string);
        std::string centerText(std::string, const int& = Configure::predeterminatedSizeWindows);
        void cleanScreen();

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
        void mainMenu();
    public:
        //Constructores
        Menu();
        Menu(const Menu&);
        Menu(List<Recipe>&, const std::string&, const bool&);
};


#endif // __MENU_H__