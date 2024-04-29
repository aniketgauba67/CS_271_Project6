#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

#include "vertex.h"

using namespace std;

template <typename D, typename K>
class Graph {
    public:
        Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges);
        Vertex<D,K>* get(K key);
        bool reachable(K u, K v);
        void print_path(K u, K v);
        string edge_class(K u, K v);
        void bfs(K s);
        void bfs_tree(K s);

    private:
        vector<Vertex<D,K>*> vertices;
        vector<vector<K>> edges;
        void print_path(K u, K v, string suff);
        void dfs(K s);
        void dfs_visit(Vertex<D,K>* u, int* time);
};

#endif

