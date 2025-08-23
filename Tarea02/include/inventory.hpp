#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <string.h>
#include <iomanip>

#include "product.hpp"
#include "configure.hpp"

class Inventory{
    private:
        int numberOfProducts;
        Product products[configure::inventoryCapacity];

    public:
        Inventory();
        Inventory(const Inventory&);
        Inventory(const int&, const Product*);

        //Interfaces:
            //Getter's
        int getNumberOfProducts() const;
        const Product* getProducts() const;

        std::string toString() const;

            //Setter's
        void setNumberOfProducts(const int&);
        void setProducts(const Product*);

        Inventory& operator=(const Inventory&);

        //Algoritmitos
        Product* searchProduct(const std::string&);

        void addProduct(const Product&);

        void increaseProduct(const std::string&, const int&);
        void decreaseProduct(const std::string&, const int&);
};

#endif // __INVENTORY_H__