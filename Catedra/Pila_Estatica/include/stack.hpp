#ifndef __STACK_H__
#define __STACK_H__

//Definición

template <class T, int ARRAYSIZE = 1024>
class Stack{
    private:
        T data[ARRAYSIZE];
        int top;

        void copyAll(const Stack<T, ARRAYSIZE>);
    public:
        class Exception{
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

        Stack();
        Stack(const Stack<T, ARRAYSIZE>&);
        
        bool isEmpty();
        bool isFull();

        void push(const T&);
        
        T pop();

        T& getTop();


        Stack<T,ARRAYSIZE>& operator = (const Stack<T, ARRAYSIZE>&);
};

//Implementación

template<class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::copyAll(const Stack<T, ARRAYSIZE> other){
    int i(0);
    while(i <= other.top){
        this->data[i++] = other.data[i];
    }

    this->top = other.top;
}

template<class T, int ARRAYSIZE>
Stack<T,ARRAYSIZE>::Stack() : top(-1){}

template<class T, int ARRAYSIZE>
Stack<T, ARRAYSIZE>::Stack(const Stack<T, ARRAYSIZE>& other){
    copyAll(other);
}


template<class T, int ARRAYSIZE>
bool Stack<T, ARRAYSIZE>::isEmpty(){
    return this->top == -1;
}

template<class T, int ARRAYSIZE>
bool Stack<T, ARRAYSIZE>::isFull(){
   return this->top == (ARRAYSIZE-1); 
}

template<class T, int ARRAYSIZE>
void Stack<T, ARRAYSIZE>::push(const T& data){
    if(isFull()){
        throw Exception("Desbordamiento de Memoria. Push");
    }

    this->data[++this->top] = data;
}

template<class T, int ARRAYSIZE>
T Stack<T, ARRAYSIZE>::pop(){
    if(isEmpty()){
        throw Exception("Insufienciencia de Datos. Pop");
    }

    return this->data[this->top--];
}


template<class T, int ARRAYSIZE>
T& Stack<T, ARRAYSIZE>::getTop(){
    if(isEmpty()){
        throw Exception("Insuficiencia de Datos. getTop");
    }
    return &this->data[this->top];
}

template<class T, int ARRAYSIZE>
Stack<T,ARRAYSIZE>& Stack<T, ARRAYSIZE>::operator = (const Stack<T, ARRAYSIZE>& other){
    this->copyAll(other);
    return *this;
}


//Implementación


#endif // __STACK_H__