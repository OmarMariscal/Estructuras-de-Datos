#ifndef __RECIPE_H__
#define __RECIPE_H__

#include <iostream>
#include <string>
#include <sstream>

#include "../lib/nlohmann/json.hpp"

#include "category.hpp"
#include "simplelinkedlist.hpp"
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
        SimpleLinkedList<StringWrapper> procedureList;
        SimpleLinkedList<Ingredient> ingredientList;
        Date creationDate;

    public:
        Recipe();
        Recipe(const Recipe&);
        Recipe(const int&, const std::string&, const Name&, const Category&, const int&, const SimpleLinkedList<StringWrapper>&, const SimpleLinkedList<Ingredient>&, const Date&);
        
        int getId() const;
        std::string getRecipeName() const;
        Name getAuthor() const;
        Category getCategory() const;
        int getPreparationTime() const;
        SimpleLinkedList<StringWrapper>& getProcedureList();
        SimpleLinkedList<Ingredient>& getIngredientList();
        Date getCreationDate() const;

        std::string toString(const std::string& = "full") const;

        //Setter's
        void setId(const int&);
        void setRecipeName(const std::string&);
        void setAuthor(const Name&);
        void setCategory(const Category&);
        void setPreparationTime(const int&);
        void setProcedureList(const SimpleLinkedList<StringWrapper>&);
        void setIngredientList(const SimpleLinkedList<Ingredient>&);
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
        
        Recipe& operator = (const Recipe&);
};

#endif // __RECIPE_H__