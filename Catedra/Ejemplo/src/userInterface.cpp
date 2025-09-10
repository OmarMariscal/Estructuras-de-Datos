#include "userInterface.hpp"

using namespace std;

void UserInterface::mainMenu() {
    char op;

    do{
        system("CLS");

        cout << "Menu Principal de Alumnos" <<endl << endl;  
        
        cout << "[A]ñadir alumno" << endl;
        cout << "[E]liminar alumno" << endl;
        cout << "[M]ostrar listado" << endl;
        cout << "[G]uardar al disco" << endl;
        cout << "[L]eer del disco" << endl;
        cout << "[S]alir" << endl;

        cout << "Elija una opcion (A, E, M, G, L, S): ";
        cin >> op;
        cin.ignore();

        op = toupper(op);

        switch (op){
        case 'A':
            this->addStudent();
            break;
        case 'E':
            this->delStudent();
            break;
        case 'M':
            this->showList();
            break;
        case 'G':
            this->writeToDisk();
            break;
        case 'L':
            this->readFromDisk();
            break;
        case 'S':
            cout << "Adios ... " << endl;
            enterToContinue();
            break;
        default:
            cout << "Opcion Invalida, trata de nuevo" <<endl;
            enterToContinue();
            break;
        }

    } while(op != 'S');


}

void UserInterface::addStudent(){
    system("CLS");

    Student myStudent;
    Date myDate;
    string myCadena;
    Name myName;

    cout << "Añadiendo un estudiante: " << endl << endl;
    cout << "Codigo: ";
    getline(cin, myCadena);

    cout << "Apellido: ";
    getline(cin, myCadena);
    myName.setLast(myCadena);
}

void UserInterface::delStudent(){
    
}

void UserInterface::showList(){
    system("CLS");
    cout << "Contenido de la lista" << endl << endl;

    cout << this->myListRef->toString() << endl << endl;
    enterToContinue();
}

void UserInterface::writeToDisk(){
    string myStr;
    ofstream myArchivo;

    system("CLS");
    
    cout << "Nombre del Archivo para Escribir: ";
    getline(cin, myStr);

    myArchivo.open(myStr, ios_base::trunc);

    if(myArchivo.is_open()){
        myArchivo << *this->myListRef;

        myArchivo.close();
        cout << "Archivo Creado :D" << endl;
    }

    else{
        cout << "Lamentablemente, no se pueden abrir archivos para escritura. :(" << endl;
    }

    this->enterToContinue();
}

void UserInterface::readFromDisk(){
    string myStr;
    ifstream myArchivo;

    system("CLS");
    cout << "Recuperacion de la lista desde un archivo" << endl << endl;
    cout << "Nombre del archivo: ";
    getline(cin, myStr);


    myArchivo.open(myStr);

    if(myArchivo.is_open()){
        myListRef -> deleteAll();
        myArchivo >> *myListRef;

        cout << "Lista Efectivamente Recuperada." <<endl;
    }
    else{
        cout << "No se pudo abrir el archivo para lectura." << endl;
    }
    cout << endl;
    enterToContinue();
}

void UserInterface::enterToContinue(){
    cout << "[ENTER] Para Continuar...";
    getchar();
}

UserInterface::UserInterface(List<Student>& listRef) : myListRef(&listRef){
    mainMenu();
}
