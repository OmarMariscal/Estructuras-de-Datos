#ifndef __RECIPE_H__
#define __RECIPE_H__

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

#include "../lib/nlohmann/json.hpp"

#include "category.hpp"
#include "list.hpp"
#include "ingredient.hpp"
#include "name.hpp"
#include "date.hpp"
#include "stringwrapped.hpp"
#include "configure.hpp"

class Recipe{
    private:
        int id;
        std::string recipeName;
        Name author;
        Category category;
        int preparationTime; 
        List<StringWrapper, Configure::maximunIngredientSize> procedureList;
        List<Ingredient, Configure::maximunIngredientSize> ingredientList;
        Date creationDate;

    public:
        Recipe();
        Recipe(const Recipe&);
        Recipe(const int&, const std::string&, const Name&, const Category&, const int&, const List<StringWrapper, Configure::maximunIngredientSize>&, const List<Ingredient, Configure::maximunIngredientSize>&, const Date&);
        
        int getId() const;
        std::string getRecipeName() const;
        Name getAuthor() const;
        Category getCategory() const;
        int getPreparationTime() const;
        List<StringWrapper, Configure::maximunIngredientSize>& getProcedureList();
        List<Ingredient, Configure::maximunIngredientSize>& getIngredientList();
        Date getCreationDate() const;

        std::string toString() const;

        //Setter's
        void setId(const int&);
        void setRecipeName(const std::string&);
        void setAuthor(const Name&);
        void setCategory(const Category&);
        void setPreparationTime(const int&);
        void setProcedureList(const List<StringWrapper, Configure::maximunIngredientSize>&);
        void setIngredientList(const List<Ingredient, Configure::maximunIngredientSize>&);
        void setCreationDate(const Date&);

        //Algoritmicos 
            //Control de Ingredientes
        void addIngredient(const Ingredient&);
        void deleteIngredient(const Ingredient&);
        void clearIngredients();
        Ingredient* searchIngredient(const Ingredient&);

            //Control de Procedimiento
        void addStepToProcedure(const std::string&);
        void deleteStepFromProcedure(const int&);
        void clearProcedure();

        bool operator == (const Recipe&) const;
        bool operator < (const Recipe&) const;
        bool operator > (const Recipe&) const;
        bool operator <= (const Recipe&) const;
        bool operator >= (const Recipe&) const;

        int compareTo(const Recipe&);
        static int compare(const Recipe&, const Recipe&);

        static int compareByName(const Recipe&, const Recipe&);
        static int compareByAuthor(const Recipe&, const Recipe&);
        static int compareByCategory(const Recipe&, const Recipe&);
        static int compareByPreparationTime(const Recipe&, const Recipe&);
        static int compareByCreationDate(const Recipe&, const Recipe&);
        
        nlohmann::json toJson() const;
        void fromJson(const nlohmann::json&);
    
        friend std::ostream& operator << (std::ostream&, const Recipe&);
        friend std::istream& operator >> (std::istream&, Recipe&);

        Recipe& operator = (const Recipe&);
};

#endif // __RECIPE_H__