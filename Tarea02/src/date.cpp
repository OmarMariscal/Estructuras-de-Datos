#include "date.hpp"

// Constructor base que usa chorono para inicializar la fecha en hoy
Date::Date() {
  auto now = std::chrono::system_clock::now();
  std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
  std::tm localTime = *std::localtime(&currentTime);

  this->year = localTime.tm_year + 1900;
  this->month = localTime.tm_mon + 1;
  this->day = localTime.tm_mday;
}

// Constructor Copia
Date::Date(const Date& other)
    : year(other.year), month(other.month), day(other.day) {}

// Constructor Paramétrico
Date::Date(const int& y, const int& m, const int& d)
    : year(y), month(m), day(d) {}

// Getter's
int Date::getYear() const {
  return this->year;
}

int Date::getMonth() const {
  return this->month;
}

int Date::getDay() const {
  return this->day;
}

// toString()
std::string Date::toString() const {
  // Utilizamos un arreglo para imprimir la fecha de texto y no solo en formato
  // dd/mm/aaaa
  std::string months[12] = {"Enero",      "Febrero", "Marzo",     "Abril",
                            "Mayo",       "Junio",   "Julio",     "Agosto",
                            "Septiembre", "Octubre", "Noviembre", "Diciembre"};
  return std::to_string(day) + " de " + months[month - 1] + " del " +
         std::to_string(year);
}

// Setter's
void Date::setYear(const int& year) {
  auto now = std::chrono::system_clock::now();
  std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
  std::tm dateNow = *std::localtime(&timeNow);

  // Lanzamos una excepción si se intenta poner un año más adelante del actual o
  // menor a la configuración
  if (year < configure::minimumYear || year > (dateNow.tm_year + 1900)) {
    throw std::out_of_range("El anio debe estar entre el rango " +
                            std::to_string(configure::minimumYear) + " y " +
                            std::to_string(dateNow.tm_year + 1900));
  }
  this->year = year;
}

void Date::setMonth(const int& month) {
  // Lanzamos excepción si se intenta poner un mes inválido
  if (month < 0 || month > 12)
    throw std::out_of_range(
        "El mes debe estar entre 1 (Enero) y 12 (Diciembre).");
  this->month = month;
}

void Date::setDay(const int& day) {
  // Lanzamos excepción si se intenta poner un día inválido
  if (day < 0 || day > 31)
    throw std::out_of_range("El dia es invalido");
  this->day = day;
}

Date& Date::operator=(const Date& other) {
  this->year = other.year;
  this->month = other.month;
  this->day = other.day;

  return *this;
}
