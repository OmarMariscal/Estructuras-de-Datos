#include <graph.hpp>


template<unsigned SIZE>
int Graph<SIZE>::getIdx(const std::string& l) {
    for(int i(0); i < SIZE; i++){
        if(this->vertexArray[i].exist && this->vertexArray[i].label == l){
            return i;
        }
    }
    return -1;
}

template<unsigned SIZE>
void Graph<SIZE>::copyAll(const Graph<SIZE>& other){
    for(int i(0); i < SIZE; i++){
        this->vertexArray[i] = other.vertexArray[i];
        
        for(int j(0); i < SIZE; j++){
            this->edgeMatrix[i][j] = other.edgeMatrix[i][j];
        }
    }

    this->isDirected = other.isDirected;
    this->isWeighted = other.isWeighted;
    this->counter = other.counter;
}


template<unsigned SIZE>
Graph<SIZE>::Graph() {}

template<unsigned SIZE>
Graph<SIZE>::Graph(const Graph<SIZE>& other){
    this->copyAll(other);
}

template<unsigned SIZE>
bool Graph<SIZE>::isEmpty() const{
    return this->counter == 0;
}

template<unsigned SIZE>
bool Graph<SIZE>::isFull() const{
    return this->counter == (SIZE - 1);
}

template<unsigned SIZE>
bool Graph<SIZE>::getIsDirected() const{
    return this->isDirected;
}

template <unsigned SIZE>
bool Graph<SIZE>::getWeighted() const{
    return this->isWeighted;
}

template<unsigned SIZE>
void Graph<SIZE>::setIsDirected(const bool& d){
    this->isDirected = d;
}

template<unsigned SIZE>
void Graph<SIZE>::setWeighted(const bool& w){
    this->isWeighted = w;
}

template<unsigned SIZE>
std::string Graph<SIZE>::toString() const{
    std::string result;
    for(int i(0); i < SIZE; i++){
        if(this->vertexArray[i].exists){
            result += this->vertexArray[i].label;
            for(int j(0); j < SIZE; j++){
                if(this->edgeMatrix[i][j].exists){
                    result += " -> " + this->vertexArray[j].label;

                    if(this->isWeighted){
                        result += ":" + std::to_string(this->edgeMatrix[i][j].cost);
                    }
                }
            }

            result += "\n";
        }
    }

    return result;
}

template<unsigned SIZE>
void Graph<SIZE>::addVertex(const std::string& l){
    if(this->isFull() || this->getIdx(l) != -1)
        return;

    int i(0);
    while(this->vertexArray[i].exists){
        i++;
    }    

    this->vertexArray[i].exists = true;
    this->vertexArray[i].label = l;

    this->counter++;
}

template<unsigned SIZE>
void Graph<SIZE>::delVertex(const std::string& l){
    int vertexIdx(this->getIdx(l));
    
    if(vertexIdx == -1)
        return;

    this->vertexArray[vertexIdx].exists = false;

    for(int i(0); i < SIZE; i++){
        this->addEdge[vertexArray][i].exists = false;
        this->addEdge[i][vertexArray].exists = false;
    }

    this->counter--;
}

template<unsigned SIZE>
void Graph<SIZE>::addEdge(const std::string& o, const std::string& d, const float& cost){
    int orig(this->getIdx(o));
    int dest(this->getIdx(d));
    
    if(orig == -1 || dest == -1 || this->edgeMatrix[orig][dest].exists)
        return;
    
    this->edgeMatrix[orig][dest].exists = true;
    this->edgeMatrix[orig][dest].cost = cost;

    if(!this->isDirected){
        this->edgeMatrix[dest][orig].exists = true;
        this->edgeMatrix[dest][orig].cost = cost;
    }
}

template<unsigned SIZE>
void Graph<SIZE>::delEdge(const std::string& o, const std::string& d){
    int orig(this->getIdx(o));
    int dest(this->getIdx(d));
    
    if(orig == -1 || dest == -1)
        return;

    this->edgeMatrix[orig][dest].exists = false;    
    
    if(!this->isDirected){
        this->edgeMatrix[dest][orig].exists = false;    
    }
}

template<unsigned SIZE>
Graph<SIZE>& Graph<SIZE>::operator = (const Graph<SIZE>& other){
    this->copyAll(other);
    return *this;
}
