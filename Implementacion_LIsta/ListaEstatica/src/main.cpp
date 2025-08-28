#include <iostream>

#include "list.hpp"
#include "student.hpp"

using namespace std;

int main(int argc, char *argv[]){
    List<Student> myList;
    string nombre;
    
    int myInt;

    system("CLS");

    do{
        cout<<"Dame un valor entero";
        getline(cin,nombre);

        myList.insertData(myList.getLastPos(), nombre);

        cout<<"Valor Ingresado!!"<<endl<<endl;
    }while(myInt != 0);

    cout<<"Contenido de la lista: "<<endl;

    cout<<myList.toString();
    cout<<"fasdfads";
    system("PAUSE");
}
