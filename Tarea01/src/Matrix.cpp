/*Nombre: Mariscal Rodríguez Omar Jesús
Fecha de Entrega: 17 de Agosto de 2025 
Problema: Actividad de Aprendizaje 01: Tipos de Dato Primitivo y Tipos de Datos Compuestos
Archivo: Matrix.cpp*/


#include <iostream> //Entrada y Salida Estándar
#include <iomanip> //Crear tabla para imprimir la Matrix
#include <random> //Biblioteca para dar reales aleatorios
#include <sstream> //Para facilitar el método to_string
#include "Matrix.h" //Definición de la clase

using CompositeData::Matrix;

//Método Constructor
Matrix::Matrix(int size){
    this->size = size;
}

//Setter del Size de la matriz
void Matrix::setSize(int size){
    this->size = size;
}

void Matrix::zeros(){ //Inicializar las cantidades en 0 como buena practica
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            this->values[i][j] = 0;
}

void Matrix::randomizer(){
    //Generar una serie de números pseudoaleatorios para llenar la matriz
    std::random_device seed; //Un generador de semilla aleatoria en cualquier ejecución
    std::default_random_engine engine(seed()); //Usamos el motor aleatorio por defecto, el más simple, con la semilla generada
    std::uniform_real_distribution<float> distribution(-100.00,100.00); //Crear el objeto de una distribución normal de reales en el rango de -100.00 a 100.00

    //Ciclo anidado para llenar la matriz con los números pesudoaleatorios
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            values[i][j] = (round(distribution(engine) * 100) / 100);
}



std::string Matrix::to_string(){
    std::ostringstream oss;
    const int width = 10; //Anchura de cada celda
    //Creación de una función lambda para imprimir una línea
    auto linea = [&](){
        oss << "+";

        for(int i = 0; i < size; i ++)
            oss << std::string(width,'-')<<"+";

        oss<<"\n";
    };

    linea();

    //Imprimir los valores valores de manera ordenada
    for(int i = 0; i < size; i++){
         for(int j = 0; j < size; j++){
            oss << "|" << std::setw(width) << std::left << values[i][j];
        }
      oss<<"|"<<"\n";
        linea();
    }

    return oss.str(); //Retornar el string
}   


//Operador de Suma
Matrix Matrix::operator+(const Matrix& otro)const {
    Matrix sum(size);
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            sum.values[i][j] = this->values[i][j] + otro.values[i][j];
    return sum;
}

//Operador de Multiplicación
Matrix Matrix::operator*(const Matrix& otro) const{
    Matrix times(size);
    //Recorrer ambas matrices en un determinado orden siguiendo el algoritmo de multiplicación.
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)             
            for(int k = 0; k < size; k++)
                times.values[i][j] += (this->values[i][k] * otro.values[k][j]);
    return times;
}