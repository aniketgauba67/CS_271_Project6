#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

template<typename D, typename K>
class Graph {
public:
    struct Vertex {
        D data;
        K key;
        vector<Vertex*> adj;
        int distance;
    };

    Graph(const vector<K>& keys, const vector<D>& data, const vector<vector<K>>& edges);
    const Vertex* get(K key) const;
    bool reachable(const K& u, const K& v);
    void bfs(const K& s);
    void print_path(const K& u, const K& v);
    string edge_class(const K& u, const K& v);
    void bfs_tree(const K& s);
    bool edge_exists(const K& u, const K& v);

private:    
    unordered_map<K, Vertex> vertices;
};

#endif // GRAPH_H
