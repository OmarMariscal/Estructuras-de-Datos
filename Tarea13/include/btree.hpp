#ifndef __BTREE_H__
#define __BTREE_H__

#include <string>

#include "ownexceptions.hpp"

using namespace std;

// Definición
template <class T>
class BTree {
  class Node;

 public:
  typedef Node* Position;

 private:
  class Node {
   private:
    T* dataPtr = nullptr;
    Position left = nullptr;
    Position right = nullptr;

   public:
    Node();
    Node(const T&);

    ~Node();

    T* getDataPtr();
    T& getData();

    Position& getLeft();
    Position& getRight();

    void setDataPtr(T*);
    void setData(const T&);
    void setLeft(const Position&);
    void setRight(const Position&);
  };

  Position root = nullptr;
  void copyAll(const Position&, Position&);

  void deleteAll(Position&);
  void addData(Position&, const T&);
  void deleteData(Position&, const T&);
  Position& getHighest(Position&);
  Position& getLowest(Position&);
  unsigned int getHeight(const Position&) const;
  Position& findData(Position&, const T&);
  string& parsePreOrder(const Position&, string&) const;
  string& parseInOrder(const Position&, string&) const;
  string& parsePostOrder(const Position&, string&) const;

 public:
  BTree();
  BTree(const BTree<T>&);

  ~BTree();

  bool isEmpty() const;
  void addData(const T&);
  void deleteData(const T&);

  Position& findData(const T&);
  T& retrieve(const Position&);

  bool isLeaf(const Position&) const;
  Position& getLowest();
  Position& getHighest();
  unsigned int getHeight(const std::string& = "root") const;

  string parsePreOrder() const;
  string parseInOrder() const;
  string parsePostOrder() const;

  void deleteAll();

  BTree& operator=(const BTree<T>&);
};

// Implementación
// Node
template <class T>
BTree<T>::Node::Node() {}

template <class T>
BTree<T>::Node::Node(const T& element) : dataPtr(new (nothrow) T(element)) {
  if (dataPtr == nullptr) {
    throw NodeExceptions::NodeExceptionTo("Memoria no disponible, Node");
  }
}

template <class T>
BTree<T>::Node::~Node() {
  delete this->dataPtr;
}

template <class T>
T* BTree<T>::Node::getDataPtr() {
  return this->dataPtr;
}

template <class T>
T& BTree<T>::Node::getData() {
  if (this->dataPtr == nullptr)
    throw NodeExceptions::NodeExceptionTo("Dato Inexistente, getData");
  return *this->dataPtr;
}

template <class T>
typename BTree<T>::Position& BTree<T>::Node::getLeft() {
  return this->left;
}

template <class T>
typename BTree<T>::Position& BTree<T>::Node::getRight() {
  return this->right;
}

template <class T>
void BTree<T>::Node::setDataPtr(T* p) {
  this->dataPtr = p;
}

template <class T>
void BTree<T>::Node::setData(const T& e) {
  if (this->dataPtr == nullptr) {
    this->dataPtr = new (nothrow) T(e);
    if (this->dataPtr == nullptr)
      throw NodeExceptions::NodeExceptionTo("Memoria no disponible. Set Data");
  } else
    *this->dataPtr = e;
}

template <class T>
void BTree<T>::Node::setLeft(const typename BTree<T>::Position& pointer) {
  this->left = pointer;
}

template <class T>
void BTree<T>::Node::setRight(const typename BTree<T>::Position& pointer) {
  this->right = pointer;
}

// Implementación del Árbol
template <class T>
BTree<T>::BTree() {}

template <class T>
BTree<T>::BTree(const BTree<T>& other) {
  this->copyAll(other.root, this->root);
}

template <class T>
BTree<T>::~BTree() {
  this->deleteAll();
}

template <class T>
bool BTree<T>::isEmpty() const {
  return this->root == nullptr;
}

template <class T>
void BTree<T>::addData(const T& e) {
  this->addData(this->root, e);
}

template <class T>
void BTree<T>::addData(Position& r, const T& e) {
  if (r == nullptr) {
    r = new (nothrow) Node(e);
    if (r == nullptr)
      throw NodeExceptions::NodeExceptionTo();
    return;
  }
  if (e < r->getData())
    this->addData(r->getLeft(), e);
  else
    this->addData(r->getRight(), e);

  // Sale de la recursividad
}

template <class T>
void BTree<T>::deleteData(const T& e) {
  this->deleteData(this->root, e);
}

template <class T>
void BTree<T>::deleteData(Position& r, const T& e) {
  if (r == nullptr)
    return;

  if (r->getData() == e) {  // Eliminación
    if (this->isLeaf(r)) {  // Es Hoja
      delete r;
      r = nullptr;

      return;
    }

    if (r->getLeft() != nullptr &&
        r->getRight() != nullptr) {  // Tiene los dos hijos
      r->setData(this->getHighest(r->getLeft())->getData());
      this->deleteData(r->getLeft(), r->getData());

      // Aquí sale de la recursividad
      return;
    }

    Position aux(r);

    r = (r->getLeft() == nullptr) ? r->getRight() : r->getLeft();

    delete aux;

    return;
  }

  if (e < r->getData())
    this->deleteData(r->getLeft(), e);
  else
    this->deleteData(r->getRight(), e);

  // Sale de recursividad
}

template <class T>
typename BTree<T>::Position& BTree<T>::findData(const T& e) {
  return this->findData(this->root, e);
}

template <class T>
typename BTree<T>::Position& BTree<T>::findData(Position& r, const T& e) {
  if (r == nullptr || r->getData() == e)
    return r;

  if (e < r->getData())
    return this->findData(r->getLeft(), e);
  return this->findData(r->getRight(), e);
}

template <class T>
T& BTree<T>::retrieve(const Position& r) {
  if (r == nullptr)
    throw DataContainersExceptions::InvalidPosition("Subarbol vacio. Retrieve");
  return r->getData();
}

template <class T>
bool BTree<T>::isLeaf(const Position& r) const {
  return (r->getLeft() == nullptr && r->getRight() == nullptr);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getLowest() {
  return this->getLowest(this->root);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getLowest(Position& r) {
  if (r == nullptr || r->getLeft() == nullptr)
    return r;
  return this->getLowest(r->getLeft());
}

template <class T>
typename BTree<T>::Position& BTree<T>::getHighest() {
  return this->getHighest(this->root);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getHighest(Position& r) {
  if (r == nullptr || r->getRight() == nullptr)
    return r;
  return this->getHighest(r->getRight());
}

template <class T>
unsigned int BTree<T>::getHeight(const std::string& from) const {
  if (from == "left")
    return this->getHeight(this->root->getLeft());
  if (from == "right")
    return this->getHeight(this->root->getRight());
  else
    return this->getHeight(this->root);
}

template <class T>
unsigned int BTree<T>::getHeight(const Position& r) const {
  if (r == nullptr)
    return 0;

  unsigned int lH(this->getHeight(r->getLeft()));
  unsigned int rH(this->getHeight(r->getRight()));

  return (lH > rH ? lH : rH) + 1;
}

template <class T>
void BTree<T>::copyAll(const Position& from, Position& to) {
  if (from == nullptr) {
    to = nullptr;
    return;
  }

  // Crear el Nodo
  to = new (nothrow) Node(from->getData());
  if (to == nullptr)
    throw NodeExceptions::NodeExceptionTo();

  this->copyAll(from->getLeft(), to->getLeft());
  this->copyAll(from->getRight(), to->getRight());
}

template <class T>
void BTree<T>::deleteAll() {
  this->deleteAll(this->root);
}

template <class T>
void BTree<T>::deleteAll(Position& r) {
  if (r == nullptr)
    return;

  this->deleteAll(r->getLeft());
  this->deleteAll(r->getRight());

  delete r;
  r = nullptr;
}

template <class T>
string BTree<T>::parsePreOrder() const {
  string result;
  this->parsePreOrder(this->root, result);
  return result;
}

template <class T>
string& BTree<T>::parsePreOrder(const Position& r, string& str) const {
  if (r != nullptr) {
    str += r->getData().toString() + "\n";
    this->parsePreOrder(r->getLeft(), str);
    this->parsePreOrder(r->getRight(), str);
  }

  return str;
}

template <class T>
string BTree<T>::parseInOrder() const {
  string result;
  this->parseInOrder(this->root, result);
  return result;
}

template <class T>
string& BTree<T>::parseInOrder(const Position& r, string& str) const {
  if (r != nullptr) {
    this->parseInOrder(r->getLeft(), str);
    str += r->getData().toString() + "\n";
    this->parseInOrder(r->getRight(), str);
  }

  return str;
}

template <class T>
string BTree<T>::parsePostOrder() const {
  string result;
  this->parsePostOrder(this->root, result);
  return result;
}

template <class T>
string& BTree<T>::parsePostOrder(const Position& r, string& str) const {
  if (r != nullptr) {
    this->parsePostOrder(r->getLeft(), str);
    this->parsePostOrder(r->getRight(), str);
    str += r->getData().toString() + "\n";
  }

  return str;
}

template <class T>
BTree<T>& BTree<T>::operator=(const BTree<T>& other) {
  this->deleteAll();
  this->copyAll(other.root, this->root);
}

#endif  // __BTREE_H__