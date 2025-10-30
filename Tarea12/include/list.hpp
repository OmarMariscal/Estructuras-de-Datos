#ifndef __LIST_H__
#define __LIST_H__

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

#include "ownexceptions.hpp"

using namespace std;

// Definición
template <class T>
class List {
  class Node;

 public:
  typedef Node* Position;

 private:
  int totalElements = 0;
  class Node {
   private:
    T* dataPtr = nullptr;
    Position prev = nullptr;
    Position next = nullptr;

   public:
    Node();
    Node(const T&);

    ~Node();

    T* getDataPtr();
    T& getData();

    Position getPrev() const;
    Position getNext() const;

    void setDataPtr(T*);
    void setData(const T&);
    void setNext(const Position&);
    void setPrev(const Position&);
  };

  bool isValidPosition(const Position&) const;
  void add(const List<T>&);
  void swapData(Position, Position);

  Position header = nullptr;

 public:
  List();
  List(const List<T>&);

  ~List();

  bool isEmpty() const;

  void insertData(const Position&, const T&);
  void insertSortedData(const T&);
  void deleteData(const Position&);
  int getTotalElements() const;
  Position getFirstPos() const;
  Position getLastPos() const;
  Position getPrevPos(const Position&) const;
  Position getNextPos(const Position&) const;
  Position getNodeAt(int index) const;

  Position findData(const T&) const;
  T& retrieve(const Position&);

  string toString() const;
  string toString(const T&, int(const T&, const T&)) const;

  void sortDataBubble();
  void sortDataInsert();
  void sortDataSelect();
  void sortDataShell();

  void deleteAll();

  List<T>& operator=(const List<T>&);

  void sortDataBubble(int(const T&, const T&));
  void sortDataInsert(int(const T&, const T&));
  void sortDataSelect(int(const T&, const T&));
  void sortDataShell(int(const T&, const T&));

  template <class X>
  friend std::ostream& operator<<(std::ostream&, const List<X>&);
  template <class X>
  friend std::istream& operator>>(std::istream&, List<X>&);
};

// Implementación
// Node
template <class T>
List<T>::Node::Node() {}

template <class T>
List<T>::Node::Node(const T& element) : dataPtr(new T(element)) {
  if (dataPtr == nullptr) {
    throw NodeExceptions::MemoryNotAvaliable("Memoria no disponible, Node");
  }
}

template <class T>
List<T>::Node::~Node() {
  delete this->dataPtr;
}

template <class T>
T* List<T>::Node::getDataPtr() {
  return this->dataPtr;
}

template <class T>
T& List<T>::Node::getData() {
  if (this->dataPtr == nullptr)
    throw NodeExceptions::MemoryNotAvaliable("Dato Inexistente, getData");
  return *this->dataPtr;
}

template <class T>
typename List<T>::Position List<T>::Node::getPrev() const {
  return this->prev;
}

template <class T>
typename List<T>::Position List<T>::Node::getNext() const {
  return this->next;
}

template <class T>
void List<T>::Node::setDataPtr(T* p) {
  this->dataPtr = p;
}

template <class T>
void List<T>::Node::setData(const T& e) {
  if (this->dataPtr == nullptr) {
    this->dataPtr = new T(e);
    if (this->dataPtr == nullptr)
      throw NodeExceptions::MemoryNotAvaliable("Memoria no disponible, setData");
  } else
    *this->dataPtr = e;
}

template <class T>
void List<T>::Node::setPrev(const typename List<T>::Position& pointer) {
  this->prev = pointer;
}

template <class T>
void List<T>::Node::setNext(const typename List<T>::Position& pointer) {
  this->next = pointer;
}

// Lista

template <class T>
bool List<T>::isValidPosition(const Position& pointer) const {
  Position aux(this->header->getNext());

  while (aux != header) {
    if (aux == pointer) {
      return true;
    }
    aux = aux->getNext();
  }

  return false;
}

template <class T>
void List<T>::add(const List<T>& other) {
  Position aux(other.header->getNext()), newNode;

  while (aux != other.header) {
    if (newNode = new Node(aux->getData()) == newNode == nullptr)
      throw DataContainersExceptions::MemoryDeficiency("Memoria no Disponible");

    newNode->setPrev(this->header->getPrev());
    newNode->setNext(this->header);

    this->header->getPrev()->setNext(newNode);
    this->header->setPrev(newNode);
    this->totalElements++;

    aux = aux->getNext();
  }
}

template <class T>
void List<T>::swapData(Position a, Position b) {
  T temp = a->getData();
  a->setData(b->getData());
  b->setData(temp);
}

template <class T>
List<T>::List() : header(new Node), totalElements(0) {
  if (this->header == nullptr)
    throw NodeExceptions::MemoryNotAvaliable("Memoria no Disponible, List");

  this->header->setPrev(this->header);
  this->header->setNext(this->header);
}

template <class T>
List<T>::List(const List<T>& other) : totalElements(other.totalElements) {
  this->add(other);
}

template <class T>
List<T>::~List() {
  this->deleteAll();

  delete this->header;
}

template <class T>
bool List<T>::isEmpty() const {
  return this->header->getNext() == this->header;
}

template <class T>
void List<T>::insertData(const typename List<T>::Position& position,
                         const T& element) {
  if (position != nullptr && !this->isValidPosition(position))
    throw DataContainersExceptions::InvalidPosition();

  Position newNode(new Node(element));
  if (newNode == nullptr)
    throw NodeExceptions::MemoryNotAvaliable("Memoria No Disponible");

  Position insPos(position == nullptr ? header : position);

  newNode->setPrev(insPos);
  newNode->setNext(insPos->getNext());

  insPos->getNext()->setPrev(newNode);
  insPos->setNext(newNode);
  this->totalElements++;
}

template <class T>
void List<T>::insertSortedData(const T& element) {
  Position newNode(new Node(element));
  if (newNode == nullptr)
    throw NodeExceptions::MemoryNotAvaliable("Memoria No Disponible");

  Position aux(this->header->getNext());

  while (aux != this->header && aux->getData() < newNode->getData())
    aux = aux->getNext();

  newNode->setPrev(aux);
  newNode->setNext(aux->getNext());

  aux->getNext()->setPrev(newNode);
  aux->setNext(newNode);
  this->totalElements++;
}

template <class T>
void List<T>::deleteData(const typename List<T>::Position& position) {
  if (!this->isValidPosition(position))
    throw DataContainersExceptions::InvalidPosition();

  position->getPrev()->setNext(position->getNext());
  position->getNext()->setPrev(position->getPrev());

  delete position;
  this->totalElements--;
}

template <class T>
int List<T>::getTotalElements() const {
  return this->totalElements;
}

template <class T>
typename List<T>::Position List<T>::getFirstPos() const {
  return this->isEmpty() ? nullptr : this->header->getNext();
}

template <class T>
typename List<T>::Position List<T>::getLastPos() const {
  return this->isEmpty() ? nullptr : this->header->getPrev();
}

template <class T>
typename List<T>::Position List<T>::getPrevPos(
    const typename List<T>::Position& position) const {
  return position == this->header->getNext() || !this->isValidPosition(position)
             ? nullptr
             : position->getPrev();
}

template <class T>
typename List<T>::Position List<T>::getNextPos(
    const typename List<T>::Position& position) const {
  return position == this->header->getPrev() || !this->isValidPosition(position)
             ? nullptr
             : position->getNext();
}

template <class T>
typename List<T>::Position List<T>::findData(const T& dataSearched) const {
  Position aux(this->header->getNext());

  while (aux != this->header) {
    if (aux->getData() == dataSearched)
      return aux;
    aux = aux->getNext();
  }

  return nullptr;
}

template <class T>
T& List<T>::retrieve(const typename List<T>::Position& p) {
  if (!this->isValidPosition(p))
    throw DataContainersExceptions::InvalidPosition();
  return p->getData();
}

template <class T>
string List<T>::toString() const {
  string result;
  Position aux(this->header->getNext());

  while (aux != this->header) {
    result += aux->getData().toString() + "\n";
    aux = aux->getNext();
  }

  return result;
}

template <class T>
string List<T>::toString(const T& searched, int cmp(const T&, const T&)) const {
  string result;
  Position aux(this->header->getNext());

  while (aux != this->header) {
    if (cmp(searched, aux->getData()) == 0) 
      result += aux->getData().toString() + "\n";
    aux = aux->getNext();
  }
  return result;
}

template <class T>
void List<T>::deleteAll() {
  Position aux;

  while (this->header->getNext() != this->header) {
    aux = this->header->getNext();

    this->header->setNext(aux->getNext());
    delete aux;
  }

  this->header->setPrev(this->header);
  this->totalElements = 0;
}

template <class T>
List<T>& List<T>::operator=(const List<T>& other) {
  this->deleteAll();
  this->add(other);
  this->totalElements = other.totalElements;

  return *this;
}

template <class T>
void List<T>::sortDataBubble() {
  bool swapped;
  typename List<T>::Position lptr = this->header;
  do {
    swapped = false;
    typename List<T>::Position ptr = this->header->getNext();
    while (ptr->getNext() != lptr) {
      typename List<T>::Position nxt = ptr->getNext();

      if (ptr->getData() > nxt->getData()) {
        this->swapData(ptr, nxt);
        swapped = true;
      }
      ptr = ptr->getNext();
    }

    lptr = ptr;
  } while (swapped);
}

template <class T>
void List<T>::sortDataInsert() {
  if (this->isEmpty())
    return;

  typename List<T>::Position current = this->header->getNext()->getNext();

  while (current != this->header) {
    T key = current->getData();
    typename List<T>::Position mover = current->getPrev();

    while (mover != this->header && mover->getData() > key) {
      mover->getNext()->setData(mover->getData());
      mover = mover->getPrev();
    }

    mover->getNext()->setData(key);
    current = current->getNext();
  }
}

template <class T>
void List<T>::sortDataSelect() {
  if (this->isEmpty())
    return;

  Position current = this->header->getNext();
  while (current != this->header) {
    Position minNode = current;
    Position scanner = current->getNext();

    while (scanner != this->header) {
      if (scanner->getData() < minNode->getData())
        minNode = scanner;

      scanner = scanner->getNext();
    }

    if (minNode != current)
      this->swapData(minNode, current);

    current = current->getNext();
  }
}

template <class T>
void List<T>::sortDataShell() {
  int series[] = {4181, 2584, 1597, 987, 610, 377, 233, 144, 89, 55,
                  34,   21,   13,   8,   5,   3,   2,   1,   0};

  int size = 0;
  Position temp = this->getFirstPos();
  while (temp != nullptr) {
    size++;
    temp = temp->getNext();
  }

  int pos = 0;
  int gap = series[pos];

  while (gap > size) {
    gap = series[++pos];
  }

  while (gap > 0) {
    for (int i = gap; i < size; i++) {
      Position nodeI = this->getNodeAt(i);
      T tempData = nodeI->getData();

      int j = i;
      while (j >= gap) {
        Position nodeJMinusGap = this->getNodeAt(j - gap);

        if (nodeJMinusGap->getData() > tempData) {
          Position nodeJ = this->getNodeAt(j);
          nodeJ->setData(nodeJMinusGap->getData());
          j -= gap;
        } else {
          break;
        }
      }

      Position nodeJ = this->getNodeAt(j);
      nodeJ->setData(tempData);
    }

    gap = series[++pos];
  }
}

template <class T>
void List<T>::sortDataBubble(int cmp(const T&, const T&)) {
  if (this->isEmpty() || this->header->getNext()->getNext() == this->header)
    return;

  bool swapped;
  typename List<T>::Position lptr = this->header;
  do {
    swapped = false;
    typename List<T>::Position ptr = this->header->getNext();
    while (ptr->getNext() != lptr) {
      typename List<T>::Position nxt = ptr->getNext();
      if (cmp(ptr->getData(), nxt->getData()) > 0) {
        this->swapData(ptr, nxt);
        swapped = true;
      }
      ptr = ptr->getNext();
    }
    lptr = ptr;
  } while (swapped);
}

template <class T>
void List<T>::sortDataInsert(int cmp(const T&, const T&)) {
  if (this->isEmpty() || this->header->getNext()->getNext() == this->header)
    return;

  typename List<T>::Position current = this->header->getNext()->getNext();

  while (current != this->header) {
    T key = current->getData();
    typename List<T>::Position mover = current->getPrev();

    while (mover != this->header && cmp(mover->getData(), key) > 0) {
      mover->getNext()->setData(mover->getData());
      mover = mover->getPrev();
    }

    mover->getNext()->setData(key);
    current = current->getNext();
  }
}

template <class T>
void List<T>::sortDataSelect(int cmp(const T&, const T&)) {
  if (this->isEmpty() || this->header->getNext()->getNext() == this->header)
    return;

  Position current = this->header->getNext();
  while (current != this->header) {
    Position minNode = current;
    Position scanner = current->getNext();

    while (scanner != this->header) {
      if (cmp(scanner->getData(), minNode->getData()) < 0)
        minNode = scanner;

      scanner = scanner->getNext();
    }

    if (minNode != current)
      this->swapData(minNode, current);

    current = current->getNext();
  }
}

template <class T>
void List<T>::sortDataShell(int cmp(const T&, const T&)) {
  int series[] = {4181, 2584, 1597, 987, 610, 377, 233, 144, 89, 55,
                  34,   21,   13,   8,   5,   3,   2,   1,   0};

  int size = 0;
  Position temp = this->getFirstPos();
  while (temp != nullptr) {
    size++;
    temp = temp->getNext();
  }

  int pos = 0;
  int gap = series[pos];

  while (gap > size) {
    gap = series[++pos];
  }

  while (gap > 0) {
    for (int i = gap; i < size; i++) {
      Position nodeI = this->getNodeAt(i);
      T tempData = nodeI->getData();

      int j = i;
      while (j >= gap) {
        Position nodeJMinusGap = this->getNodeAt(j - gap);

        if (cmp(nodeJMinusGap->getData(), tempData) > 0) {
          Position nodeJ = this->getNodeAt(j);
          nodeJ->setData(nodeJMinusGap->getData());
          j -= gap;
        } else {
          break;
        }
      }

      Position nodeJ = this->getNodeAt(j);
      nodeJ->setData(tempData);
    }

    gap = series[++pos];
  }
}

template <class T>
typename List<T>::Position List<T>::getNodeAt(int index) const {
  if (this->totalElements < index || index < 0)
    throw DataContainersExceptions::InvalidPosition();

  Position current = this->header->getNext();
  int count = 0;

  while (current != this->header && count < index) {
    current = current->getNext();
    count++;
  }

  return current;
}

template <class X>
std::ostream& operator<<(std::ostream& os, const List<X>& list) {
  typename List<X>::Position aux = list.header->getNext();

  while (aux != list.header) {
    os << aux->getData();
    aux = aux->getNext();
  }

  return os;
}

template <class X>
std::istream& operator>>(std::istream& is, List<X>& list) {
  X element;
  try {
    while (is >> element) {
      list.insertSortedData(element);
    }
  } catch (const std::invalid_argument& ex) {
  }

  return is;
}
#endif  // __LIST_H__