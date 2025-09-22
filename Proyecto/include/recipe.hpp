#ifndef __RECIPE_H__
#define __RECIPE_H__

#include <iostream>
#include <string>
#include <sstream>

#include "category.hpp"
#include "list.hpp"
#include "ingredient.hpp"
#include "date.hpp"



class Recipe{
    private:
        int id;
        std::string recipeName;
        Category category;
        int preparationTime; 
        List<std::string> procedureList;
        List<Ingredient> ingredientList;
        Date creationDate;

    public:
        Recipe();
        Recipe(const Recipe&);
        Recipe(const int&, const std::string&, const Category&, const int&, const List<std::string>&, const List<Ingredient>&, const Date&);
        
        int getId() const;
        std::string getRecipeName() const;
        Category getCategory() const;
        int getPreparationTime() const;
        List<std::string> getProcedureList() const;
        List<Ingredient> getIngredientList() const;

        std::string toString() const;

        //Setter's
        void setId(const int&);
        void setRecipeName(const std::string& );
        void setCategory(const Category&);
        void setPreparationTime(const int&);
        void setProcedureList(const List<std::string>&);
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

        bool operator == (const Recipe&);
        bool operator < (const Recipe&);
        bool operator > (const Recipe&);
        bool operator <= (const Recipe&);
        bool operator >= (const Recipe&);

        int compareTo(const Recipe&);
        static int compare(const Recipe&, const Recipe&);

        int compareByName(const Recipe&);
        int compareByCategory(const Recipe&);
        int compareByPreparationTime(const Recipe&);
        int compareByCreationDate(const Recipe&);
    
        friend std::ostream& operator << (std::ostream&, const Ingredient&);
        friend std::istream& operator >> (std::istream&, Ingredient&);

        Recipe& operator = (const Recipe&);
};

#endif // __RECIPE_H__