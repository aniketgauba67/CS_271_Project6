#include "graph.h"
#include <iostream>
#include <vector>
#include <map>


using namespace std;

// Constructor Class
template<typename D, typename K>
Graph<D, K>::Graph(const vector<K>& keys, const vector<D>& data, const vector<vector<K>>& edges) {
    if (keys.size() != data.size() || keys.size() != edges.size()) {
        return;
    }

    for (size_t i = 0; i < keys.size(); ++i) {
        vertices[keys[i]].data = data[i];
        vertices[keys[i]].key = keys[i];
    }

    for (size_t i = 0; i < edges.size(); ++i) {
        for (const K& key : edges[i]) {
            vertices[keys[i]].adj.push_back(&vertices[key]);
        }
    }
}

// Get Function
template<typename D, typename K>
Vertex<D, K>* Graph<D, K>::get(K key) const{
    int length = vetices.size();

    for(int i = 0; i<len; i++){
        if(vertices[i]->key == key){
            return vertices[i];
        }
    }
    return nullptr;
}


// edge exists functions
template<typename D, typename K>
bool Graph<D, K>::edge_exists(const K& u, const K& v) {
    Vertex* u_vertex = get(u);
    if (u_vertex == nullptr) {
        return false;
    }
    for (Vertex* adj_vertex : u_vertex->adj) {
        if (adj_vertex->key == v) {
            return true;
        }
    }
    return false;
}




