#ifndef __INGREDIENT_H__
#define __INGREDIENT_H__

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "../lib/nlohmann/json.hpp"

#include "ownexceptions.hpp"

class Ingredient{
    private:
        std::string nameIngredient;
        float amount;
        std::string unit;
    public:
        Ingredient();
        Ingredient(const Ingredient&);
        /// @brief 
        /// @param nameIngrediet 
        /// @param  amount
        /// @param  unit
        Ingredient(const std::string&, const float&, const std::string&);

        std::string getNameIngredient() const;
        float getAmount() const;
        std::string getUnit() const;

        std::string toString() const;

        void setNameInredient(const std::string&);
        void setAmount(const float&);
        void setUnit(const std::string&);

        bool operator == (const Ingredient&) const;
        bool operator != (const Ingredient&) const;
        bool operator < (const Ingredient&) const;
        bool operator > (const Ingredient&) const;
        bool operator <= (const Ingredient&) const;
        bool operator >= (const Ingredient&) const;

        int compare(const Ingredient&) const;
        static int compareTo(const Ingredient&, const Ingredient&);

        static int compareByAmount(const Ingredient&, const Ingredient&);
        static int compareByUnit(const Ingredient&, const Ingredient&);

        nlohmann::json toJson() const;
        void fromJson(const nlohmann::json&);
        
        Ingredient& operator = (const Ingredient&);
         
};

#endif // __INGREDIENT_H__