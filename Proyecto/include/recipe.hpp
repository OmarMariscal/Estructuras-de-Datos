#ifndef __RECIPE_H__
#define __RECIPE_H__

#include <iostream>
#include <string>
#include <sstream>

#include "../lib/nlohmann/json.hpp"

#include "category.hpp"
#include "list.hpp"
#include "ingredient.hpp"
#include "date.hpp"
#include "stringwrapped.hpp"


class Recipe{
    private:
        int id;
        std::string recipeName;
        Category category;
        int preparationTime; 
        List<StringWrapper> procedureList;
        List<Ingredient> ingredientList;
        Date creationDate;

    public:
        Recipe();
        Recipe(const Recipe&);
        Recipe(const int&, const std::string&, const Category&, const int&, const List<StringWrapper>&, const List<Ingredient>&, const Date&);
        
        int getId() const;
        std::string getRecipeName() const;
        Category getCategory() const;
        int getPreparationTime() const;
        List<StringWrapper> getProcedureList() const;
        List<Ingredient> getIngredientList() const;

        std::string toString() const;

        //Setter's
        void setId(const int&);
        void setRecipeName(const std::string& );
        void setCategory(const Category&);
        void setPreparationTime(const int&);
        void setProcedureList(const List<StringWrapper>&);
        void setIngredientList(const List<Ingredient>&);

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

        int compareByName(const Recipe&);
        int compareByCategory(const Recipe&);
        int compareByPreparationTime(const Recipe&);
        int compareByCreationDate(const Recipe&);
        
        nlohmann::json toJson() const;
        void fromJson(const nlohmann::json&);
    
        friend std::ostream& operator << (std::ostream&, const Recipe&);
        friend std::istream& operator >> (std::istream&, Recipe&);

        Recipe& operator = (const Recipe&);
};

#endif // __RECIPE_H__