#ifndef __STRINGWRAPPED_H__
#define __STRINGWRAPPED_H__

#include <string>
#include <../lib/nlohmann/json.hpp>

#include <iostream>

using json = nlohmann::json;

class StringWrapper {
private:
    std::string valor;

public:
    // ==================== CONSTRUCTORES ====================
    StringWrapper() : valor("") {}
    StringWrapper(const std::string& v) : valor(v) {}
    StringWrapper(const char* v) : valor(v) {}
    StringWrapper(const StringWrapper& other) : valor(other.valor) {}
    StringWrapper(StringWrapper&& other) noexcept : valor(std::move(other.valor)) {}
    StringWrapper(size_t n, char c) : valor(n, c) {}
    
    // ==================== OPERADORES DE ASIGNACIÓN ====================
    StringWrapper& operator=(const StringWrapper& other) {
        if (this != &other) {
            valor = other.valor;
        }
        return *this;
    }
    
    StringWrapper& operator=(StringWrapper&& other) noexcept {
        if (this != &other) {
            valor = std::move(other.valor);
        }
        return *this;
    }
    
    StringWrapper& operator=(const std::string& v) {
        valor = v;
        return *this;
    }
    
    StringWrapper& operator=(const char* v) {
        valor = v;
        return *this;
    }
    
    StringWrapper& operator=(char c) {
        valor = c;
        return *this;
    }
    
    // ==================== GETTERS Y SETTERS ====================
    const std::string& getValor() const { return valor; }
    std::string& getValor() { return valor; }
    void setValor(const std::string& v) { valor = v; }
    
    // ==================== CONVERSIÓN ====================
    operator std::string() const { return valor; }
    const char* c_str() const { return valor.c_str(); }
    const char* data() const { return valor.data(); }
    
    // ==================== ACCESO A ELEMENTOS ====================
    char& operator[](size_t pos) { return valor[pos]; }
    const char& operator[](size_t pos) const { return valor[pos]; }
    char& at(size_t pos) { return valor.at(pos); }
    const char& at(size_t pos) const { return valor.at(pos); }
    char& front() { return valor.front(); }
    const char& front() const { return valor.front(); }
    char& back() { return valor.back(); }
    const char& back() const { return valor.back(); }
    
    // ==================== CAPACIDAD ====================
    size_t size() const { return valor.size(); }
    size_t length() const { return valor.length(); }
    size_t capacity() const { return valor.capacity(); }
    bool empty() const { return valor.empty(); }
    void reserve(size_t n) { valor.reserve(n); }
    void shrink_to_fit() { valor.shrink_to_fit(); }
    size_t max_size() const { return valor.max_size(); }
    void resize(size_t n) { valor.resize(n); }
    void resize(size_t n, char c) { valor.resize(n, c); }
    
    // ==================== MODIFICADORES ====================
    void clear() { valor.clear(); }
    
    StringWrapper& insert(size_t pos, const std::string& str) {
        valor.insert(pos, str);
        return *this;
    }
    
    StringWrapper& insert(size_t pos, const char* s) {
        valor.insert(pos, s);
        return *this;
    }
    
    StringWrapper& erase(size_t pos = 0, size_t len = std::string::npos) {
        valor.erase(pos, len);
        return *this;
    }
    
    StringWrapper& append(const std::string& str) {
        valor.append(str);
        return *this;
    }
    
    StringWrapper& append(const char* s) {
        valor.append(s);
        return *this;
    }
    
    StringWrapper& append(size_t n, char c) {
        valor.append(n, c);
        return *this;
    }
    
    void push_back(char c) { valor.push_back(c); }
    void pop_back() { valor.pop_back(); }
    
    StringWrapper& replace(size_t pos, size_t len, const std::string& str) {
        valor.replace(pos, len, str);
        return *this;
    }
    
    void swap(StringWrapper& other) { valor.swap(other.valor); }
    
    // ==================== OPERACIONES DE STRING ====================
    size_t find(const std::string& str, size_t pos = 0) const {
        return valor.find(str, pos);
    }
    
    size_t find(const char* s, size_t pos = 0) const {
        return valor.find(s, pos);
    }
    
    size_t find(char c, size_t pos = 0) const {
        return valor.find(c, pos);
    }
    
    size_t rfind(const std::string& str, size_t pos = std::string::npos) const {
        return valor.rfind(str, pos);
    }
    
    size_t rfind(const char* s, size_t pos = std::string::npos) const {
        return valor.rfind(s, pos);
    }
    
    size_t rfind(char c, size_t pos = std::string::npos) const {
        return valor.rfind(c, pos);
    }
    
    size_t find_first_of(const std::string& str, size_t pos = 0) const {
        return valor.find_first_of(str, pos);
    }
    
    size_t find_last_of(const std::string& str, size_t pos = std::string::npos) const {
        return valor.find_last_of(str, pos);
    }
    
    size_t find_first_not_of(const std::string& str, size_t pos = 0) const {
        return valor.find_first_not_of(str, pos);
    }
    
    size_t find_last_not_of(const std::string& str, size_t pos = std::string::npos) const {
        return valor.find_last_not_of(str, pos);
    }
    
    StringWrapper substr(size_t pos = 0, size_t len = std::string::npos) const {
        return StringWrapper(valor.substr(pos, len));
    }
    
    int compare(const StringWrapper& other) const {
        return valor.compare(other.valor);
    }
    
    int compare(const std::string& str) const {
        return valor.compare(str);
    }
    
    int compare(const char* s) const {
        return valor.compare(s);
    }
    
    int compare(size_t pos, size_t len, const std::string& str) const {
        return valor.compare(pos, len, str);
    }
    
    // ==================== OPERADORES DE CONCATENACIÓN ====================
    StringWrapper operator+(const StringWrapper& other) const {
        return StringWrapper(valor + other.valor);
    }
    
    StringWrapper operator+(const std::string& str) const {
        return StringWrapper(valor + str);
    }
    
    StringWrapper operator+(const char* s) const {
        return StringWrapper(valor + s);
    }
    
    StringWrapper operator+(char c) const {
        return StringWrapper(valor + c);
    }
    
    StringWrapper& operator+=(const StringWrapper& other) {
        valor += other.valor;
        return *this;
    }
    
    StringWrapper& operator+=(const std::string& str) {
        valor += str;
        return *this;
    }
    
    StringWrapper& operator+=(const char* s) {
        valor += s;
        return *this;
    }
    
    StringWrapper& operator+=(char c) {
        valor += c;
        return *this;
    }
    
    // ==================== OPERADORES DE COMPARACIÓN ====================
    bool operator==(const StringWrapper& other) const {
        return valor == other.valor;
    }
    
    bool operator==(const std::string& str) const {
        return valor == str;
    }
    
    bool operator==(const char* s) const {
        return valor == s;
    }
    
    bool operator!=(const StringWrapper& other) const {
        return valor != other.valor;
    }
    
    bool operator!=(const std::string& str) const {
        return valor != str;
    }
    
    bool operator!=(const char* s) const {
        return valor != s;
    }
    
    bool operator<(const StringWrapper& other) const {
        return valor < other.valor;
    }
    
    bool operator<(const std::string& str) const {
        return valor < str;
    }
    
    bool operator<=(const StringWrapper& other) const {
        return valor <= other.valor;
    }
    
    bool operator>(const StringWrapper& other) const {
        return valor > other.valor;
    }
    
    bool operator>=(const StringWrapper& other) const {
        return valor >= other.valor;
    }
    
    // ==================== ITERADORES ====================
    using iterator = std::string::iterator;
    using const_iterator = std::string::const_iterator;
    using reverse_iterator = std::string::reverse_iterator;
    using const_reverse_iterator = std::string::const_reverse_iterator;
    
    iterator begin() { return valor.begin(); }
    const_iterator begin() const { return valor.begin(); }
    const_iterator cbegin() const { return valor.cbegin(); }
    
    iterator end() { return valor.end(); }
    const_iterator end() const { return valor.end(); }
    const_iterator cend() const { return valor.cend(); }
    
    reverse_iterator rbegin() { return valor.rbegin(); }
    const_reverse_iterator rbegin() const { return valor.rbegin(); }
    const_reverse_iterator crbegin() const { return valor.crbegin(); }
    
    reverse_iterator rend() { return valor.rend(); }
    const_reverse_iterator rend() const { return valor.rend(); }
    const_reverse_iterator crend() const { return valor.crend(); }
    
    // ==================== SERIALIZACIÓN JSON ====================
    json toJson() const {
        return json(valor);
    }
    
    void fromJson(const json& j) {
        valor = j.get<std::string>();
    }
    
    // ==================== OPERADORES DE STREAM ====================
    friend std::ostream& operator<<(std::ostream& os, const StringWrapper& sw) {
        os << sw.valor;
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, StringWrapper& sw) {
        is >> sw.valor;
        return is;
    }
    
    friend std::istream& getline(std::istream& is, StringWrapper& sw) {
        return std::getline(is, sw.valor);
    }
    
    friend std::istream& getline(std::istream& is, StringWrapper& sw, char delim) {
        return std::getline(is, sw.valor, delim);
    }
};

// ==================== OPERADORES GLOBALES ====================
// Para permitir concatenación con string a la izquierda
inline StringWrapper operator+(const std::string& str, const StringWrapper& sw) {
    return StringWrapper(str + sw.getValor());
}

inline StringWrapper operator+(const char* s, const StringWrapper& sw) {
    return StringWrapper(std::string(s) + sw.getValor());
}

inline StringWrapper operator+(char c, const StringWrapper& sw) {
    return StringWrapper(c + sw.getValor());
}

// Operadores de comparación globales
inline bool operator==(const std::string& str, const StringWrapper& sw) {
    return str == sw.getValor();
}

inline bool operator==(const char* s, const StringWrapper& sw) {
    return std::string(s) == sw.getValor();
}

inline bool operator!=(const std::string& str, const StringWrapper& sw) {
    return str != sw.getValor();
}

inline bool operator!=(const char* s, const StringWrapper& sw) {
    return std::string(s) != sw.getValor();
}



#endif // __STRINGWRAPPED_H__