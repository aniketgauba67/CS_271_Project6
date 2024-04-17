#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <unordered_map>

template<typename D, typename K>
class Graph {
public:
    Graph(const std::vector<K>& keys, const std::vector<D>& data, const std::vector<std::vector<K>>& edges);
    
    D* get(const K& key);
    bool reachable(const K& u, const K& v);
    void bfs(const K& s);
    void print_path(const K& u, const K& v);
    std::string edge_class(const K& u, const K& v);
    void bfs_tree(const K& s);

private:
    struct Vertex {
        D data;
        K key;
        std::vector<Vertex*> adj;
    };
    
    std::unordered_map<K, Vertex> vertices;
};

#endif // GRAPH_H
