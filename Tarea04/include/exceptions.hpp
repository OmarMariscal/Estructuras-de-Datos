#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <exception>
#include <string>

class Exception : public std::exception {
 private:
  std::string msg;

 public:
  Exception() noexcept : msg("Error Indefinido") {}
  Exception(const Exception& ex) noexcept : msg(ex.msg) {}
  Exception(const std::string& m) : msg(m) {}
  Exception& operator=(const Exception& ex) noexcept {
    msg = ex.msg;
    return *this;
  }

  virtual ~Exception() {}
  virtual const char* what() const noexcept { return msg.c_str(); }
};

class OperationCanceledException : public Exception {
 public:
  OperationCanceledException() noexcept : Exception("Operacion Cancelada") {}

  OperationCanceledException(const OperationCanceledException& ex) noexcept
      : Exception(ex) {}

  OperationCanceledException(const std::string& m) : Exception(m) {}

  OperationCanceledException& operator=(
      const OperationCanceledException& ex) noexcept {
    Exception::operator=(ex);  // reutiliza asignación de la base
    return *this;
  }

  virtual ~OperationCanceledException() {}
};

#endif  // __EXCEPTIONS_H__