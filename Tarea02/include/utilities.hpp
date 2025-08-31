/*utilities.hpp es una serie de acciones útiles para reciclar código.
Es una clase abstracta, no necesita instanciarse, y tiene métodos para leer un
rango de números o leer números exclusivamente enteros > 0 Utiliza templates, y
para tener la combinación de templates y métodos estáticos sin complicarse con
el compilador, va en el mismo header. Otra opción para tener los archivos
serparados sería tener un .tpp o indicar la ruta al compilador
*/

#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <iostream>
#include <limits>  //Para verificar que la entrada sea del tipo pedido
#include <string>

template <typename T>
class Utilities {
 public:
  // lectura de datos enteros o flotantes gracias al template
  static T readNumberRange(const T&, const T&, const std::string&);
  static T readPositiveNumber(const std::string&);
};

template <typename T>
T Utilities<T>::readNumberRange(const T& lowerLimit,
                                const T& upperLimit,
                                const std::string& prompt) {
  T value;

  // Iteración perpetua hasta que se introduzca un valor válido
  while (true) {
    std::cout << prompt;  // Mensaje
    std::cin >> value;    // Valor Resultado

    // Verificar si se ingresó algo diferente a un número
    if (std::cin.fail()) {
      std::cin.clear();  // Limpiar el error
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n');  // Vaciar el buffer
      system("CLS");
      std::cout << "Entrada invalida.\n Por favor, intetelo nuevamente.\n\n";
      system("PAUSE");
      continue;  // Volver al inicio del loop
    }

    // Vaciar el buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Verificar el rango
    if (value < lowerLimit || value > upperLimit) {
      system("CLS");
      std::cout
          << "Numero fuera de rango.\n Por favor, intetelo nuevamente.\n\n";
      continue;  // Volver al inicio de la iteción
    }

    // Entrada correcta
    return value;
  }  // Bucle indefinido hasta que se dé un valor compelto
}

// Misma dinámica pero con valores exclusivamente > 0
template <typename T>
T Utilities<T>::readPositiveNumber(const std::string& prompt) {
  T value;

  while (true) {
    std::cout << prompt;
    std::cin >> value;

    // Verificar si se ingresó algo diferente a un número
    if (std::cin.fail()) {
      std::cin.clear();  // Limpiar el error
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n');  // Vaciar el buffer
      system("CLS");
      std::cout << "Entrada invalida.\n Por favor, intetelo nuevamente.\n\n";
      system("PAUSE");
      continue;  // Volver al inicio del loop
    }

    // Vaciar el buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Verificar el rango
    if (value <= 0) {
      system("CLS");
      std::cout
          << "Numero fuera de rango.\n Por favor, intetelo nuevamente.\n\n";
      continue;  // Volver al inicio de la iteción
    }

    // Entrada correcta
    return value;
  }  // Bucle indefinido hasta que se dé un valor compelto
}

#endif  // __UTILITIES_H__