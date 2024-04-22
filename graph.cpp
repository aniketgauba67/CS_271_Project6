#include "graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_set>
#include <list>
#include <stack>
#include <unordered_map>


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
const typename Graph<D, K>::Vertex* Graph<D, K>::get(K key) const{
    for(const auto& pair : vertices){
        if(pair.second.key == key){
            return &pair.second;
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

template<typename D, typename K>
bool Graph<D, K>::reachable(const K& u, const K& v) {
    // Create a map to store visited vertices
    unordered_map<K, bool> visited;

    // Create a queue for BFS
    queue<Vertex*> queue;

    // Mark the current node as visited and enqueue it
    visited[u] = true;
    queue.push(&vertices[u]);

    while(!queue.empty()) {
        // Dequeue a vertex from queue
        Vertex* vertex = queue.front();
        queue.pop();

        // Get all adjacent vertices of the dequeued vertex
        // If an adjacent vertex has not been visited, then mark it visited and enqueue it
        for(auto i = vertex->adj.begin(); i != vertex->adj.end(); ++i) {
            if (!visited[(*i)->key]) {
                // If this adjacent node is the destination node, return true
                if ((*i)->key == v)
                    return true;

                visited[(*i)->key] = true;
                queue.push(*i);
            }
        }
    }

    // If BFS is complete without visiting v
    return false;
}

template<typename D, typename K>
void Graph<D, K>::bfs(const K& s) {
    // Create a map to store visited vertices
    unordered_map<K, bool> visited;

    // Create a queue for BFS
    queue<Vertex*> queue;

    // Mark the current node as visited and enqueue it
    visited[s] = true;
    vertices[s].distance = 0;  
    queue.push(&vertices[s]);

    while(!queue.empty()) {
        // Dequeue a vertex from queue and print it
        Vertex* vertex = queue.front();
        queue.pop();


        // Get all adjacent vertices of the dequeued vertex
        // If an adjacent vertex has not been visited, then mark it visited, update distance and enqueue it
        for(auto i = vertex->adj.begin(); i != vertex->adj.end(); i++) {
            if (!visited[(*i)->key]) {
                visited[(*i)->key] = true;
                (*i)->distance = vertex->distance + 1;  // Update distance
                queue.push(*i);
            }
        }
    }
}

template<typename D, typename K>
void Graph<D, K>::print_path(const K& u, const K& v) {

    unordered_map<K, bool> visited;
    unordered_map<K, K> parent;

    // Create a queue for BFS
    queue<Vertex*> queue;

    // Mark the current node as visited and enqueue it
    visited[u] = true;
    queue.push(&vertices[u]);

    while(!queue.empty()) {

        // Dequeue a vertex from queue
        Vertex* vertex = queue.front();
        queue.pop();

        // Get all adjacent vertices thats been de-queued
        // If an adjacent vertex has not been visited, then mark it visited, update parent and enqueue it
        for(auto i = vertex->adj.begin(); i != vertex->adj.end(); ++i) {
            if (!visited[(*i)->key]) {
                visited[(*i)->key] = true;
                parent[(*i)->key] = vertex->key;  // Update parent
                queue.push(*i);
            }
        }
    }

    // If BFS is complete without visiting v
    if (!visited[v]) {
        cout << "No path exists from: " << u << " and " << v << endl;
        return;
    }

    // If a path exists, we get it from the parent
    list<K> path;
    for (K vertex = v; vertex != u; vertex = parent[vertex]) {
        path.push_front(vertex);
    }
    path.push_front(u);

    // Print the path
    auto it = path.begin();
    cout << *it;
    for (++it; it != path.end(); ++it) {
        cout << " -> " << *it;
    }

    // THis removes any white space that gives us an error
    cout << flush;
}



