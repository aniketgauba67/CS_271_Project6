#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

template<typename D, typename K>
class Graph {
public:
    Graph(const vector<K>& keys, const vector<D>& data, const vector<vector<K>>& edges);
    Vertex* get(const K& key);
    bool reachable(const K& u, const K& v);
    void bfs(const K& s);
    void print_path(const K& u, const K& v);
    string edge_class(const K& u, const K& v);
    void bfs_tree(const K& s);

private:
    struct Vertex {
        D data;
        K key;
        vector<Vertex*> adj;
    };
    
    unordered_map<K, Vertex> vertices;
};

#endif // GRAPH_H
