#include "graph.h"
#include <iostream>
#include <vector>


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
Vertex* Graph<D, K>::get(const K& key) {

}





