#include "graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <list>

using namespace std;

// Constructor Class
template <typename D, typename K>
Graph<D, K>::Graph(const vector<K> &keys, const vector<D> &data, const vector<vector<K>> &edges)
{
    if (keys.size() != data.size() || keys.size() != edges.size())
    {
        return;
    }

    for (size_t i = 0; i < keys.size(); ++i)
    {
        vertices[keys[i]].data = data[i];
        vertices[keys[i]].key = keys[i];
    }

    for (size_t i = 0; i < edges.size(); ++i)
    {
        for (const K &key : edges[i])
        {
            vertices[keys[i]].adj.push_back(&vertices[key]);
        }
    }
}

// Get Function
template <typename D, typename K>
const typename Graph<D, K>::Vertex *Graph<D, K>::get(K key) const
{
    for (const auto &pair : vertices)
    {
        if (pair.second.key == key)
        {
            return &pair.second;
        }
    }
    return nullptr;
}

// edge exists functions
template <typename D, typename K>
bool Graph<D, K>::edge_exists(const K &u, const K &v)
{
    Vertex *u_vertex = get(u);
    if (u_vertex == nullptr)
    {
        return false;
    }
    for (Vertex *adj_vertex : u_vertex->adj)
    {
        if (adj_vertex->key == v)
        {
            return true;
        }
    }
    return false;
}

template <typename D, typename K>
bool Graph<D, K>::reachable(const K &u, const K &v)
{
    // Create a map to store visited vertices
    unordered_map<K, bool> visited;

    // Create a queue for BFS
    queue<Vertex *> queue;

    // Mark the current node as visited and enqueue it
    visited[u] = true;
    queue.push(&vertices[u]);

    while (!queue.empty())
    {
        // Dequeue a vertex from queue
        Vertex *vertex = queue.front();
        queue.pop();

        // Get all adjacent vertices of the dequeued vertex
        // If an adjacent vertex has not been visited, then mark it visited and enqueue it
        for (auto i = vertex->adj.begin(); i != vertex->adj.end(); ++i)
        {
            if (!visited[(*i)->key])
            {
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

// Create the function print_path
template <typename D, typename K>
void print_path(K u, K v, std::unordered_map<K, std::list<K>> &graph)
{
    // Check if the start and end vertices are in the graph
    if (graph.find(u) == graph.end() || graph.find(v) == graph.end())
    {
        std::cout << "Invalid vertex key" << std::endl;
        return;
    }
    std::queue<K> q;                      // Queue for BFS
    std::unordered_map<K, K> predecessor; // Map to store the predecessor of each vertex
    std::unordered_set<K> visited;        // Set to store visited vertices
    std::list<K> path;

    // Start BFS from the vertex 'u'
    q.push(u);
    visited.insert(u);
    bool found = false;
    while (!q.empty() && !found)
    {
        K current = q.front();
        q.pop();
        // Check if we have reached the destination vertex
        if (current == v)
        {
            found = true;
            break;
        }
        // Explore each adjacent vertex
        for (const K &adj : graph[current])
        {
            if (visited.find(adj) == visited.end())
            {
                visited.insert(adj);
                q.push(adj);
                predecessor[adj] = current;
            }
        }
    }
    // If 'v' was not reached from 'u'
    if (!found)
    {
        std::cout << "No path exists from " << u << " to " << v << std::endl;
        return;
    }

    // Backtrack from 'v' to 'u' using the 'predecessor' map to find the path
    for (K current = v; current != u; current = predecessor[current])
    {
        path.push_front(current);
    }
    path.push_front(u);

    // Print the path
    auto it = path.begin();
    std::cout << *it;
    ++it;
    while (it != path.end())
    {
        std::cout << " -> " << *it;
        ++it;
    }
    std::cout << std::endl;
}
