/*Nombre: Mariscal Rodríguez Omar Jesús
Fecha de Entrega: 17 de Agosto de 2025
Problema: Actividad de Aprendizaje 01: Tipos de Dato Primitivo y Tipos de Datos
Compuestos Archivo: Interfaces.h*/

#pragma once

#include <iostream>

// Namespace de Utilidades varias relacionadas al input
namespace Utilities {
/// @brief Utilidades Varias
class InputUtilities {
 public:
  /// @brief Pedir al usuario un entero positivo en un rango determinado. Se
  /// ejecuta un bucle hasta que se ingrese una cantidad válida
  /// @param  label Texto que se imprimira para pedir la información
  /// @param  lowerLimit Número mínimo que el usuario puede ingresar
  /// @param  upperLimit Numero máxmo que el usuario puede ingresar
  /// @return Seleccion de la selección del usuario.
  static int inputPositiveIntegerLimit(std::string, int, int);
};
}  // namespace Utilities

namespace Menus {
/// @brief Menu Principal y sus distintas bifurcaciones a otros
/// Submenús/Funciones
class Menu {
 public:
  /// @brief Menu Principal desde el que se acceden los demás submenús/funciones
  void mainMenu();

 private:
  /// @brief Mostrar la tabla de Datos
  void dataTypes();
  /// @brief Mostrar el ejemplo de Datos Compuestos (Matrices)
  void compositeData();
  /// @brief Mensaje de despedida
  void exit();
};
}  // namespace Menus