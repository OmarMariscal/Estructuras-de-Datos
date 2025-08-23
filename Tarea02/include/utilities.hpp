#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <iostream>
#include <string>
#include <limits>

template <typename T>
class Utilities{
    public:

        static T readNumberRange(const T&, const T&, const std::string&);
        static T readPositiveNumber(const std::string&);
};

template <typename T>
T Utilities<T>::readNumberRange(const T& lowerLimit, const T& upperLimit, const std::string& prompt){
    T value;

    while(true){
        std::cout<<prompt;
        std::cin>>value;

        //Verificar si se ingresó algo diferente a un número
        if(std::cin.fail()){
            std::cin.clear(); //Limpiar el error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Vaciar el buffer
            system("CLS");
            std::cout<<"Entrada invalida.\n Por favor, intetelo nuevamente.\n\n";
            system("PAUSE");
            continue; //Volver al inicio del loop
        }

        //Vaciar el buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        //Verificar el rango
        if(value < lowerLimit || value > upperLimit){
            system("CLS");
            std::cout<<"Numero fuera de rango.\n Por favor, intetelo nuevamente.\n\n";
            continue; //Volver al inicio de la iteción
        }

        //Entrada correcta
        return value;
    } //Bucle indefinido hasta que se dé un valor compelto   
}

template <typename T>
T Utilities<T>::readPositiveNumber(const std::string& prompt){
    T value;

    while(true){
        std::cout<<prompt;
        std::cin>>value;

        //Verificar si se ingresó algo diferente a un número
        if(std::cin.fail()){
            std::cin.clear(); //Limpiar el error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Vaciar el buffer
            system("CLS");
            std::cout<<"Entrada invalida.\n Por favor, intetelo nuevamente.\n\n";
            system("PAUSE");
            continue; //Volver al inicio del loop
        }

        //Vaciar el buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        //Verificar el rango
        if(value <= 0){
            system("CLS");
            std::cout<<"Numero fuera de rango.\n Por favor, intetelo nuevamente.\n\n";
            continue; //Volver al inicio de la iteción
        }

        //Entrada correcta
        return value;
    } //Bucle indefinido hasta que se dé un valor compelto   
}

#endif // __UTILITIES_H__