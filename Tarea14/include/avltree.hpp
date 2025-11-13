#ifndef __AVLTree_H__
#define __AVLTree_H__

#include <string>
#include "ownexceptions.hpp"

using namespace std;

//Definición
template <class T>
class AVLTree{
    class Node;

    public:
        typedef Node* Position;

    private:
        class Node{
            private:
                T* dataPtr = nullptr;
                Position left = nullptr;
                Position right = nullptr;

                unsigned height = 1;
            public:
                Node();
                Node(const T&);

                ~Node();

                T* getDataPtr();
                T& getData();

                Position& getLeft();
                Position& getRight();
                unsigned getHeight() const;

                void updateHeight();

                void setDataPtr(T*);
                void setData(const T&);
                void setLeft(const Position&);
                void setRight(const Position&);
                void setHeight(const unsigned&);

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
    
    //AVL
    int getBalanceFactor(const Position&) const;
    void leftRotation(Position&);
    void rightRotation(Position&);
    
    void doBalancing(Position&);

    public:
        AVLTree();
        AVLTree(const AVLTree<T>&);

        ~AVLTree();

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

        AVLTree& operator = (const AVLTree<T>&);
};

//Implementación
    //Node
template<class T>
AVLTree<T>::Node::Node() {}

template<class T>
AVLTree<T>::Node::Node(const T& element) : dataPtr(new (nothrow) T(element)){
    if(dataPtr == nullptr){
        throw NodeExceptions::NodeExceptionTo("Memoria no disponible, Node");
    }
}

template<class T>
AVLTree<T>::Node::~Node(){
    delete this->dataPtr;
}

template<class T>
T* AVLTree<T>::Node::getDataPtr(){
    return this->dataPtr;
}

template<class T>
T& AVLTree<T>::Node::getData(){
    if(this->dataPtr == nullptr)
        throw NodeExceptions::NodeExceptionTo("Dato Inexistente, getData");
    return *this->dataPtr;
}

template<class T>
typename AVLTree<T>::Position& AVLTree<T>::Node::getLeft() {
    return this->left;
}

template<class T>
typename AVLTree<T>::Position& AVLTree<T>::Node::getRight(){
    return this->right;
}

template <class T>
unsigned AVLTree<T>::Node::getHeight() const{
    return this->height;
}

template <class T>
void AVLTree<T>::Node::updateHeight() {
    unsigned lH(this->left == nullptr ? 0 : this->left->height);
    unsigned rH(this->right == nullptr ? 0 : this->right->height);

    this->height = (lH > rH ? lH : rH) + 1;
}

template<class T>
void AVLTree<T>::Node::setDataPtr(T* p){
    this->dataPtr = p;
}

template<class T>
void AVLTree<T>::Node::setData(const T& e){
    if(this->dataPtr == nullptr){
        this->dataPtr = new (nothrow) T(e);
        if(this->dataPtr == nullptr)
            throw NodeExceptions::NodeExceptionTo("Memoria no disponible. Set Data");
    }
    else
        *this->dataPtr = e;
}

template<class T>
void AVLTree<T>::Node::setLeft(const typename AVLTree<T>::Position& pointer){
    this->left = pointer;
}

template<class T>
void AVLTree<T>::Node::setRight(const typename AVLTree<T>::Position& pointer){
    this->right = pointer;
}

template <class T>
void AVLTree<T>::Node::setHeight(const unsigned& h){
    this->height = h;
}

//Implementación del Árbol
template <class T>
AVLTree<T>::AVLTree(){}

template <class T>
AVLTree<T>::AVLTree(const AVLTree<T>& other){
    this->copyAll(other.root, this->root);
}

template <class T>
AVLTree<T>::~AVLTree(){
    this->deleteAll();
}

template <class T>
bool AVLTree<T>::isEmpty() const{
    return this->root == nullptr;
}

template <class T>
void AVLTree<T>::addData(const T& e){
    this->addData(this->root, e);
}

template <class T>
void AVLTree<T>::addData(Position& r, const T& e){
    if(r == nullptr){
        r = new (nothrow) Node(e);
        if(r == nullptr)
            throw NodeExceptions::NodeExceptionTo();
        return;
    }
    if(e < r->getData()) this->addData(r->getLeft(), e);
    else this->addData(r->getRight(), e);

    r->updateHeight();
    this->doBalancing(r);
}

template <class T>
void AVLTree<T>::deleteData(const T& e){
    this->deleteData(this->root, e);
}

template <class T>
void AVLTree<T>::deleteData(Position& r, const T& e){
    if(r == nullptr)
        return;
    
    if(r->getData() == e){ 
        if(this->isLeaf(r)){ 
            delete r;
            r = nullptr;
        }
        else if(r->getLeft() != nullptr && r->getRight() != nullptr){
            Position& pred = this->getHighest(r->getLeft());
            r->setData(pred->getData());
            this->deleteData(r->getLeft(), pred->getData());
        }
        else {
            Position aux(r);
            r = (r->getLeft() == nullptr) ? r->getRight() : r->getLeft();
            delete aux;
        }
    }
    else if(e < r->getData()) {
        this->deleteData(r->getLeft(), e);
    }
    else {
        this->deleteData(r->getRight(), e);
    }

    if(r != nullptr) {
        r->updateHeight();
        this->doBalancing(r);
    }
}

template <class T>
typename AVLTree<T>::Position& AVLTree<T>::findData(const T& e){
    return this->findData(this->root, e);
}

template <class T>
typename AVLTree<T>::Position& AVLTree<T>::findData(Position& r, const T& e){
    if(r == nullptr || r->getData() == e)
        return r;
    
    if(e < r->getData())
        return this->findData(r->getLeft(), e);
    return this->findData(r->getRight(), e);

}

template <class T>
T& AVLTree<T>::retrieve(const Position& r){
    if(r == nullptr)
        throw DataContainersExceptions::InvalidPosition("Subarbol vacio. Retrieve");
    return r->getData();
}

template <class T>
bool AVLTree<T>::isLeaf(const Position& r) const{
    return (r->getLeft() == nullptr && r->getRight() == nullptr);       
}

template <class T>
typename AVLTree<T>::Position& AVLTree<T>::getLowest(){
    return this->getLowest(this->root);
}

template <class T>
typename AVLTree<T>::Position& AVLTree<T>::getLowest(Position& r){
    if(r == nullptr || r->getLeft() == nullptr)
        return r;
    return this->getLowest(r->getLeft());    
}

template <class T>
typename AVLTree<T>::Position& AVLTree<T>::getHighest(){
    return this->getHighest(this->root);
}

template <class T>
typename AVLTree<T>::Position& AVLTree<T>::getHighest(Position& r){
    if(r == nullptr || r->getRight() == nullptr)
        return r;
   return  this->getHighest(r->getRight());    
}

template <class T>
unsigned int AVLTree<T>::getHeight(const std::string& branch) const{
    if(this->root == nullptr)
        return 0;
    if(branch == "left")
        return this->getHeight(this->root->getLeft());
    if(branch == "right")
        return this->getHeight(this->root->getRight());
    return this->getHeight(this->root);
}

template <class T>
unsigned int AVLTree<T>::getHeight(const Position& r) const{
    return r == nullptr ? 0 : r->getHeight();
}

template <class T>
void AVLTree<T>::copyAll(const Position& from, Position& to){
    if(from == nullptr){
        to = nullptr;
        return;
    }

    //Crear el Nodo 
    to = new (nothrow) Node(from->getData());
    if(to == nullptr)
        throw NodeExceptions::NodeExceptionTo();

    this->copyAll(from->getLeft(), to->getLeft());
    this->copyAll(from->getRight(), to->getRight());
    to->updateHeight();
}

template <class T>
void AVLTree<T>::deleteAll(){
    this->deleteAll(this->root);
}


template <class T>
void AVLTree<T>::deleteAll(Position& r){
    if(r == nullptr)
        return;
    
    this->deleteAll(r->getLeft());
    this->deleteAll(r->getRight());
    
    delete r;
    r = nullptr;
}

template <class T>
string AVLTree<T>::parsePreOrder() const{
    string result;
    this->parsePreOrder(this->root, result);
    return result;
}

template <class T>
string& AVLTree<T>::parsePreOrder(const Position& r, string& str) const{
    if(r != nullptr){
        str += r->getData().toString() + "\n";
        this->parsePreOrder(r->getLeft(), str);
        this->parsePreOrder(r->getRight(), str);        
    }
    
    return str;
}

template <class T>
string AVLTree<T>::parseInOrder() const{
    string result;
    this->parseInOrder(this->root, result);
    return result;
}

template <class T>
string& AVLTree<T>::parseInOrder(const Position& r, string& str) const{
    if(r != nullptr){
        this->parseInOrder(r->getLeft(), str);
        str += r->getData().toString() + "\n";
        this->parseInOrder(r->getRight(), str);        
    }
    
    return str;
}

template <class T>
string AVLTree<T>::parsePostOrder() const{
    string result; 
    this->parsePostOrder(this->root, result);
    return result;
}

template <class T>
string& AVLTree<T>::parsePostOrder(const Position& r, string& str) const{
    if(r != nullptr){
        this->parsePostOrder(r->getLeft(), str);
        this->parsePostOrder(r->getRight(), str);        
        str += r->getData().toString() + "\n";
    }
    
    return str;
}


template <class T>
AVLTree<T>& AVLTree<T>::operator = (const AVLTree<T>& other){
    if(this == &other)
        return *this;
        
    this->deleteAll();
    this->copyAll(other.root, this->root);

    return *this;
}

template <class T>
int AVLTree<T>::getBalanceFactor(const Position& r) const{
    return (this->getHeight(r->getRight()) - this->getHeight(r->getLeft()));
}

template <class T>
void AVLTree<T>::leftRotation(Position& r){
    Position aux(r->getRight());

    r->setRight(aux->getLeft());
    aux->setLeft(r);
    r = aux;

    r->getLeft()->updateHeight();
    r->updateHeight();
}

template <class T>
void AVLTree<T>::rightRotation(Position& r){
    Position aux(r->getLeft());

    r->setLeft(aux->getRight());
    aux->setRight(r);
    r = aux;

    r->getRight()->updateHeight();
    r->updateHeight();
}

template <class T>
void AVLTree<T>::doBalancing(Position& r){
    switch(this->getBalanceFactor(r)){
        case -2:
            if(this->getBalanceFactor(r->getLeft()) == 1){
                this->leftRotation(r->getLeft());
                r->updateHeight(); 
            }
            this->rightRotation(r);
            break;
            
        case 2:
            if(this->getBalanceFactor(r->getRight()) == -1){
                this->rightRotation(r->getRight());
                r->updateHeight();  
            }
            this->leftRotation(r);
            break;
    }
}

#endif // __AVLTree_H__