#ifndef __RECIPEBOOK_H__
#define __RECIPEBOOK_H__

#include <string>

#include "list.hpp"
#include "recipe.hpp"

class RecipeBook{
    private:
        List<Recipe> recipes;
        std::string recipeBookName;
        std::string filePath;
        bool modify;
        int totalRecipes;

        void setModify();
        void updateTotalRecipes();
        bool isValidRecipe(const Recipe&);

    public:
        RecipeBook();
        RecipeBook(const RecipeBook&);
        RecipeBook(const List<Recipe>&, const std::string&, const std::string&, const bool&, const int&);
        
        //Getter's
        List<Recipe> getRecipes() const;
        std::string getRecipeBookName() const;
        std::string getFilePath() const;
        bool getModify() const;
        int getTotalRecipes() const;

        //Setter's
        void setRecipes(const List<Recipe>&);
        void setRecipeBookName(const std::string&);
        void setFilePath(const std::string&);
        void setTotalRecipes(const int&);

        //Algoritmicos
        void addRecipe(const Recipe&);
        void deleteRecipe(const Recipe&);
        void deleteRecipeByName(const Recipe&);

        Recipe searchRecipe(const Recipe&);
        Recipe searchRecipeByName(const Recipe&);

        //Ingredientes
        void addIngredientToRecipe(const Recipe&, const Ingredient&);
        void deleteIngredientFromRecipe(const Recipe&, const Ingredient&);
        void clearIngredientesFromRecipe(const Recipe&);

        void addStepToRecipe(const Recipe&, const std::string&);
        void deleteStepFromRecipe(const Recipe&, const int&);
        void clearSteptsFromRecipe(const Recipe&);


        //Ordenamiento
        void sortRecipesByName();
        void sortRecipesByPreparationTime();

        void deleteAllRecipes();
        
};


#endif // __RECIPEBOOK_H__