#include <iostream>

#include "exceptions.hpp"

int main(){
    try{
        throw DateExceptions::InvalidDate("La Fecha no es Valida");
    } catch(const DateExceptions::InvalidDate& ex){
        std::cout << ex.what();
    }
    getchar();
}
