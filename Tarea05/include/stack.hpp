#ifndef __STACK_H__
#define __STACK_H__

// Definición

#include "ownexceptions.hpp"

template <class T, int ARRAYSIZE = 1024>
class Stack {
 private:
  T data[ARRAYSIZE];
  int top;

  void copyAll(const Stack<T, ARRAYSIZE>&);

 public:
  Stack();
  Stack(const Stack<T, ARRAYSIZE>&);

  bool isEmpty();
  bool isFull();

  void push(const T&);
  T pop();

  T& getTop();

  Stack<T, ARRAYSIZE>& operator=(const Stack<T, ARRAYSIZE>&);
};

// Implementación

template <class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::copyAll(const Stack<T, ARRAYSIZE>& other) {
  int i = 0;

  while (i <= other.top) {
    this->data[i++] = other.data[i];
  }

  this->top = other.top;
}

template <class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>::Stack() : top(-1) {}

template <class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>::Stack(const Stack<T, ARRAYSIZE>& other) {
  copyAll(other);
}

template <class T, int ARRAYSIZE>
bool Stack<T, ARRAYSIZE>::isEmpty() {
  return this->top == -1;
}

template <class T, int ARRAYSIZE>
bool Stack<T, ARRAYSIZE>::isFull() {
  return this->top == (ARRAYSIZE - 1);
}

template <class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::push(const T& data) {
  if (isFull()) {
    throw DataContainersExceptions::MemoryOverflow();
  }

  this->data[++this->top] = data;
}

template <class T, int ARRAYSIZE>
T Stack<T, ARRAYSIZE>::pop() {
  if (isEmpty()) {
    throw DataContainersExceptions::MemoryDeficiency();
  }

  return this->data[this->top--];
}

template <class T, int ARRAYSIZE>
T& Stack<T, ARRAYSIZE>::getTop() {
  if (isEmpty()) {
    throw DataContainersExceptions::MemoryDeficiency();
  }
  return this->data[this->top];
}

template <class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>& Stack<T, ARRAYSIZE>::operator=(
    const Stack<T, ARRAYSIZE>& other) {
  this->copyAll(other);
  return *this;
}

#endif  // __STACK_H__