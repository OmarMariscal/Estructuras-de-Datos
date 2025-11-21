
#ifdef _WIN32
    #include <windows.h> // Solo se incluye si es Windows
#else
    #include <clocale>   // Librería estándar para Linux/Mac
#endif
#include "menu.hpp"


int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001);
    #else
        std::setlocale(LC_ALL, ""); 
    #endif

    Menu menu;
    return 0;
}