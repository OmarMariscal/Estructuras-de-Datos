#ifndef __NOTATIONTRANSFORMER_H__
#define __NOTATIONTRANSFORMER_H__

#include <string>

#include "queue.hpp"
#include "stack.hpp"

#include "ownexceptions.hpp"

class NotationTransformer {
 private:
  Queue<char>& infixQueue;
  Queue<char>& postfixQueue;
  Stack<char>& operatorStack;

  bool isOperator(const char&) const;
  int getPrecedence(const char&) const;
  bool isValidExpresion(const Queue<char>&);

 public:
  NotationTransformer();
  NotationTransformer(const NotationTransformer&);
  NotationTransformer(const Queue<char>&);

  void setInflixQueue(const Queue<char>&);
  void transformToPosfija();

  static Queue<char> stringToQueue(const std::string&);
  std::string postFixToString() const;

  NotationTransformer& operator=(const NotationTransformer&);
};

#endif  // __NOTATIONTRANSFORMER_H__