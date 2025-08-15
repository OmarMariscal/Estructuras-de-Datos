/*Nombre: Mariscal Rodríguez Omar Jesús
Fecha de Entrega: 17 de Agosto de 2025 
Problema: Actividad de Aprendizaje 01: Tipos de Dato Primitivo y Tipos de Datos Compuestos
Archivo: DataTypeTable.cpp*/

#include <iostream> //Librería de Entrada y Salida de Datos Estándar
#include <iomanip> //Librería para el control de entrada y salida de datos. Usada para darle el formato a la tabla
#include <limits> //Librería para extreaer del lenguaje el tamaño de los tipos de datos. 
#include "DataTypeTable.h" //Incluir la definición de la clase

//using std's para agilizar funciones recurrentes en el archivo
using std::cout;
using std::left;
using std::string;
using std::setw;
using std::numeric_limits;

//Función  para imprimir la tabla de valores con funciones del lenguaje
void Tables::DataTypeTable::showDataTypeTable(){
     //Medidas para el ancho de cada apartado
    const int widthType = 30;
    const int widthBits = 10;
    const int widthMin = 15;
    const int widthMax = 15;

    // Función para imprimir línea horizontal
    auto linea = [&]() {
        cout << "+" << string(widthType,'-') 
             << "+" << string(widthBits,'-') 
             << "+" << string(widthMin,'-') 
             << "+" << string(widthMax,'-') << "+\n";
    };

    // Cabeceraas
    linea();
    cout << "|" << setw(widthType) << left << "Tipo de dato"
         << "|" << setw(widthBits) << left << "Bits"
         << "|" << setw(widthMin) << left << "Valor minimo"
         << "|" << setw(widthMax) << left << "Valor maximo" << "|\n";
    linea();

    // Filas de los distintos tipos de datos
    //Usamos setw para establecer los anchos de cada apartado
    cout << "|" << setw(widthType) << left << "Caracter con signo"
         << "|" << setw(widthBits) << left << sizeof(char)*8
         << "|" << setw(widthMin) << left << int(numeric_limits<char>::min())
         << "|" << setw(widthMax) << left << int(numeric_limits<char>::max()) << "|\n";

    cout << "|" << setw(widthType) << left << "Caracter sin signo"
         << "|" << setw(widthBits) << left << sizeof(unsigned char) * 8
         << "|" << setw(widthMin) << left << int(numeric_limits<unsigned char>::min())
         << "|" << setw(widthMax) << left << int(numeric_limits<unsigned char>::max()) << "|\n";

    cout << "|" << setw(widthType) << left << "Entero corto con signo"
         << "|" << setw(widthBits) << left << sizeof(int) * 8
         << "|" << setw(widthMin) << left << numeric_limits<int>::min()
         << "|" << setw(widthMax) << left << numeric_limits<int>::max() << "|\n";

    cout << "|" << setw(widthType) << left << "Entero corto sin signo"
         << "|" << setw(widthBits) << left << sizeof(unsigned int) * 8
         << "|" << setw(widthMin) << left << numeric_limits<unsigned int>::min()
         << "|" << setw(widthMax) << left << numeric_limits<unsigned int>::max() << "|\n";

    cout << "|" << setw(widthType) << left << "Entero largo con signo"
         << "|" << setw(widthBits) << left << sizeof(long int) * 8
         << "|" << setw(widthMin) << left << numeric_limits<long int>::min()
         << "|" << setw(widthMax) << left << numeric_limits<long int>::max() << "|\n";

    cout << "|" << setw(widthType) << left << "Entero largo sin signo"
         << "|" << setw(widthBits) << left << sizeof(unsigned long int) * 8
         << "|" << setw(widthMin) << left << numeric_limits<unsigned long int>::min()
         << "|" << setw(widthMax) << left << numeric_limits<unsigned long int>::max() << "|\n";

    cout << "|" << setw(widthType) << left << "Real de precision simple"
         << "|" << setw(widthBits) << left << sizeof(float) * 8
         << "|" << setw(widthMin) << left << numeric_limits<float>::min()
         << "|" << setw(widthMax) << left << numeric_limits<float>::max() << "|\n";

    cout << "|" << setw(widthType) << left << "Real de doble precision"
         << "|" << setw(widthBits) << left << sizeof(double) * 8
         << "|" << setw(widthMin) << left << numeric_limits<double>::min()
         << "|" << setw(widthMax) << left << numeric_limits<double>::max() << "|\n";
    //linea final
    linea(); 
}