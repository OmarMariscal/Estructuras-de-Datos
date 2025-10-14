#ifndef __LIST_H__
#define __LIST_H__

//LISTA CIRCULAR SIN ENCABEZADO

#include <string>
#include <exception>

using namespace std;

//Definición
template <class T>
class List{
    class Node;

    public:
        typedef Node* Position;

    private:
        class Node{
            private:
                T data;
                Position next = nullptr;
            public:
                Node();
                Node(const T&);

                T& getData();
                Position getNext() const;

                void setData(const T&);
                void setNext(const Position&);
        };

        bool isValidPosition(const Position&) const;
        void add(const List<T>&);

        Position anchor = nullptr;

    public:
        List();
        List(const List<T>&);

        ~List();

        bool isEmpty() const;

        void insertData(const Position&, const T&);
        void deleteData(const Position&);
        Position getFirstPos() const;
        Position getLastPos() const;
        Position getPrevPos(const Position&) const;
        Position getNextPos(const Position&) const;

        Position findData(const T&) const;
        T& retrieve(const Position&);

        string toString() const;

        void sortData();
        void deleteAll();

        List<T>& operator = (const List<T>&);
        
        List<T>& operator += (const List<T>&);
        List<T> operator + (const List<T>&);
};

//Implementación
    //Node
template<class T>
List<T>::Node::Node() {}

template<class T>
List<T>::Node::Node(const T& element) : data(element){}

template<class T>
T& List<T>::Node::getData(){
    return this->T;
}

template<class T>
typename List<T>::Position List<T>::Node::getNext() const{
    return this->next;
}

template<class T>
void List<T>::Node::setData(const T& data){
    this->data = data;
}

template<class T>
void List<T>::Node::setNext(const typename List<T>::Position& pointer){
    this->next = pointer;
}


//Lista

template <class T>
bool List<T>::isValidPosition(const Position& pointer) const{
    Position aux = this->anchor;

    while(aux != nullptr){
        if(aux == p){
            return true;
        }   
        aux = aux->getNext();     
    }

    return false;
}

template <class T>
void List<T>::add(const List<T>& other){
    Position aux(other.anchor), lastInsert(this->getLastPos()), newNode(nullptr);


    while(aux != nullptr){
        if(newNode = new Node(aux->getData()))
            throw std::exception("Memoria no Disponbile, add");

        if(lastInsert == nullptr)
            this->anchor = newNode;
        else
            lastInsert->setNext(newNode);
        
        lastInsert = newNode;
        aux = aux->getNext();
    }

}

template <class T>
List<T>::List(){}

template <class T>
List<T>::List(const List<T>& other){
    this->add(other);
}

template <class T>
List<T>::~List(){
    this->deleteAll();
}

template <class T>
bool List<T>::isEmpty() const{
    return this->anchor == nullptr;
}

template <class T>
void List<T>::insertData(const typename List<T>::Position& position, const T& element){
    if( p != nullptr && !this->isValidPosition(position))
        throw std::exception("Posicion Invalida");
    
    Position newNode(new Node(element));
    if(newNode == nullptr)
        throw std::exception("Memoria no Disponible");
    
    if(position == nullptr){ //Insertar al Principio

        if(this->isEmpty()){
            newNode->setNext(newNode);
        }
        else{
            newNode->setNext(this->anchor);
            this->getLastPos()->setNext(newNode);
        }

        this->anchor = newNode;
    }

    else{ //Cualquier otra
        newNode->setNext(position->getNext());
        position->setNext(newNode);
    }

}

template <class T>
void List<T>::deleteData(const typename List<T>::Position& position){
    if(!this->isValidPosition(position))
        throw std::exception("Posicion Invalida");
    
    if(position == this->anchor){
        if(position->getData() == position){ //Queda solo uno
            this->anchor = nullptr;
        }

        else{
            this->getLastPos()->setNext(position->getNext());
            this->anchor = position->getNext();
        }
    } 
    
    else //Cualquier otra Posición
        this->getPrevPos(position)->setNext(position->getNext());
    
    delete position;
}

template <class T>
typename List<T>::Position List<T>::getFirstPos() const{
    return this->anchor;
}

template <class T>
typename List<T>::Position List<T>::getLastPos() const{
    if(this->isEmpty())
        return nullptr;
    
    Position aux (this->anchor);
    while(aux->getNext() != this->anchor)
        aux = aux->getNext();

    return aux;
}


template <class T>
typename List<T>::Position List<T>::getPrevPos(const typename List<T>::Position& p) const{
    if(this->isEmpty())
        return nullptr;

    Position aux(this->anchor);
    do{
        if(aux->getNext() == p)
            return aux;
        aux = aux->getNext();

    }while(aux != this->anchor);
    
    return nullptr;

}
template <class T>
typename List<T>::Position List<T>::getNextPos(const typename List<T>::Position& position) const{
   return this->isValidPosition(position) || position->getNext() == this->anchor ? nullptr : position->getNext();
}


template <class T>
typename List<T>::Position List<T>::findData(const T& dataSearched) const{
    if(this->isEmpty())
        return nullptr;

    Position aux(this->anchor);

    do{
        if(aux->getData() == dataSearched)
            return aux;
        
        aux = aux->getNext();
    } while(aux != this->anchor);
    
    return nullptr;
}

template <class T>
T& List<T>::retrieve(const typename List<T>::Position& p){
    if(!this->isValidPosition(p))
        throw std::exception("Posicion Invalida");
    return p->getData();
}

template <class T>
string List<T>::toString() const{
    string result;

    if(!this->isEmpty()){
        Position aux(this->anchor);

        do{
            result += aux->getData()->toString() + '\n';
            aux = aux->getNext();
        }while(aux != this->anchor);
    }

    return result;
}

template <class T>
void List<T>::sortData(){
    //PENDIENTE
}

template <class T>
void List<T>::deleteAll(){

    if(this->isEmpty())
        return;

    Position mark(this->anchor), aux;

    do{
        aux = this->anchor;
        this->anchor = aux->getNext();
        delete aux;        
    } while(this->anchor != mark);

    this->anchor = nullptr;
}

template <class T>
List<T>& List<T>::operator = (const List<T>& other){
    this->deleteAll();
    this->add(other);

    return *this;
}


#endif // __LIST_H__