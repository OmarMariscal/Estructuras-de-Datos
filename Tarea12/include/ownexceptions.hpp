#ifndef __OWNEXCEPTIONS_H__
#define __OWNEXCEPTIONS_H__

#include <stdexcept>
#include <string>

namespace DataContainersExceptions {
class MemoryDeficiency : public std::runtime_error {
 public:
  explicit MemoryDeficiency(const std::string& msg = "Insuficiencia de Memoria")
      : std::runtime_error(msg) {}
};

class InvalidPosition : public std::runtime_error {
 public:
  explicit InvalidPosition(
      const std::string& msg = "La posicion Ingresada es Invalida")
      : std::runtime_error(msg) {}
};
}  // namespace DataContainersExceptions

namespace InputExceptions {
class InvalidOption : public std::runtime_error {
 public:
  explicit InvalidOption(
      const std::string& msg = "La opcion ingresada esta fuera de rango")
      : runtime_error(msg) {}
};

class EmptyString : public std::runtime_error {
 public:
  explicit EmptyString(
      const std::string& msg = "El string no puede estar vacio")
      : runtime_error(msg) {}
};

class OperationCanceledException : public std::runtime_error {
 public:
  explicit OperationCanceledException(
      const std::string msg = "Operacion Cancelada")
      : runtime_error(msg) {}
};

class NumberNotPositive : public std::runtime_error {
 public:
  explicit NumberNotPositive(
      const std::string& msg = "Esta entrada debe ser mayor a 0")
      : runtime_error(msg) {}
};
}  // namespace InputExceptions

namespace NotationTransformerExceptions {
class InvalidExpresion : public std::runtime_error {
 public:
  explicit InvalidExpresion(
      const std::string& msg = "La Expresion No es Valida")
      : std::runtime_error(msg) {}
};

class NotOperator : public std::runtime_error {
 public:
  explicit NotOperator(
      const std::string& msg = "No es un operador para asignarle precedencia.")
      : std::runtime_error(msg) {}
};

class NotInfixData : public std::runtime_error {
 public:
  explicit NotInfixData(
      const std::string& msg = "No se ha capturado la notacion infija.")
      : std::runtime_error(msg) {}
};
}  // namespace NotationTransformerExceptions

namespace NodeExceptions {
class MemoryNotAvaliable : std::runtime_error {
 public:
  explicit MemoryNotAvaliable(const std::string& msg = "Excepcion del Nodo")
      : runtime_error(msg) {}
};
}  // namespace NodeExceptions

#endif  // __OWNEXCEPTIONS_H__