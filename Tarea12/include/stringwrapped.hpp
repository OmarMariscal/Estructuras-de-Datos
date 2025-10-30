#ifndef __STRINGWRAPPER_H__
#define __STRINGWRAPPER_H__

#include <string>
#include <iostream>

class StringWrapper {
private:
    std::string valor;

public:
    // ==================== CONSTRUCTORES ====================
    StringWrapper();
    StringWrapper(const std::string& v);
    StringWrapper(const char* v);
    StringWrapper(const StringWrapper& other);
    StringWrapper(StringWrapper&& other) noexcept;
    StringWrapper(size_t n, char c);
    
    // ==================== OPERADORES DE ASIGNACIÓN ====================
    StringWrapper& operator=(const StringWrapper& other);
    StringWrapper& operator=(StringWrapper&& other) noexcept;
    StringWrapper& operator=(const std::string& v);
    StringWrapper& operator=(const char* v);
    StringWrapper& operator=(char c);
    
    // ==================== GETTERS Y SETTERS (inline) ====================
    const std::string& getValor() const { return valor; }
    std::string& getValor() { return valor; }
    void setValor(const std::string& v) { valor = v; }
    std::string toString() const { return valor; }
    
    // ==================== CONVERSIÓN (inline) ====================
    operator std::string() const { return valor; }
    const char* c_str() const { return valor.c_str(); }
    const char* data() const { return valor.data(); }
    
    // ==================== ACCESO A ELEMENTOS (inline) ====================
    char& operator[](size_t pos) { return valor[pos]; }
    const char& operator[](size_t pos) const { return valor[pos]; }
    char& at(size_t pos) { return valor.at(pos); }
    const char& at(size_t pos) const { return valor.at(pos); }
    char& front() { return valor.front(); }
    const char& front() const { return valor.front(); }
    char& back() { return valor.back(); }
    const char& back() const { return valor.back(); }
    
    // ==================== CAPACIDAD (inline) ====================
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
    void clear();
    StringWrapper& insert(size_t pos, const std::string& str);
    StringWrapper& insert(size_t pos, const char* s);
    StringWrapper& erase(size_t pos = 0, size_t len = std::string::npos);
    StringWrapper& append(const std::string& str);
    StringWrapper& append(const char* s);
    StringWrapper& append(size_t n, char c);
    void push_back(char c);
    void pop_back();
    StringWrapper& replace(size_t pos, size_t len, const std::string& str);
    void swap(StringWrapper& other);
    
    // ==================== OPERACIONES DE STRING (inline) ====================
    size_t find(const std::string& str, size_t pos = 0) const { return valor.find(str, pos); }
    size_t find(const char* s, size_t pos = 0) const { return valor.find(s, pos); }
    size_t find(char c, size_t pos = 0) const { return valor.find(c, pos); }
    size_t rfind(const std::string& str, size_t pos = std::string::npos) const { return valor.rfind(str, pos); }
    size_t rfind(const char* s, size_t pos = std::string::npos) const { return valor.rfind(s, pos); }
    size_t rfind(char c, size_t pos = std::string::npos) const { return valor.rfind(c, pos); }
    size_t find_first_of(const std::string& str, size_t pos = 0) const { return valor.find_first_of(str, pos); }
    size_t find_last_of(const std::string& str, size_t pos = std::string::npos) const { return valor.find_last_of(str, pos); }
    size_t find_first_not_of(const std::string& str, size_t pos = 0) const { return valor.find_first_not_of(str, pos); }
    size_t find_last_not_of(const std::string& str, size_t pos = std::string::npos) const { return valor.find_last_not_of(str, pos); }
    StringWrapper substr(size_t pos = 0, size_t len = std::string::npos) const { return StringWrapper(valor.substr(pos, len)); }
    int compare(const StringWrapper& other) const { return valor.compare(other.valor); }
    int compare(const std::string& str) const { return valor.compare(str); }
    int compare(const char* s) const { return valor.compare(s); }
    int compare(size_t pos, size_t len, const std::string& str) const { return valor.compare(pos, len, str); }

    // ==================== OPERADORES (la mayoría son inline) ====================
    StringWrapper operator+(const StringWrapper& other) const { return StringWrapper(valor + other.valor); }
    StringWrapper operator+(const std::string& str) const { return StringWrapper(valor + str); }
    StringWrapper operator+(const char* s) const { return StringWrapper(valor + s); }
    StringWrapper operator+(char c) const { return StringWrapper(valor + c); }
    StringWrapper& operator+=(const StringWrapper& other);
    StringWrapper& operator+=(const std::string& str);
    StringWrapper& operator+=(const char* s);
    StringWrapper& operator+=(char c);
    
    bool operator==(const StringWrapper& other) const { return valor == other.valor; }
    bool operator==(const std::string& str) const { return valor == str; }
    bool operator==(const char* s) const { return valor == s; }
    bool operator!=(const StringWrapper& other) const { return valor != other.valor; }
    bool operator!=(const std::string& str) const { return valor != str; }
    bool operator!=(const char* s) const { return valor != s; }
    bool operator<(const StringWrapper& other) const { return valor < other.valor; }
    bool operator<(const std::string& str) const { return valor < str; }
    bool operator<=(const StringWrapper& other) const { return valor <= other.valor; }
    bool operator>(const StringWrapper& other) const { return valor > other.valor; }
    bool operator>=(const StringWrapper& other) const { return valor >= other.valor; }
    
    // ==================== ITERADORES (inline) ====================
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
    
    // ==================== OPERADORES DE STREAM (amigos) ====================
    friend std::ostream& operator<<(std::ostream& os, const StringWrapper& sw);
    friend std::istream& operator>>(std::istream& is, StringWrapper& sw);
    friend std::istream& getline(std::istream& is, StringWrapper& sw);
    friend std::istream& getline(std::istream& is, StringWrapper& sw, char delim);
};

// ==================== OPERADORES GLOBALES (deben ser inline en el header) ====================
inline StringWrapper operator+(const std::string& str, const StringWrapper& sw) { return StringWrapper(str + sw.getValor()); }
inline StringWrapper operator+(const char* s, const StringWrapper& sw) { return StringWrapper(std::string(s) + sw.getValor()); }
inline StringWrapper operator+(char c, const StringWrapper& sw) { return StringWrapper(c + sw.getValor()); }

inline bool operator==(const std::string& str, const StringWrapper& sw) { return str == sw.getValor(); }
inline bool operator==(const char* s, const StringWrapper& sw) { return std::string(s) == sw.getValor(); }
inline bool operator!=(const std::string& str, const StringWrapper& sw) { return str != sw.getValor(); }
inline bool operator!=(const char* s, const StringWrapper& sw) { return std::string(s) != sw.getValor(); }

#endif // __STRINGWRAPPER_H__