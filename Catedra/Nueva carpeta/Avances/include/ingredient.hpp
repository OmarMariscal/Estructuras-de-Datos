#ifndef __INGREDIENT_H__
#define __INGREDIENT_H__

#include <iostream>
#include <string>
#include <sstream>

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

        std::string getName() const;
        float getAmount() const;
        std::string getUnit() const;

        std::string toString() const;

        void setNameInredient(const std::string&);
        void setAmount(const float&);
        void setUnit(const std::string&);

        bool operator == (const Ingredient&);
        bool operator != (const Ingredient&);
        bool operator < (const Ingredient&);
        bool operator > (const Ingredient&);
        bool operator <= (const Ingredient&);
        bool operator >= (const Ingredient&);

        int compare(const Ingredient&) const;
        static int compareTo(const Ingredient&, const Ingredient&);

        int compareByAmount(const Ingredient&) const;
        static int CompareToByAmount(const Ingredient&, const Ingredient&);

        friend std::ostream& operator << (std::ostream&, const Ingredient&);
        friend std::istream& operator >> (std::istream&, Ingredient&);

        Ingredient& operator = (const Ingredient&);
         
};

#endif // __INGREDIENT_H__