#include "inventory.hpp"


Inventory::Inventory() : numberOfProducts(0){

}

Inventory::Inventory(const Inventory& other) : numberOfProducts(other.numberOfProducts){
    for(int i = 0; i < other.numberOfProducts; i++)
        this->products[i] = other.products[i];
}

Inventory::Inventory(const int& n, const Product* products) : numberOfProducts(n){
    for(int i = 0; i < configure::inventoryCapacity; i++)
        this->products[i] = products[i];
}

int Inventory::getNumberOfProducts() const{
    return this->numberOfProducts;
}

const Product* Inventory::getProducts() const{
    return products;
}


std::string Inventory::toString() const{
    std::ostringstream oss;

    oss<<"===========================================================================================================================\n";
    oss<<"                                                       INVENTARIO COMPLETO           \n";
    oss<<"===========================================================================================================================\n";

    //Encabezados
    oss<< std::left
        <<std::setw(20) << "CODIGO DE BARRAS"
        <<std::setw(10) << "NOMBRE"
        <<std::setw(10) << "PESO"
        <<std::setw(32) << "FECHA DE ENTRADA"
        <<std::setw(20) << "PRECIO AL MAYOREO"
        <<std::setw(20) << "PRECIO AL MENUDEO"
        <<std::setw(8) << "EXISTENCIAS";

    oss<< "\n---------------------------------------------------------------------------------------------------------------------------\n";

    //Recorrer los Productos
    for(int i = 0; i < numberOfProducts; i++){
        oss<< std::left
            <<std::setw(20) << products[i].getBarcode()
            <<std::setw(10) << products[i].getProductName()
            <<std::setw(10) << products[i].getWeight()
            <<std::setw(32) << products[i].getEntryDate().toString()
            <<std::setw(20) << products[i].getWholesalePrice()
            <<std::setw(20) << products[i].getRetailPrice()
            <<std::setw(8) << products[i].getCurrentExistence()
            <<"\n";
    }

    oss<< "\n\n---------------------------------------------------------------------------------------------------------------------------\n";

    oss<< std::left
        << std::setw(20) << "TOTAL DE PRODUCTOS: "
        << numberOfProducts <<"\n";

    return oss.str();
}

void Inventory::setNumberOfProducts(const int& numberOfProducts){
    if(numberOfProducts < 0)
        throw std::out_of_range("El numero de productos no puede ser menor o igual a 0");
}

void Inventory::setProducts(const Product* products){
    for(int i = 0; i < configure::inventoryCapacity; i++)
        this->products[i] = products[i];
}

Inventory& Inventory::operator=(const Inventory& other){
    this->numberOfProducts = other.numberOfProducts;
    for(int i = 0; i < configure::inventoryCapacity; i++)
        this->products[i] = other.products[i];
    return *this;
}

Product* Inventory::searchProduct(const std::string& barcode){
    for(int i = 0; i < numberOfProducts; i++)
        if(products[i].getBarcode() == barcode)
            return &products[i];
    return nullptr;
}

//Algorítmicos
void Inventory::addProduct(const Product& newProduct){
    if(numberOfProducts >= configure::inventoryCapacity)
        throw std::out_of_range("Inventario lleno");
   
    if(searchProduct(newProduct.getBarcode()) != nullptr)
        throw std::invalid_argument("El producto ya esta registrado.");

    products[numberOfProducts] = newProduct;
    numberOfProducts++;
}

void Inventory::increaseProduct(const std::string& barcode, const int& increase){
    if(numberOfProducts <= 0)
        throw std::logic_error("No hay productos registrados");
    
    Product* validation = searchProduct(barcode);
    if(validation == nullptr)
        throw std::invalid_argument("Codigo de barras no encontrado");
    
    validation->increaseExistence(increase);
}

void Inventory::decreaseProduct(const std::string& barcode, const int& decrease){
    if(numberOfProducts <= 0)
        throw std::logic_error("No hay productos registrados");
    
    Product* validation = searchProduct(barcode);
    if(validation == nullptr)
        throw std::invalid_argument("Codigo de barras no encontrado");
    if(decrease > validation->getCurrentExistence())
        throw std::invalid_argument("No puedes poner una cantidad que dejaria en negativo el stock");
    validation->decreaseExistence(decrease);
}

