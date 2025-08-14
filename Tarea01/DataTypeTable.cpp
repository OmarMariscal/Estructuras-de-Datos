/*Nombre: Mariscal Rodríguez Omar Jesús
Fecha de Entrega: 17 de Agosto de 2025 
Problema: Actividad de Aprendizaje 01: Tipos de Dato Primitivo y Tipos de Datos Compuestos
Versión: 1.0*/

#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

class DataTypeTable{
    public:
        DataTypeTable();
        static void showDataTypeTable();
};

void DataTypeTable::showDataTypeTable(){
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

    // Cabecera
    linea();
    cout << "|" << setw(widthType) << left << "Tipo de dato"
         << "|" << setw(widthBits) << left << "Bits"
         << "|" << setw(widthMin) << left << "Valor mínimo"
         << "|" << setw(widthMax) << left << "Valor máximo" << "|\n";
    linea();

    // Filas de datos
    cout << "|" << setw(widthType) << left << "Caracter con signo"
         << "|" << setw(widthBits) << left << sizeof(char)*8
         << "|" << setw(widthMin) << left << int(std::numeric_limits<char>::min())
         << "|" << setw(widthMax) << left << int(std::numeric_limits<char>::max()) << "|\n";

    cout << "|" << setw(widthType) << left << "Caracter sin signo"
         << "|" << setw(widthBits) << left << sizeof(unsigned char) * 8
         << "|" << setw(widthMin) << left << int(std::numeric_limits<unsigned char>::min())
         << "|" << setw(widthMax) << left << int(std::numeric_limits<unsigned char>::max()) << "|\n";

    cout << "|" << setw(widthType) << left << "Entero corto con signo"
         << "|" << setw(widthBits) << left << sizeof(int) * 8
         << "|" << setw(widthMin) << left << std::numeric_limits<int>::min()
         << "|" << setw(widthMax) << left << std::numeric_limits<int>::max() << "|\n";

    cout << "|" << setw(widthType) << left << "Entero corto sin signo"
         << "|" << setw(widthBits) << left << sizeof(unsigned int) * 8
         << "|" << setw(widthMin) << left << std::numeric_limits<unsigned int>::min()
         << "|" << setw(widthMax) << left << std::numeric_limits<unsigned int>::max() << "|\n";

    cout << "|" << setw(widthType) << left << "Entero largo con signo"
         << "|" << setw(widthBits) << left << sizeof(long int) * 8
         << "|" << setw(widthMin) << left << std::numeric_limits<long int>::min()
         << "|" << setw(widthMax) << left << std::numeric_limits<long int>::max() << "|\n";

    cout << "|" << setw(widthType) << left << "Entero largo sin signo"
         << "|" << setw(widthBits) << left << sizeof(unsigned long int) * 8
         << "|" << setw(widthMin) << left << std::numeric_limits<unsigned long int>::min()
         << "|" << setw(widthMax) << left << std::numeric_limits<unsigned long int>::max() << "|\n";

    cout << "|" << setw(widthType) << left << "Real de precisión simple"
         << "|" << setw(widthBits) << left << sizeof(float) * 8
         << "|" << setw(widthMin) << left << std::numeric_limits<float>::min()
         << "|" << setw(widthMax) << left << std::numeric_limits<float>::max() << "|\n";

    cout << "|" << setw(widthType) << left << "Real de doble precisión"
         << "|" << setw(widthBits) << left << sizeof(double) * 8
         << "|" << setw(widthMin) << left << std::numeric_limits<double>::min()
         << "|" << setw(widthMax) << left << std::numeric_limits<double>::max() << "|\n";

    linea(); 
}

int main() {
    DataTypeTable::showDataTypeTable();
    return 0;
}