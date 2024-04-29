#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

using namespace std;

template <typename DataType, typename KeyType>
class Vertex {
public:
    Vertex(DataType initData, KeyType initKey) : data(initData), key(initKey) {}

    Vertex() : data(DataType()), key(KeyType()) {}

    DataType data;
    KeyType key;

    struct BFSProperties {
        int distance = 0;
        bool visited = false;
        Vertex<DataType, KeyType>* predecessor = nullptr;
        int finishTime = 0;
        vector<KeyType> adjacencyList;
    };

    BFSProperties bfsProps;
};

#endif
