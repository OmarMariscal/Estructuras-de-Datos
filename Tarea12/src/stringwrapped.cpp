#include "stringwrapped.hpp"
// ==================== CONSTRUCTORES ====================
StringWrapper::StringWrapper() : valor("") {}
StringWrapper::StringWrapper(const std::string& v) : valor(v) {}
StringWrapper::StringWrapper(const char* v) : valor(v) {}
StringWrapper::StringWrapper(const StringWrapper& other) : valor(other.valor) {}
StringWrapper::StringWrapper(StringWrapper&& other) noexcept : valor(std::move(other.valor)) {}
StringWrapper::StringWrapper(size_t n, char c) : valor(n, c) {}

// ==================== OPERADORES DE ASIGNACIÓN ====================
StringWrapper& StringWrapper::operator=(const StringWrapper& other) {
    if (this != &other) {
        valor = other.valor;
    }
    return *this;
}

StringWrapper& StringWrapper::operator=(StringWrapper&& other) noexcept {
    if (this != &other) {
        valor = std::move(other.valor);
    }
    return *this;
}

StringWrapper& StringWrapper::operator=(const std::string& v) {
    valor = v;
    return *this;
}

StringWrapper& StringWrapper::operator=(const char* v) {
    valor = v;
    return *this;
}

StringWrapper& StringWrapper::operator=(char c) {
    valor = c;
    return *this;
}

// ==================== MODIFICADORES ====================
void StringWrapper::clear() { valor.clear(); }

StringWrapper& StringWrapper::insert(size_t pos, const std::string& str) {
    valor.insert(pos, str);
    return *this;
}

StringWrapper& StringWrapper::insert(size_t pos, const char* s) {
    valor.insert(pos, s);
    return *this;
}

StringWrapper& StringWrapper::erase(size_t pos, size_t len) {
    valor.erase(pos, len);
    return *this;
}

StringWrapper& StringWrapper::append(const std::string& str) {
    valor.append(str);
    return *this;
}

StringWrapper& StringWrapper::append(const char* s) {
    valor.append(s);
    return *this;
}

StringWrapper& StringWrapper::append(size_t n, char c) {
    valor.append(n, c);
    return *this;
}

void StringWrapper::push_back(char c) { valor.push_back(c); }

void StringWrapper::pop_back() { valor.pop_back(); }

StringWrapper& StringWrapper::replace(size_t pos, size_t len, const std::string& str) {
    valor.replace(pos, len, str);
    return *this;
}

void StringWrapper::swap(StringWrapper& other) { valor.swap(other.valor); }

// ==================== OPERADORES DE CONCATENACIÓN ====================
StringWrapper& StringWrapper::operator+=(const StringWrapper& other) {
    valor += other.valor;
    return *this;
}

StringWrapper& StringWrapper::operator+=(const std::string& str) {
    valor += str;
    return *this;
}

StringWrapper& StringWrapper::operator+=(const char* s) {
    valor += s;
    return *this;
}

StringWrapper& StringWrapper::operator+=(char c) {
    valor += c;
    return *this;
}

// ==================== OPERADORES DE STREAM ====================
// Nota: Las funciones amigas no llevan el prefijo StringWrapper::
std::ostream& operator<<(std::ostream& os, const StringWrapper& sw) {
    os << sw.valor;
    return os;
}

std::istream& operator>>(std::istream& is, StringWrapper& sw) {
    is >> sw.valor;
    return is;
}

std::istream& getline(std::istream& is, StringWrapper& sw) {
    return std::getline(is, sw.valor);
}

std::istream& getline(std::istream& is, StringWrapper& sw, char delim) {
    return std::getline(is, sw.valor, delim);
}