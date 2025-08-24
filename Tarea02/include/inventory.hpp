#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <iomanip>  //Para hacer más estéticos las impresionse de pantalla
#include <string>

#include "configure.hpp"
#include "product.hpp"

class Inventory {
 private:
  int numberOfProducts;  // Número de elementos registrados
  Product
      products[configure::inventoryCapacity];  // Arreglo estático de productos.
                                               // Se puede modificar desde el
                                               // archivo configure.hpp

 public:
  // Constructores
  Inventory();
  Inventory(const Inventory&);
  Inventory(const int&, const Product*);

  // Interfaces:
  // Getter's
  int getNumberOfProducts() const;
  const Product* getProducts() const;

  std::string toString() const;

  // Setter's
  void setNumberOfProducts(const int&);
  void setProducts(const Product*);

  Inventory& operator=(const Inventory&);

  // Algoritmitos
  Product* searchProduct(
      const std::string&);  // Buscador de productos. Devuelve un apuntador

  void addProduct(const Product&);  // Agregar un producto

  void increaseProduct(const std::string&,
                       const int&);  // Incrementa la cantidad en existencia
                                     // dado un código de barras
  void decreaseProduct(const std::string&,
                       const int&);  // Decrece la cantidad en existencia dado
                                     // un código de barras
};

#endif  // __INVENTORY_H__