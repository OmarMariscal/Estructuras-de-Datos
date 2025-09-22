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

    class MemoryOverflow : public std::runtime_error {
    public:
    explicit MemoryOverflow(const std::string& msg = "Desbordamiento de Memoria")
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

    class NumberNotPositive : public std::runtime_error{
        public:
            explicit NumberNotPositive(const std::string& msg = "Esta entrada debe ser mayor a 0") : runtime_error(msg){}
    };
}  // namespace InputExceptions

namespace DateExceptions{
    class InvalidDate : public std::runtime_error{
        public:
            explicit InvalidDate(const std::string& msg = "La fecha es invalida") : runtime_error(msg) {}
    };
}

namespace RecipeExceptions{
    class RepeatedIngredient : public std::runtime_error {
        public:
            explicit RepeatedIngredient(const std::string& msg = "El ingrediente ya esta registrado en la lista.") : runtime_error(msg) {}
    };

    class NonExistenIngredient : public std::runtime_error{
        public:
            explicit NonExistenIngredient(const std::string& msg = "El ingrediente no existe en la lista.") : runtime_error(msg) {}
    };
}

namespace RecipeBookExceptions{
    class IdNotAvalible : std::runtime_error{
        public:
            explicit IdNotAvalible(const std::string& msg = "El Id ya esta registrado.") : runtime_error(msg) {}
   };

   class RecipeNotFound : std::runtime_error{
        public:
            explicit RecipeNotFound(const std::string& msg = "La receta no esta registrada") : runtime_error(msg) {}
   };
}

#endif  // __OWNEXCEPTIONS_H__