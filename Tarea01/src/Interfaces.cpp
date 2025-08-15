/*Nombre: Mariscal Rodríguez Omar Jesús
Fecha de Entrega: 17 de Agosto de 2025 
Problema: Actividad de Aprendizaje 01: Tipos de Dato Primitivo y Tipos de Datos Compuestos
Archivo: Interfaces.cpp*/


#include "Interfaces.h" //Importación del Menú y las Utilidades
#include "DataTypeTable.h" //Imporatación de la clase de tabla de valores 
#include "Matrix.h" //Importación de la clase de matrices

#include <iostream> //Entrada y Salida Estándar
#include <sstream> //Para manipular strings con mayor facilidad

//std's frecuentes
using std::cout;
using std::cin;
using std::endl;

namespace Utilities{
    int InputUtilities::inputPositiveIntegerLimit(std::string label, int lowerLimit, int upperLimit){
        int answer;
        //Ciclo PostPrueba para obtener un entero en un rango determinado
        do{
            system("CLS");
            cout<< label; //Impresión de un mensaje
            cin>> answer;
             //Evaluación de la respuesta
            if(answer < lowerLimit || answer > upperLimit){
                system("CLS");
                cout<<"Se ha ingresado un numero fuera de lo establecido."<<endl;
                cout<<"Por favor, intentelo nuevamente."<<endl<<endl;
                system("PAUSE");
            }

        } while(answer < lowerLimit || answer > upperLimit);

        return answer;
    }    
}

namespace Menus{
    //Menú Principal del Programa
    void Menu::mainMenu(){
        system("CLS");
        
        //El menú principal es un string acompañado de ostringstream para poder llevarlo facilmente a las funciones de utilidades.
        std::ostringstream oss;
        oss << "+------------------------------------------------+\n";
        oss << "|                 Menu Principal                 |\n";
        oss << "+------------------------------------------------+\n";
        oss << "| 1. Mostrar Tabla de Tipos de Datos             |\n";
        oss << "| 2. Ejemplo del uso de Tipo de Dato Compuesto   |\n";
        oss << "| 3. Salir                                       |\n";
        oss << "+------------------------------------------------+\n";
        oss << "Ingrese una opcion: ";
        int selection = Utilities::InputUtilities::inputPositiveIntegerLimit(oss.str(),1,3); //Elección del Usuario
        
        //Redirigir a la opción correspondiente
        switch (selection){
        case 1:
            dataTypes();
            break;
        case 2:
            compositeData();
            break;
        case 3:
            exit();
            break;
        //No hay necesidad de un case default; esto por las utilidades que no permiten avanzar si no se ingresa un número correcto.
        }
    }

    //Mostrar la tabla de tipos de datos
    void Menu::dataTypes(){
        system("CLS");
        
        cout<<"La siguiente tabla muestra la informacion de distintos tipos de datos obtenidos directamente del lenguaje: "<<endl;
        Tables::DataTypeTable::showDataTypeTable(); //Uso del método estático (sin instancia requerida)
        
        system("PAUSE");
        mainMenu(); //Regresamos al menú principal
    }    

    //Menú de Datos Compuestos
    void Menu::compositeData(){
        system("CLS");
        //Pedir el Size de la matriz
        int size = Utilities::InputUtilities::inputPositiveIntegerLimit("Ingrese un valor entre 3 y 10 para determinar la capacidad de la matriz: ",3,10);
        
        //Instanciar las matrices A y B
        CompositeData::Matrix matrixA(size);
        CompositeData::Matrix matrixB(size);

        //Inicializarlas en 0's
        matrixA.zeros();
        matrixB.zeros();

        //Llenarlas con números aleatorios reales en el rango determinado
        matrixA.randomizer();
        matrixB.randomizer();

        //MatrizC y MatrizD obtenidas de las operaciones sobrecargadas
        CompositeData::Matrix matrixC = matrixA * matrixB;
        CompositeData::Matrix matrixD = matrixA + matrixB;

        //Impresión de cada matriz con el método to_string()
        cout<<"Matriz A: "<<endl;
        cout<<matrixA.to_string()<<endl;

        cout<<"Matriz B: "<<endl;
        cout<<matrixB.to_string()<<endl;

        cout<<"Matriz C, Multiplicacion AxB"<<endl;
        cout<<matrixC.to_string()<<endl;

        cout<<"Matriz D, Suma de A+B"<<endl;
        cout<<matrixD.to_string()<<endl;

        system("PAUSE");

        //Regresamos al menú principal
        mainMenu();
    }

    //Mensaje de Exit
    void Menu::exit(){
        system("CLS");
        //Despedida
        cout<<"Saliendo del Programa...\n"<<endl;
        cout<<"Programa Hecho por: Mariscal Rodriguez Omar Jesus"<<endl;
        cout<<"Materia: Estructuras de Datos"<<endl;
        cout<<"Profesor: Gutierrez Hernandez Alfredo.\n"<<endl;
        cout<<"Tenga un Lindo Dia :)"<<endl;
    }
}


