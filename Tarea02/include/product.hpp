#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <string>
#include <iomanip>

#include "date.hpp"
#include "configure.hpp"

class Product{
    private:
        std::string barcode;
        std::string productName;
        float weight;
        Date entryDate;
        float wholesalePrice;
        float retailPrice;
        int currentExistence;
    public:
        Product();
        Product(const Product&);

        //Interfaces
            //Getter's
        std::string getBarcode() const;
        std::string getProductName() const;
        float getWeight() const;
        Date getEntryDate() const;
        float getWholesalePrice() const;
        float getRetailPrice() const;
        int getCurrentExistence() const;

        std::string toString() const;

            //Setter's
        void setBarcode(const std::string&);
        void setProductName(const std::string&);
        void setWeight(const float&);
        void setEntryDate(const Date&);
        void setWholesalePrice(const float&);
        void setRetailPrice(const float&);
        void setCurrentExistence(const int&);

        Product& operator=(const Product&);

        //Algoritmicos
        void increaseExistence(const int&);
        void decreaseExistence(const int &);
};

#endif // __PRODUCT_H__