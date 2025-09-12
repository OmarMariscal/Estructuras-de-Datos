#ifndef __RECIPE_H__
#define __RECIPE_H__

#include <iostream>
#include <string>
#include <sstream>

#include "category.hpp"
#include "list.hpp"
#include "ingredient.hpp"

class Recipe{
    private:
        std::string recipeName;
        Category category;
        int preparationTime; //¿Hacer una Clase?
        List<std::string> procedureList;
        List<Ingredient> ingredientList;
    public:
        Recipe();
        Recipe(const Recipe&);
        
        std::string getRecipeName() const;
        Category getCategory() const;
        int getPreparationTime() const;
        List<std::string> getProcedureList() const;
        List<Ingredient> getIngredientList() const;

        std::string toString() const;

        void setRecipeName(const std::string& );
        void setCategory(const Category&);
        void setPreparationTime(const int&);
        void setProcedureList(const List<std::string>&);
        void setIngredientList(const List<Ingredient>&);

        void addIngredient(const Ingredient&);
        void deleteIngredient(const Ingredient&);
        void clearIngredients();

        void addStepToProcedure(const std::string&);
        void deleteStepFromProcedure(const int&);
        void clearProcedure();

        bool operator == (const Recipe&);
        bool operator < (const Recipe&);
        bool operator > (const Recipe&);
        bool operator <= (const Recipe&);
        bool operator >= (const Recipe&);

        int compareByPreparationTime(const Ingredient&) const;
        static int compareToByPreparationTime(const Ingredient&, const Ingredient&);

        

        friend std::ostream& operator << (std::ostream&, const Ingredient&);
        friend std::istream& operator >> (std::istream&, Ingredient&);

        Recipe& operator = (const Recipe&);
};

#endif // __RECIPE_H__