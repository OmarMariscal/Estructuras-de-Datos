#ifndef __QUEUE_H__
#define __QUEUE_H__


#include <string>

#include "ownexceptions.hpp"

using namespace std;

//Definición
template <class T>
class Queue{
    class Node;

    private:
        typedef Node* Position;

        class Node{
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
        Position header = nullptr;

        void add(const Queue<T>&);
        void deleteAll();

    public:
        Queue();
        Queue(const Queue<T>&);

        ~Queue();

        bool isEmpty() const;
        void enqueue(const T&);
        T dequeue();
        T& getFront();

        Queue<T>& operator = (const Queue<T> &);

};

//Implementación
    //Node
template<class T>
Queue<T>::Node::Node() {}

template<class T>
Queue<T>::Node::Node(const T& element) : dataPtr(new T(element)){
    if(dataPtr == nullptr){
        throw NodeExceptions::MemoryNotAvaliable("Memoria no disponible, Node");
    }
}

template<class T>
Queue<T>::Node::~Node(){
    delete this->dataPtr;
}

template<class T>
T* Queue<T>::Node::getDataPtr(){
    return this->dataPtr;
}

template<class T>
T& Queue<T>::Node::getData(){
    if(this->dataPtr == nullptr)
        throw NodeExceptions::MemoryNotAvaliable("Dato Inexistente, getData");
    return *this->dataPtr;
}

template<class T>
typename Queue<T>::Position Queue<T>::Node::getPrev() const{
    return this->prev;
}

template<class T>
typename Queue<T>::Position Queue<T>::Node::getNext() const{
    return this->next;
}

template<class T>
void Queue<T>::Node::setDataPtr(T* p){
    this->dataPtr = p;
}

template<class T>
void Queue<T>::Node::setData(const T& e){
    if(this->dataPtr == nullptr)
        if(this->dataPtr = new T(e) == nullptr)
            throw NodeExceptions::MemoryNotAvaliable("Memoria no disponible, setData");
    else
        *this->dataPtr = e;
}

template<class T>
void Queue<T>::Node::setPrev(const typename Queue<T>::Position& pointer){
    this->prev = pointer;
}

template<class T>
void Queue<T>::Node::setNext(const typename Queue<T>::Position& pointer){
    this->next = pointer;
}


//Queue
template <class T>
void Queue<T>::add(const Queue<T>& other){
    Position aux(other.header->getNext()), newNode;


    while(aux != other.header){
        newNode = new (nothrow) Node(aux->getData());

        if(newNode == nullptr)
            throw DataContainersExceptions::MemoryDeficiency("Memoria no Disponible");

        newNode->setPrev(this->header->getPrev());
        newNode->setNext(this->header);

        this->header->getPrev()->setNext(newNode);
        this->header->setPrev(newNode);

        aux = aux->getNext();
    }
}

template <class T>
void Queue<T>::deleteAll(){
    Position aux;

    while(this->header->getNext() != this->header){
        aux = this->header->getNext();

        this->header->setNext(aux->getNext());
        delete aux;
    }

    this->header->setPrev(this->header);
}

template <class T>
Queue<T>::Queue() : header(new (nothrow) Node) {
    if(this->header == nullptr)
        throw NodeExceptions::MemoryNotAvaliable();
    
    this->header->setPrev(this->header);
    this->header->setNext(this->header);
}

template <class T>
Queue<T>::Queue(const Queue<T>& other) : Queue() {
    this->add(other);
}

template <class T>
Queue<T>::~Queue(){
    this->deleteAll();

    delete this->header;
}


template <class T>
bool Queue<T>::isEmpty() const{
    return this->header->getNext() == header;
}

template <class T>
void Queue<T>::enqueue(const T& e){
    Position newNode = new (nothrow) Node(e);
    if (newNode == nullptr)
        throw NodeExceptions::MemoryNotAvaliable("Memoria no disponible");
    
    newNode->setPrev(this->header->getPrev());
    newNode->setNext(this->header);

    this->header->getPrev()->setNext(newNode);
    this->header->setPrev(newNode);

}

template <class T>
T Queue<T>::dequeue(){
    if(this->isEmpty())
        throw DataContainersExceptions::MemoryDeficiency();
    Position aux(this->header->getNext());
    T result(aux->getData());

    aux->getPrev()->setNext(aux->getNext());
    aux->getNext()->setPrev(aux->getPrev());
    
    delete aux;

    return result;
}

template <class T>
T& Queue<T>::getFront(){
    if(this->isEmpty())
        throw DataContainersExceptions::MemoryDeficiency();

    return this->header->getNext()->getData();
}

template <class T>
Queue<T>& Queue<T>::operator= (const Queue<T>& other){
    this->deleteAll();
    this->add(other);

    return *this;
}

#endif