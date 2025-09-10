#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <exception>
#include <string>

using namespace std;

//Definición

template <class T, int ARRAYSIZE = 1024>
class Queue{
    private:
        T data[ARRAYSIZE];
        int frontPos = 0;
        int endPos = ARRAYSIZE-1;

        void copyAll(const Queue<T, ARRAYSIZE>&);

    public:
        class Exception : public Exception{
        Exception() noexcept : msg("Error Indefinido") {}
        Exception(const Exception& ex) noexcept : msg(ex.msg) {}
        Exception(const std::string& m) : msg(m) {}
        Exception& operator=(const Exception& ex) noexcept {
            msg = ex.msg;
            return *this;
        }

        virtual ~Exception() {}
        virtual const char* what() const noexcept { return msg.c_str(); }
         };
        Queue();
        Queue(const Queue<T, ARRAYSIZE>&);

        bool isEmpty() const;
        bool isFull() const;

        void enqueue(const T&);
        T dequeue();

        T& getTop();

        Queue<T, ARRAYSIZE>& operator = (const Queue<T,ARRAYSIZE>&);

};

//Implementación

template<class T, int ARRAYSIZE>
void Queue<T,ARRAYSIZE>::copyAll(const Queue<T,ARRAYSIZE>& other){

}


template<class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>::Queue(){}

template <class T, int ARRAYSIZE>
Queue<T,ARRAYSIZE>::Queue(const Queue<T,ARRAYSIZE>&){

}

template<class T, int ARRAYSIZE>
bool Queue<T,ARRAYSIZE>::isEmpty() const{
    return (this->frontPos == this->endPos + 1) || (this->frontPos == 0 && this->endPost == ARRAYSIZE-1);
}

template<class T, int ARRAYSIZE>
bool Queue<T,ARRAYSIZE>::isFull() const{
    return (this->frontPos == this->endPos + 2) || (this->frontPos == 0 && this->endPos == ARRAYSIZE - 2) || (this->frontPos == 1 && this->endPos == ARRAYSIZE - 1);
}

template<class T, int ARRAYSIZE>
void Queue<T,ARRAYSIZE>::enqueue(const T& data){
    if(this->isFull())
        throw("Desbordamiento de Datos, Enqueue");
    
    if(++this->endPos == ARRAYSIZE){
        this->endPos =0;
    }

    this->data[this->endPos] = data;
}

template<class T, int ARRAYSIZE>
T Queue<T, ARRAYSIZE>::dequeue(){
    if(this->isEmpty())
        throw Exception("Insuficiencia de Datos, Dequeue");

    T result(this->data[this->frontPos]);

    if(++this->frontPos == ARRAYSIZE){
        this->frontPos = 0;
    }

    return T()
}

template<class T, int ARRAYSIZE>
T& Queue<T, ARRAYSIZE>::getTop(){
    if(this->isEmpty())
       throw Exception("Insuficienda de datos");

    return this->data[this->frontPos];
}

template<class T, int ARRAYSIZE>
Queue<T,ARRAYSIZE>& Queue<T,ARRAYSIZE>::operator = (const Queue<T,ARRAYSIZE>& other){
    copyAll(other);
    return *this;
}




#endif // __QUEUE_H__