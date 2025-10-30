#ifndef __STACK_H__
#define __STACK_H__

#include <string>

#include "ownexceptions.hpp"

using namespace std;

//Definición
template <class T>
class Stack{
    class Node;
    private:
        typedef Node* Position;
        class Node{
            private:
                T data;
                Position next;
            public:
                Node();
                Node(const T&);

                T& getData();
                Position getNext() const;

                void setData(const T&);
                void setNext(const Position&);
        };

        Position anchor = nullptr;
        void add(const Stack<T>&);
        void deleteAll();

        public:
            Stack();
            Stack(const Stack&);

            ~Stack();

            bool isEmpty() const;
            void push(const T&);
            T pop();

            T& getTop();


            Stack<T>& operator = (const Stack&);

};


//Implementación
    //Node
template<class T>
Stack<T>::Node::Node() {}

template<class T>
Stack<T>::Node::Node(const T& element) : data(element){}

template<class T>
T& Stack<T>::Node::getData(){
    return this->data;
}

template<class T>
typename Stack<T>::Position Stack<T>::Node::getNext() const{
    return this->next;
}

template<class T>
void Stack<T>::Node::setData(const T& data){
    this->data = data;
}

template<class T>
void Stack<T>::Node::setNext(const typename Stack<T>::Position& pointer){
    this->next = pointer;
}


//IMplementación del Stack


template <class T>
void Stack<T>::add(const Stack<T>& other){
    Position aux(other.anchor), lastInsert(nullptr), newNode(nullptr);


    while(aux != nullptr){
        newNode = new (nothrow) Node(aux->getData());
        if(newNode == nullptr)
            throw NodeExceptions::MemoryNotAvaliable("Memoria no Disponible");

        if(lastInsert == nullptr)
            this->anchor = newNode;
        else
            lastInsert->setNext(newNode);
        
        lastInsert = newNode;
        aux = aux->getNext();
    }

}

template <class T>
void Stack<T>::deleteAll(){
    Position aux;

    while(this->anchor != nullptr){
        aux = this->anchor;
        this->anchor = aux->getNext();
        delete aux;
    }
}

template <class T>
Stack<T>::Stack(){}

template <class T>
Stack<T>::Stack(const Stack<T>& other) {
    this->add(other);
}

template <class T>
Stack<T>::~Stack(){
    this->deleteAll();
}

template <class T>
bool Stack<T>::isEmpty() const{
    return this->anchor == nullptr;
}

template <class T>
void Stack<T>::push(const T& e){
    Position newNode(new (nothrow) Node(e));

    if(newNode == nullptr)
        throw NodeExceptions::MemoryNotAvaliable();
    newNode->setNext(this->anchor);
    this->anchor = newNode;
}

template <class T>
T Stack<T>::pop(){
    if(this->isEmpty())
        throw DataContainersExceptions::MemoryDeficiency();
    Position aux(this->anchor);
    T result(aux->getData());

    this->anchor = aux->getNext();
    delete aux;

    return result;
}

template <class T>
T& Stack<T>::getTop(){
    if(this->isEmpty())
        throw DataContainersExceptions::MemoryDeficiency();
    return this->anchor->getData();
}

template <class T>
Stack<T>& Stack<T>::operator =(const Stack<T>& other){
    this->deleteAll();
    this->add(other);

    return *this;
}

#endif // __STACK_H__