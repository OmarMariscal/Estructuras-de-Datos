#include "ingredient.hpp"

Ingredient::Ingredient()
    : nameIngredient("default"), amount(0.0), unit("default") {}

Ingredient::Ingredient(const Ingredient& other)
    : nameIngredient(other.nameIngredient),
      amount(other.amount),
      unit(other.unit) {}

Ingredient::Ingredient(const std::string& n,
                       const float& a,
                       const std::string& u)
    : nameIngredient(n), amount(a), unit(u) {}

std::string Ingredient::getNameIngredient() const {
  return this->nameIngredient;
}

float Ingredient::getAmount() const {
  return this->amount;
}

std::string Ingredient::getUnit() const {
  return this->unit;
}

std::string Ingredient::toString() const {
  std::ostringstream oss;
  oss << "    \033[31m-";
  oss << "\033[0m";
  oss << this->nameIngredient;
  oss << std::setfill('.');
  oss << std::setw(25 - this->nameIngredient.size()) << "";
  oss << std::setfill(' ');
  oss << this->amount << " " << this->unit;
  return oss.str();
}

void Ingredient::setNameInredient(const std::string& nameIngredient) {
  if (nameIngredient.empty())
    throw InputExceptions::EmptyString(
        "El nombre del ingrediente no puede estar vacio.");
  this->nameIngredient = nameIngredient;
}

void Ingredient::setAmount(const float& amount) {
  if (amount < 0)
    throw InputExceptions::NumberNotPositive(
        "La cantidad de ingrediente debe ser positiva");
  this->amount = amount;
}

void Ingredient::setUnit(const std::string& unit) {
  if (unit.empty())
    throw InputExceptions::EmptyString(
        "La unidad del ingrediente no puede estar vacia");
  this->unit = unit;
}

bool Ingredient::operator==(const Ingredient& other) const {
  return this->nameIngredient == other.nameIngredient;
}

bool Ingredient::operator!=(const Ingredient& other) const {
  return !(this->nameIngredient == other.nameIngredient);
}

bool Ingredient::operator<(const Ingredient& other) const {
  return this->nameIngredient < other.nameIngredient;
}

bool Ingredient::operator>(const Ingredient& other) const {
  return this->nameIngredient > other.nameIngredient;
}

bool Ingredient::operator<=(const Ingredient& other) const {
  return this->nameIngredient <= other.nameIngredient;
}

bool Ingredient::operator>=(const Ingredient& other) const {
  return this->nameIngredient >= other.nameIngredient;
}

int Ingredient::compare(const Ingredient& other) const {
  return (this->nameIngredient.compare(other.nameIngredient));
}

int Ingredient::compareTo(const Ingredient& ingredientA,
                          const Ingredient& ingredientB) {
  return ingredientA.nameIngredient.compare(ingredientB.nameIngredient);
}

int Ingredient::compareByAmount(const Ingredient& ingredientA,
                                const Ingredient& ingredientB) {
  return ingredientA.amount - ingredientB.amount;
}

int Ingredient::compareByUnit(const Ingredient& ingredientA,
                              const Ingredient& ingredientB) {
  return ingredientA.unit.compare(ingredientB.unit);
}

nlohmann::json Ingredient::toJson() const {
  nlohmann::json js{
      {"name ingredient", this->nameIngredient},
      {"amount", this->amount},
      {"unit", this->unit},
  };
  return js;
}

void Ingredient::fromJson(const nlohmann::json& js) {
  this->nameIngredient = js.at("name ingredient").get<std::string>();
  this->amount = js.at("amount").get<float>();
  this->unit = js.at("unit").get<std::string>();
}

Ingredient& Ingredient::operator=(const Ingredient& other) {
  this->nameIngredient = other.nameIngredient;
  this->amount = other.amount;
  this->unit = other.unit;

  return *this;
}