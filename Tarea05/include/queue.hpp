#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "ownexceptions.hpp"

using namespace std;

// Definición

template <class T, int ARRAYSIZE = 1024>
class Queue {
 private:
  T data[ARRAYSIZE];
  int frontPos = 0;
  int endPos = ARRAYSIZE - 1;

  void copyAll(const Queue<T, ARRAYSIZE>&);

 public:
  Queue();
  Queue(const Queue<T, ARRAYSIZE>&);

  bool isEmpty() const;
  bool isFull() const;

  void enqueue(const T&);
  T dequeue();

  T& getTop();

  Queue<T, ARRAYSIZE>& operator=(const Queue<T, ARRAYSIZE>&);
};

// Implementación

template <class T, int ARRAYSIZE>
void Queue<T, ARRAYSIZE>::copyAll(const Queue<T, ARRAYSIZE>& other) {
  for (int i = other.frontPos; i <= other.endPos; i++) {
    this->data[i] = other.data[i];
  }
  this->frontPos = other.frontPos;
  this->endPos = other.endPos;
}

template <class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>::Queue() {}

template <class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>::Queue(const Queue<T, ARRAYSIZE>& other) {
  copyAll(other);
}

template <class T, int ARRAYSIZE>
bool Queue<T, ARRAYSIZE>::isEmpty() const {
  return (this->frontPos == this->endPos + 1) ||
         (this->frontPos == 0 && this->endPos == ARRAYSIZE - 1);
}

template <class T, int ARRAYSIZE>
bool Queue<T, ARRAYSIZE>::isFull() const {
  return (this->frontPos == this->endPos + 2) ||
         (this->frontPos == 0 && this->endPos == ARRAYSIZE - 2) ||
         (this->frontPos == 1 && this->endPos == ARRAYSIZE - 1);
}

template <class T, int ARRAYSIZE>
void Queue<T, ARRAYSIZE>::enqueue(const T& data) {
  if (this->isFull())
    throw(DataContainersExceptions::MemoryOverflow());

  this->endPos++;
  if (this->endPos == ARRAYSIZE) {
    this->endPos = 0;
  }

  this->data[this->endPos] = data;
}

template <class T, int ARRAYSIZE>
T Queue<T, ARRAYSIZE>::dequeue() {
  if (this->isEmpty())
    throw(DataContainersExceptions::MemoryDeficiency());

  T result(this->data[this->frontPos]);

  if (++this->frontPos == ARRAYSIZE) {
    this->frontPos = 0;
  }

  return T(result);
}

template <class T, int ARRAYSIZE>
T& Queue<T, ARRAYSIZE>::getTop() {
  if (this->isEmpty())
    throw DataContainersExceptions::MemoryDeficiency();

  return this->data[this->frontPos];
}

template <class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>& Queue<T, ARRAYSIZE>::operator=(
    const Queue<T, ARRAYSIZE>& other) {
  copyAll(other);
  return *this;
}

#endif  // __QUEUE_H__