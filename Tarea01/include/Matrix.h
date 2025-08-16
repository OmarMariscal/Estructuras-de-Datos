/*Nombre: Mariscal Rodríguez Omar Jesús
Fecha de Entrega: 17 de Agosto de 2025
Problema: Actividad de Aprendizaje 01: Tipos de Dato Primitivo y Tipos de Datos
Compuestos Archivo: Matrix.h*/

#pragma once

#include <iostream>

namespace CompositeData {
/// @brief Clase de matrices y operaciones definidas entre ellas.
class Matrix {
 private:
  int size;
  float values[10][10];

 public:
  /// @brief Constructor para incializar Size
  /// @param  Size tamaño que se tomará en cuenta para las operaciones y
  /// rellenado
  Matrix(int);

  /// @brief Limpiar la matriz y dejarla llena de ceros
  void zeros();

  /// @brief Llenar el size con valores reales aleatorios en el rango
  /// establecido
  void randomizer();

  /// @brief Modificar el Size de lo que se tomará en cuenta para las
  /// operaciones
  /// @param  Size Nuevo tamaño para tomarlo en cuenta
  void setSize(int);

  /// @brief Representar la matriz en un string
  /// @return String con una representación de los valores
  std::string to_string();                     // Llevarlo a un formato legible
  Matrix operator+(const Matrix& otro) const;  // Sobrecarga del operador suma
  Matrix operator*(
      const Matrix& otro) const;  // Sobrecarga del operador multiplicación
};
}  // namespace CompositeData