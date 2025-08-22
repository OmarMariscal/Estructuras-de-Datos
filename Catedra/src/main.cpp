#include <iostream>

#include "student.hpp"
#include "name.hpp"
#include "date.hpp"

using namespace std;

int main(){
    Student myEstudiante;
    Name myNombre;
    Date myFecha;

    string myCadena;
    float myReal;

    cout<<"Codigo: ";
    getline(cin,myCadena);

    myEstudiante.setCode(myCadena);

    cout<<"Apellido: ";
    getline(cin,myCadena);

    myNombre.setLast(myCadena);

    cout<<"Nombre: ";
    getline(cin,myCadena);

    myNombre.setFirst(myCadena);

    myEstudiante.setName(myNombre);

    cout<<"Fecha Nacimiento (DD/MM/AAAA)";
    getline(cin, myCadena, '/');
    myFecha.setDay(stoi(myCadena));

    getline(cin, myCadena, '/');
    myFecha.setMonth(stoi(myCadena));

    getline(cin, myCadena);
    myFecha.setYear(stoi(myCadena));

    myEstudiante.setBirthDate(myFecha);

    cout<<"Carrera: ";
    getline(cin, myCadena);

    myEstudiante.setCareer(myCadena);

    cout<<"Fecha Inicio (DD/MM/AAAA)";
    getline(cin, myCadena, '/');
    myFecha.setDay(stoi(myCadena));

    getline(cin, myCadena, '/');
    myFecha.setMonth(stoi(myCadena));

    getline(cin, myCadena);
    myFecha.setYear(stoi(myCadena));

    myEstudiante.setStartDate(myFecha);

    cout<<"Promedio: ";
    cin>>myReal;

    myEstudiante.setGrade(myReal);

    cout<<myEstudiante.toString();

    return 0;
}