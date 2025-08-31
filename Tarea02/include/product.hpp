#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <iomanip>
#include <string>

#include "configure.hpp"
#include "date.hpp"

class Product {
 private:
  std::string barcode;      // Código de Barras
  std::string productName;  // Nombre del Producto
  float weight;             // Peso
  Date entryDate;           // Fecha de Entrada
  float wholesalePrice;     // Fecha de Mayoreo
  float retailPrice;        // Fecha de Menudeo
  int currentExistence;     // Existencia Actual
 public:
  // Constructores.
  // Al tener muchos atributos, se omitió el constructor paramétrico
  Product();
  Product(const Product&);

  // Interfaces
  // Getter's
  std::string getBarcode() const;
  std::string getProductName() const;
  float getWeight() const;
  Date getEntryDate() const;
  float getWholesalePrice() const;
  float getRetailPrice() const;
  int getCurrentExistence() const;

  std::string toString() const;

  // Setter's
  void setBarcode(const std::string&);
  void setProductName(const std::string&);
  void setWeight(const float&);
  void setEntryDate(const Date&);
  void setWholesalePrice(const float&);
  void setRetailPrice(const float&);
  void setCurrentExistence(const int&);

  Product& operator=(const Product&);

  // Algoritmicos
  void increaseExistence(const int&);  // Incrementar las existencias
  void decreaseExistence(const int&);  // Decrecer las existencias
};

#endif  // __PRODUCT_H__