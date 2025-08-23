#include "product.hpp"

Product::Product() : barcode(""), productName(""), weight(0.0), entryDate(Date()), wholesalePrice(0.0), retailPrice(0.0), currentExistence(0){

}

Product::Product(const Product& other) : barcode(other.barcode), productName(other.productName), weight(other.weight), entryDate(other.entryDate), wholesalePrice(other.wholesalePrice), retailPrice(other.retailPrice), currentExistence(other.currentExistence){
    
}

std::string Product::getBarcode() const{
    return this->barcode;
}

std::string Product::getProductName() const{
    return this->productName;
}

float Product::getWeight() const{
    return this->weight;
}

Date Product::getEntryDate() const{
    return this->entryDate;
}

float Product::getWholesalePrice() const{
    return this->wholesalePrice;
}

float Product::getRetailPrice() const{
    return this->retailPrice;
}

int Product::getCurrentExistence() const{
    return this->currentExistence;
}

std::string Product::toString() const{
    std::ostringstream oss;
    oss<<"=======================================\n"
        <<"       INFORMACION DEL PRODUCTO     \n"
        <<"=======================================\n";

    oss<< "Codigo de Barras: " << barcode
        <<"\nNombre del Producto " <<productName
        <<"\nPeso del Producto: " << weight
        <<"\nFecha de Ingreso: " <<entryDate.toString()
        <<"\nPrecio al Mayorista: " << wholesalePrice
        <<"\nPrecio al Minorista: " <<retailPrice
        <<"\nExistencias Actuales: " <<currentExistence;
    oss<<"\n=======================================\n";

    return oss.str(); 
}

void Product::setBarcode(const std::string& barcode){
    if(barcode.size() > configure::barcodeSize)
        throw std::out_of_range("Solo se permiten " + std::to_string(configure::barcodeSize) + " caracteres.");
    this->barcode = barcode;
}

void Product::setProductName(const std::string& productName){
    if(productName.empty())
        throw std::invalid_argument("El nombre no puede estar vacío");
    this->productName = productName;
}

void Product::setWeight(const float&  weight){
    if(weight <= 0)
        throw std::invalid_argument("El peso no puede ser menor ni igual que 0");
    this->weight = weight;
}

void Product::setEntryDate(const Date& entryDate){
    this->entryDate = entryDate; //Date ya tiene sus propias validaciones
}

void Product::setWholesalePrice(const float& wholesalePrice){
    if(wholesalePrice <= 0)
        throw std::invalid_argument("El precio no puede ser menor o igual a 0");
    this->wholesalePrice = wholesalePrice;
}

void Product::setRetailPrice(const float& retailPrice){
    if(retailPrice < 0)
        throw std::invalid_argument("El precio no puede ser menor o igual a 0");
    this->retailPrice = retailPrice;
}

void Product::setCurrentExistence(const int& currentExistence){
    if(currentExistence < 0)
        throw std::invalid_argument("Un producto no puede quedar en cantidad negativa.");
    this->currentExistence = currentExistence;
}

Product& Product::operator=(const Product& other){
    this->barcode = other.barcode;
    this->productName = other.productName;
    this->weight = other.weight;
    this->entryDate = other.entryDate;
    this->wholesalePrice = other.wholesalePrice;
    this->retailPrice = other.retailPrice;
    this->currentExistence = other.currentExistence;

    return *this;
}

void Product::increaseExistence(const int& increase){
    this->currentExistence+= increase;
}

void Product::decreaseExistence(const int& decrease){
    if(decrease > currentExistence)
        throw std::logic_error("No puedes tener valores negativos");
    currentExistence-= decrease;
}