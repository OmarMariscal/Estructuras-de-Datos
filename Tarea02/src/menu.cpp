#include "menu.hpp"

using std::cout;
using std::cin;
using std::endl;

void Menu::mainMenu(){
    system("CLS");
    std::string menuSelection = "";
    menuSelection += "====================================\n";
    menuSelection += "     MENU PRINCIPAL - INVENTARIO    \n";
    menuSelection += "====================================\n";
    menuSelection += "1. Registrar un Nuevo Producto.\n";
    menuSelection += "2. Aumentar Existencia\n";
    menuSelection += "3. Disminuir Existencia\n";
    menuSelection += "4. Consultar Inventario\n";
    menuSelection += "5. Buscar Producto por Codigo\n";
    menuSelection += "6. Salir\n";
    menuSelection += "-------------------------------------\n";
    menuSelection += "Seleccione una opcion: ";

    int selection = Utilities<int>::readNumberRange(1,6,menuSelection);

    switch(selection){
        case 1:
            newProduct();
            break;
        case 2:
            increaseStock();
            break;
        case 3:
            decreaseStock();
            break;
        case 4:
            checkInventory();
            break;
        case 5:
            searchProduct();
            break;
        case 6:
            exitScreen();
            break;
    }
}

void Menu::newProduct(){
    system("CLS");

    std::string menuString;
    menuString += "====================================\n";
    menuString += "     REGISTRAR NUEVO PRODUCTO    \n";
    menuString += "====================================\n";

    std::string dataString;
    int dataInt;
    float dataFloat;
    Date entryDate;
    Product newProduct;

    do{
        cout<<"Ingrese el codigo de Barras: ";
        std::getline(cin, dataString);

        if(dataString.size() > configure::barcodeSize){
            system("CLS");
            cout<<"El codigo de barras debe ser de "<<configure::barcodeSize<<" o menos caracteres.\n";
        }

    }while(dataString.size() > configure::barcodeSize);

    Product* validation = inventory.searchProduct(dataString);

    if(validation != nullptr){
        cout<<"Producto Ya registado."<<endl;
        cout<<validation->toString();
        system("PAUSE");
        mainMenu();
    };

    newProduct.setBarcode(dataString);

    cout<<"Ingrese el Nombre del Producto: ";
    std::getline(cin,dataString);
    newProduct.setProductName(dataString);

    dataFloat = Utilities<float>::readPositiveNumber("Ingrese el peso del producto: ");
    newProduct.setWeight(dataFloat);

    int select = Utilities<int>::readNumberRange(1,2,"Para la fecha de entrada, desea poner la fecha de hoy? (1. Si/ 2. No): ");

    if(select == 2){
        dataInt = Utilities<int>::readNumberRange(1,31,"Ingrese el dia de ingreso: ");
        newProduct.getEntryDate().setDay(dataInt);

        dataInt = Utilities<int>::readNumberRange(1,12,"Ingrese el numero del mes que se ingreso: ");
        newProduct.getEntryDate().setMonth(dataInt);

        dataInt = Utilities<int>::readNumberRange(configure::minimumYear, entryDate.getYear(),"Ingrese el anio en que se ingreso: ");
        newProduct.getEntryDate().setYear(dataInt);
    }

    dataFloat = Utilities<float>::readPositiveNumber("Ingrese el precio al mayoreo: ");
    newProduct.setWholesalePrice(dataFloat);

    dataFloat = Utilities<float>::readPositiveNumber("Ingrese el precio al menudeo: ");
    newProduct.setRetailPrice(dataFloat);

    dataInt = Utilities<int>::readPositiveNumber("Ingrese la cantidad en stock: ");
    newProduct.setCurrentExistence(dataInt);

    inventory.addProduct(newProduct);
    cout<<"\n\n";
    cout<<"----------------------------------------------------------";
    cout<<"Producto agregado con exito!\n";
    system("PAUSE");

    mainMenu();
}

void Menu::increaseStock(){
    system("CLS");
    if(inventory.getNumberOfProducts() <= 0){
        cout<<"Aun no existen productos registrados."<<endl;
        system("PAUSE");
        mainMenu();
    }
        std::string barcode;
        int select;
    do{
        system("CLS");
        cout<<"Ingrese el codigo de barras del producto: ";
        getline(cin, barcode);
        Product* validation = inventory.searchProduct(barcode);

        if(validation == nullptr){
            cout<<"Producto no encontrado"<<endl; 
        }
        
        else{
            int increase = Utilities<int>::readPositiveNumber(validation->toString() + "\n Cuantas Unidades desea aumentar el stock?: ");
            inventory.increaseProduct(barcode, increase);
            cout<<"Existencias Agregadas con Exito!"<<endl;
        }
        select = Utilities<int>::readNumberRange(1,2,"Desea Ingresar un Nuevo Codigo de Barras? (1. Si/ 2. No): ");
    
    }while(select != 2);

    mainMenu();
}

void Menu::decreaseStock(){
    system("CLS");
    if(inventory.getNumberOfProducts() <= 0){
        cout<<"Aun no se registran productos en el sistema."<<endl;
        system("PAUSE");
        mainMenu();
    }

    std::string barcode;
    int select;

    do{
        system("CLS");

        cout<<"Ingrese el codigo de barras del producto que desea quitar stock: ";
        getline(cin, barcode);

        Product* validation = inventory.searchProduct(barcode);
        if(validation == nullptr){
            cout<<"El codigo de barras no esta registrado."<<endl;
        }
        else{
            if(validation->getCurrentExistence() == 0){
                cout<<validation->toString();
                cout<<"Las existencias estan en 0, no pueden decrecer.\n";
            }
            else{
                int decrease = Utilities<int>::readNumberRange(1, validation->getCurrentExistence(), validation->toString() + "\nIngrese la cantidad que desee quitar del stock actual: ");
                inventory.decreaseProduct(barcode, decrease);
                cout<<"\nDecremento hecho con exito!\n";
            }
        }

        select = Utilities<int>::readNumberRange(1,2,"Desea ingresar otro codigo de barras? (1. Si/ 2. No): ");

    }while(select != 2);

    mainMenu();
}

void Menu::checkInventory(){
    system("CLS");
    if(inventory.getNumberOfProducts() <= 0){
        cout<<"Aun no se Registran Productos."<<endl;
        system("PAUSE");
        mainMenu();
    }
    cout<<inventory.toString();
    system("PAUSE");
    mainMenu();
}

void Menu::searchProduct(){
    system("CLS");
    if(inventory.getNumberOfProducts() <= 0){
        cout<<"No hay productos registrados aun."<<endl;
        cout<<"Regresando al menu principal."<<endl;
        system("PAUSE");
        mainMenu();
    }
    std::string barcode;
    int select;

    do{
        system("CLS");
        cout<<"Ingrese el codigo de barras del producto que desea buscar: ";
        getline(cin, barcode);

        Product* validation = inventory.searchProduct(barcode);

        if(validation == nullptr)
            cout<<"El codigo de barras "<<barcode<<" no se encuentra registrado en el sistema.";
        else
            cout<<validation->toString();

        select = Utilities<int>::readNumberRange(1,2,"Desea Realizar Otra Busqueda? (1. Si/ 2. No): ");
    
    }while(select != 2);

    mainMenu();
}

void Menu::exitScreen(){
    system("CLS");
    std::cout << "========================================\n";
    std::cout << "        Gracias por usar el sistema      \n";
    std::cout << "             INVENTARIO 1.0             \n";
    std::cout << "========================================\n";
    std::cout << "   Hecho por: Mariscal Rodriguez Omar Jesus \n";
    std::cout << "   Materia: Estructuras de Datos \n";
    std::cout << "   Profesor: Gutierrez Hernandez Alfredo \n";
    std::cout << "   Hasta Pronto! Lindo Dia :D \n";
    std::cout << "========================================\n\n";
    system("PAUSE");
    return;
}

Menu::Menu(){
    mainMenu();
}
