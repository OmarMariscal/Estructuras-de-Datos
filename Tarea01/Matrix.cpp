#include <iostream>
#include <iomanip>
#include <random>

class Matrix{
    private:
        int size;
        float values[10][10];
    public: 
        Matrix(int);
        void randomizer();
        
        //Sobrecarga del operador << para el cout
        friend std::ostream& operator << (std::ostream& os, const Matrix& m);
        Matrix operator + (const Matrix& otro) const;
        Matrix operator * (const Matrix& otro) const;
};

Matrix::Matrix(int size){
    this->size = size;
}

void Matrix::randomizer(){
    //Generar una serie de números pseudoaleatorios para llenar la matriz
    std::random_device seed; //Un generador de semilla aleatoria en cualquier ejecución
    std::default_random_engine engine(seed()); //Usamos el motor aleatorio por defecto, el más simple, con la semilla generada
    std::uniform_real_distribution<float> distribution(-100.00,100.00); //Crear el objeto de una distribución normal de reales en el rango de -100.00 a 100.00

    //Ciclo anidado para llenar la matriz con los números pesudoaleatorios
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            values[i][j] = (round(distribution(engine) * 100) / 100);
}

//Sobrecarga del cout
std::ostream& operator<<(std::ostream& os, const Matrix &m){
    const int width = 10; //Anchura de cada celda
    auto linea = [&](){
        os << "+";
        for(int i = 0; i < m.size; i ++){
            os << std::string(width,'-')<<"+";
        }
        os<<"\n";
    };

    linea();
    for(int i = 0; i < m.size; i++){
        for(int j = 0; j < m.size; j++){
            os << "|" << std::setw(width) << std::left << m.values[i][j];
        }
        os<<"|"<<"\n";
        linea();
    }

    return os;
}

Matrix Matrix::operator+(const Matrix& otro)const {
    Matrix sum(size);
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            sum.values[i][j] = this->values[i][j] + otro.values[i][j];
    return sum;
}

Matrix Matrix::operator*(const Matrix& otro) const{
    Matrix times(size);

    for(int i = 0; i < size; i++){

        for(int j = 0; j < size; j++){                
            times.values[i][j] = 0;
            for(int k = 0; k < size; k++){
                times.values[i][j] += (this->values[i][k] * otro.values[k][j]);
            }
        }
    }
    return times;
}

int main(){
    Matrix a1(2);
    a1.randomizer();
    std::cout<<a1;

    std::cout<<std::endl;

    Matrix a2(2);
    a2.randomizer();
    std::cout<<a2;

    std::cout<<std::endl;

    std::cout<<a1*a2;

    return 0;
}