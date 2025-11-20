#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <string>

template <unsigned SIZE = 10> 
class Graph{
    private:
        class Vertex{
            public:
                bool exists = false;
                std::string label;
        };

        class Edge {
            public:
                bool exists = false;
                float cost = 1;
        };

        Vertex vertexArray[SIZE];
        Edge edgeMatrix[SIZE][SIZE];

        bool isWeighted = true;
        bool isDirected = true;

        unsigned counter = 0;

        int getIdx(const std::string&);

        void copyAll(const Graph<SIZE>&);
    public:
        Graph();
        Graph(const Graph<SIZE>&);

        bool isEmpty() const;
        bool isFull() const;

        bool getIsDirected() const;
        bool getWeighted() const:

        void setWeighted(const bool&);
        void setIsDirected(const bool&);

        std::string toString() const;

        void addVertex(const std::string&);
        void delVertex(const std::string&);

        void addEdge(const std::string&, const std::string&, const float& = 1);
        void delEdge(const std::string&, const std::string&);



        Graph<SIZE>& operator = (const Graph<SIZE>&);

};


#endif // __GRAPH_H__