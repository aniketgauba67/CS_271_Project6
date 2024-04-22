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
        bool color; 
        K pi; 
        int f; 
    };

    Graph(const vector<K>& keys, const vector<D>& data, const vector<vector<K>>& edges);
    Vertex* get(K key);
    bool reachable(const K& u, const K& v);
    void bfs(const K& s);
    void print_path(const K& u, const K& v);
    string edge_class(const K u, const K v);
    bool edge_exists(const K& u, const K& v);
    void bfs_tree(const K& s);3
    void dfs(const K& s);
    void dfsUtil(const K& v, const K& parent, int& time);
    bool is_descendant(K u, K v);

private:    
    unordered_map<K, Vertex> vertices;
};

#endif // GRAPH_H
