#include "product.hpp"

// Constructor base
Product::Product()
    : barcode(""),
      productName(""),
      weight(0.0),
      entryDate(Date()),
      wholesalePrice(0.0),
      retailPrice(0.0),
      currentExistence(0) {}
// Constructor copia
Product::Product(const Product& other)
    : barcode(other.barcode),
      productName(other.productName),
      weight(other.weight),
      entryDate(other.entryDate),
      wholesalePrice(other.wholesalePrice),
      retailPrice(other.retailPrice),
      currentExistence(other.currentExistence) {}

// Getter's
std::string Product::getBarcode() const {
  return this->barcode;
}

std::string Product::getProductName() const {
  return this->productName;
}

float Product::getWeight() const {
  return this->weight;
}

Date Product::getEntryDate() const {
  return this->entryDate;
}

float Product::getWholesalePrice() const {
  return this->wholesalePrice;
}

float Product::getRetailPrice() const {
  return this->retailPrice;
}

int Product::getCurrentExistence() const {
  return this->currentExistence;
}

// Impresión de las características de un producto
std::string Product::toString() const {
  std::ostringstream oss;
  oss << "=======================================\n"
      << "       INFORMACION DEL PRODUCTO     \n"
      << "=======================================\n";

  oss << "Codigo de Barras: " << barcode << "\nNombre del Producto "
      << productName << "\nPeso del Producto: " << weight
      << "\nFecha de Ingreso: " << entryDate.toString()
      << "\nPrecio al Mayorista: " << wholesalePrice
      << "\nPrecio al Minorista: " << retailPrice
      << "\nExistencias Actuales: " << currentExistence;
  oss << "\n=======================================\n";

  return oss.str();
}

// Setter's
void Product::setBarcode(const std::string& barcode) {
  // Si el código de barras excede el configure, lanzamos excepción
  if (barcode.size() > configure::barcodeSize)
    throw std::out_of_range("Solo se permiten " +
                            std::to_string(configure::barcodeSize) +
                            " caracteres.");
  this->barcode = barcode;
}

void Product::setProductName(const std::string& productName) {
  // Si el nombre está vacío lanzamos excepción
  if (productName.empty())
    throw std::invalid_argument("El nombre no puede estar vacío");
  this->productName = productName;
}

void Product::setWeight(const float& weight) {
  // Si el peso es negativo o igual a 0 lanzamos excepción
  if (weight <= 0)
    throw std::invalid_argument("El peso no puede ser menor ni igual que 0");
  this->weight = weight;
}

void Product::setEntryDate(const Date& entryDate) {
  this->entryDate = entryDate;  // Date ya tiene sus propias validaciones
}

void Product::setWholesalePrice(const float& wholesalePrice) {
  // El precio no puede ser <= 0, lanzamos excepción
  if (wholesalePrice <= 0)
    throw std::invalid_argument("El precio no puede ser menor o igual a 0");
  this->wholesalePrice = wholesalePrice;
}

void Product::setRetailPrice(const float& retailPrice) {
  // El precio no puede ser <=0, lanzamos excepción
  if (retailPrice <= 0)
    throw std::invalid_argument("El precio no puede ser menor o igual a 0");
  this->retailPrice = retailPrice;
}

void Product::setCurrentExistence(const int& currentExistence) {
  // Las exist3encias no pueden ser negativas
  if (currentExistence < 0)
    throw std::invalid_argument(
        "Un producto no puede quedar en cantidad negativa.");
  this->currentExistence = currentExistence;
}

Product& Product::operator=(const Product& other) {
  this->barcode = other.barcode;
  this->productName = other.productName;
  this->weight = other.weight;
  this->entryDate = other.entryDate;
  this->wholesalePrice = other.wholesalePrice;
  this->retailPrice = other.retailPrice;
  this->currentExistence = other.currentExistence;

  return *this;
}

void Product::increaseExistence(const int& increase) {
  this->currentExistence += increase;
}

void Product::decreaseExistence(const int& decrease) {
  if (decrease > currentExistence)  // Lanzamos excepción si las existencias
                                    // quieren ser negativas.
    throw std::logic_error("No puedes tener valores negativos");
  currentExistence -= decrease;
}