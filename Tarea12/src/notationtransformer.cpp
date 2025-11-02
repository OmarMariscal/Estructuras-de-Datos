#include "notationtransformer.hpp"
#include <iostream>

// Operadores permitidos
bool NotationTransformer::isOperator(const char& caracter) const {
  return caracter == '+' || caracter == '-' || caracter == '*' ||
         caracter == '/' || caracter == '^';
}

// Darle un valor numérico para la comparación
int NotationTransformer::getPrecedence(const char& caracter) const {
  switch (caracter) {
    case '^':
      return 3;
    case '*':
    case '/':
      return 2;
    case '+':
    case '-':
      return 1;
    default:
      return 0;
  }
}

bool NotationTransformer::isValidExpresion(const Queue<char>& infixExpresion) {
  // Verificar si una notación Infija es válida
  if (infixExpresion.isEmpty())
    return false;

  Queue<char> q = infixExpresion;

  // Esta variable determinará si se espera un operador o un operando a lo largo
  // de las validaciones
  bool expectedOperand = true;
  // El balace de paréntesis, como debe haber un número par, sumaremos +1 por
  // cada ( y restaremos -1 por cada ). Tiene que estar en 0's a final
  int parenBalance = 0;
  // Número de operandos
  int operands = 0;
  // Número de Operadores
  int operators = 0;
  // Caracter anterior para hacer comparativas
  char prev = '\0';

  // Si esta vacía
  while (!q.isEmpty()) {
    char c = q.dequeue();

    // Si es una Variable o un dígito
    if (std::isalnum(static_cast<unsigned char>(c))) {
      operands++;
      // Si se inicia con un paréntesis de cierre es invalida
      if (prev == ')')
        return false;
      expectedOperand = false;  // Ahora esperamos un operador no un operando
    }

    else if (c == '(') {
      parenBalance++;                       // Balance de Paréntesis
      if (!expectedOperand && prev != '(')  // Si se ingresa un operador
        return false;
      expectedOperand = true;
    }

    else if (c == ')') {
      if (parenBalance == 0)  // Si no se han agregado paréntesis de apertura
        return false;
      if (expectedOperand)  // Si sigue inmediatamente después de un operador
        return false;
      parenBalance--;  // Balanceamos los paréntesis
      expectedOperand = false;
    }

    else if (this->isOperator(c)) {  // Si es un operador
      if (expectedOperand)           // Si se juntan dos operando
        return false;
      operators++;
      expectedOperand = true;
    }

    else {
      return false;  // Cualquier otra entrada será inválida
    }

    prev = c;
  }

  // Validaciones Varias
  if (parenBalance != 0)
    return false;
  if (expectedOperand)
    return false;
  if (operands == 0)
    return false;
  if (operands != operators + 1)
    return false;
  return true;
}

NotationTransformer::NotationTransformer() {}

NotationTransformer::NotationTransformer(const NotationTransformer& other)
    : infixQueue(other.infixQueue) {}

NotationTransformer::NotationTransformer(const Queue<char>& iQ) {
  this->setInflixQueue(iQ);
}

NotationTransformer::~NotationTransformer() = default;

void NotationTransformer::setInflixQueue(const Queue<char>& infixNotation) {
  if (this->isValidExpresion(infixNotation))  // Si es válida
    this->infixQueue = infixNotation;
  else  // Excepción si no es válida
    throw NotationTransformerExceptions::InvalidExpresion();
}

void NotationTransformer::transformToPosfija() {
  // Verificar que hay una cola de entrada.
  // En el código nunca debería haber un
  if (infixQueue.isEmpty())
    throw NotationTransformerExceptions::NotInfixData();

  char caracter;
  // Vacías si tiene algo el resultado
  while (!postfixQueue.isEmpty())
    postfixQueue.dequeue();

  // Operar sobre la cola de entrada en Infija
  while (!infixQueue.isEmpty()) {
    caracter = infixQueue.dequeue();  // Capturamos el primer caracter

    if (caracter == '(') {
      operatorStack.push(caracter);  // Agregamos si es paréntesis de apertura
      continue;
    }

    if (this->isOperator(caracter)) {  // Si es operador, vaciamos los que sean
                                       // de mayor o igual valor
      bool isRightAssociative = (caracter == '^');

      while (
          !operatorStack.isEmpty() && operatorStack.getTop() != '(' &&
          ((!isRightAssociative &&
            getPrecedence(caracter) <= getPrecedence(operatorStack.getTop())) ||
           (isRightAssociative &&
            getPrecedence(caracter) < getPrecedence(operatorStack.getTop()))))
        postfixQueue.enqueue(operatorStack.pop());

      operatorStack.push(caracter);  // Guardamos el operador
      continue;
    } else if (caracter ==
               ')') {  // Paréntesis de cierre saca todo de la pila hasta
                       // encontrarse con un paréntesis de apertura
      while (operatorStack.getTop() != '(') {
        postfixQueue.enqueue(operatorStack.pop());
      }
      operatorStack.pop();  // Se saca el paréntesis de apertura encontrado
      continue;
    }
    postfixQueue.enqueue(
        caracter);  // Si no es ni operador ni paréntesis, se considera operando
  }

  while (!operatorStack.isEmpty())  // Vacíamos al resultado el resto de
                                    // operadores en la pila
    postfixQueue.enqueue(operatorStack.pop());
}

Queue<char> NotationTransformer::stringToQueue(const std::string& s) {
  Queue<char> q;

  for (int i(0); i < s.size(); ++i) {
    char c = s[i];
    if (c == ' ')  // Ignorar Espacios
      continue;
    q.enqueue(c);
  }
  return q;
}

std::string NotationTransformer::postFixToString() const {
  Queue<char> postfix = this->postfixQueue;
  string result;
  while (!postfix.isEmpty())
    result += postfix.dequeue();
  return result;
}

NotationTransformer& NotationTransformer::operator=(
    const NotationTransformer& other) {
  this->infixQueue = other.infixQueue;
  this->postfixQueue = other.postfixQueue;
  this->operatorStack = other.operatorStack;

  return *this;
}
