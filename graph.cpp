#include "graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_set>
#include <list>
#include <stack>
#include <unordered_map>
#include <string>


using namespace std;
//========================================================
// Graph
// Constructs a graph using specified nodes, data, and edges.
// Parameters: keys, data, edges 
// Pre-condition:
//  keys, data, and edges must all be of the same size, ensuring that each key
//  has corresponding node data and a list of edges.
//  Each value in the edges vector must be a valid key existing within the keys vector.
// Post-condition:
//  A new Graph object is created with each node initialized with its key, data,
//  and adjacency list. Nodes are interconnected as per the adjacency lists provided
//  in `edges`. If the preconditions are not met, the graph may be partially constructed
//  or not constructed at all, particularly if the vector sizes mismatch, in which case
//  the constructor will terminate early.
// Return: None
//========================================================
template<typename D, typename K>
Graph<D, K>::Graph(const vector<K>& keys, const vector<D>& data, const vector<vector<K>>& edges) {
    if (keys.size() != data.size() || keys.size() != edges.size()) {
        return;  // Early return if sizes do not match, ensuring precondition is met.
    }

    for (size_t i = 0; i < keys.size(); ++i) {
        vertices[keys[i]].data = data[i];  // Mapping data to keys.
        vertices[keys[i]].key = keys[i];   // Storing the key inside the node.
    }

    for (size_t i = 0; i < edges.size(); ++i) {
        for (const K& key : edges[i]) {
            vertices[keys[i]].adj.push_back(&vertices[key]);  // Establishing node connections.
        }
    }
}

//========================================================
// Get
// Retrieves a vertex from the graph using its unique key.
// Parameters: key
// Pre-condition: None 
// Post-condition: None 
// Return: Constant pointer to the vertex if the key is found, otherwise nullptr.
//========================================================

template<typename D, typename K>
typename Graph<D, K>::Vertex* Graph<D, K>::get(K key) {
    // Iterate over all vertices in the graph's vertex map
    for (auto& pair : vertices) {
        // Check if the current vertex's key matches the given key
        if (pair.second.key == key) {
            return &pair.second; // Return a pointer to the vertex if key matches
        }
    }
    return nullptr; // Return nullptr if the key is not found in any vertex
}


//========================================================
// Edge Exists
// Determines whether an edge exists between two vertices identified by their keys.
// Parameters:
//   u - The key of the first vertex.
//   v - The key of the second vertex.
// Pre-condition: None
// Post-condition: None
// Return:
//   Boolean value indicating whether an edge exists between the two vertices:
//   returns true if there is an edge from vertex u to vertex v, otherwise false.
//========================================================
template<typename D, typename K>
bool Graph<D, K>::edge_exists(const K& u, const K& v) {
    Vertex* u_vertex = get(u);  // Retrieve the vertex corresponding to key u
    if (u_vertex == nullptr) {
        return false;  // If vertex u does not exist, return false
    }
    // Check if any of the adjacent vertices of u has the key v
    for (Vertex* adj_vertex : u_vertex->adj) {
        if (adj_vertex->key == v) {
            return true;  // Return true if vertex v is found in the adjacency list of vertex u
        }
    }
    return false;  // Return false if no adjacency from u to v is found
}

//========================================================
// Reachable
// Determines if there is a path from vertex u to vertex v using Breadth-First Search (BFS).
// Parameters:
//   u - The key of the starting vertex.
//   v - The key of the destination vertex.
// Pre-condition:
//   Both u and v should be valid keys of vertices within the graph.
// Post-condition: None
// Return:
//   Boolean value indicating whether there is a path from u to v:
//   returns true if such a path exists, otherwise false.
//========================================================
template<typename D, typename K>
bool Graph<D, K>::reachable(const K& u, const K& v) {
    // Create a map to track visited vertices
    unordered_map<K, bool> visited;

    // Initialize a queue for BFS
    queue<Vertex*> queue;

    // Start from the vertex u
    visited[u] = true;
    queue.push(&vertices[u]);

    while (!queue.empty()) {
        // Process the front vertex in the queue
        Vertex* vertex = queue.front();
        queue.pop();

        // Explore all adjacent vertices
        for (auto i = vertex->adj.begin(); i != vertex->adj.end(); ++i) {
            if (!visited[(*i)->key]) {
                // Check if the adjacent vertex is the destination
                if ((*i)->key == v)
                    return true;

                // Mark the vertex as visited and add to the queue
                visited[(*i)->key] = true;
                queue.push(*i);
            }
        }
    }
    
    // Return false if no path found after BFS completion
    return false;
}


//========================================================
// BFS (Breadth-First Search)
// Performs a breadth-first search on the graph starting from a given vertex,
// marking each visited node and updating the distance from the start vertex.
// Parameters:
//   s - The key of the starting vertex for BFS.
// Pre-condition:
//   s should be a valid key of a vertex within the graph.
// Post-condition:
//   Marks all reachable vertices from s as visited, assigns distances from s,
//   and explores the graph layer by layer.
// Return: None
//========================================================
template<typename D, typename K>
void Graph<D, K>::bfs(const K& s) {
    // Map to store the visited status of each vertex
    unordered_map<K, bool> visited;

    // Queue to manage the BFS frontier
    queue<Vertex*> queue;

    // Initialize the starting vertex
    visited[s] = true;
    vertices[s].distance = 0;  // Distance from start vertex to itself is 0
    queue.push(&vertices[s]);

    while (!queue.empty()) {
        // Process the current vertex at the front of the queue
        Vertex* vertex = queue.front();
        queue.pop();

        // Explore each adjacent vertex
        for (auto i = vertex->adj.begin(); i != vertex->adj.end(); ++i) {
            if (!visited[(*i)->key]) {
                visited[(*i)->key] = true;               // Mark the vertex as visited
                (*i)->distance = vertex->distance + 1;  // Update the distance for this vertex
                queue.push(*i);                         // Enqueue the vertex for further exploration
            }
        }
    }
}

//========================================================
// Print Path
// Finds and prints the shortest path between two vertices using BFS.
// Parameters:
//   u - The key of the starting vertex.
//   v - The key of the destination vertex.
// Pre-condition:
//   Both u and v should be valid keys of vertices within the graph.
// Post-condition:
//   Prints the shortest path from vertex u to vertex v if it exists.
//   If no path exists, a message indicating non-existence is printed.
// Return: None 
//========================================================
template<typename D, typename K>
void Graph<D, K>::print_path(const K& u, const K& v) {
    unordered_map<K, bool> visited;
    unordered_map<K, K> parent;  // Maps each vertex to its parent in the BFS tree

    // Queue for managing the BFS frontier
    queue<Vertex*> queue;

    // Initialize BFS from the starting vertex
    visited[u] = true;
    queue.push(&vertices[u]);

    while (!queue.empty()) {
        Vertex* vertex = queue.front();  // Dequeue the front vertex
        queue.pop();

        // Explore all adjacent vertices
        for (auto i = vertex->adj.begin(); i != vertex->adj.end(); ++i) {
            if (!visited[(*i)->key]) {
                visited[(*i)->key] = true;       // Mark vertex as visited
                parent[(*i)->key] = vertex->key; // Record its parent
                queue.push(*i);                  // Enqueue for further exploration
            }
        }
    }

    // Check if the destination was reached during the BFS
    if (!visited[v]) {
        cout << "No path exists from: " << u << " to " << v << endl;
        return;
    }

    // Reconstruct the path from end vertex to start vertex using the parent map
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
    cout << flush;  // Ensure the output is flushed to stdout
}

//========================================================
// BFS Tree
// Constructs a BFS tree from a starting vertex and prints the tree level by level.
// Parameters:
//   s - The key of the starting vertex for the BFS tree.
// Pre-condition:
//   s should be a valid key of a vertex within the graph.
// Post-condition:
//   Outputs the BFS tree, showing vertices grouped by their depth levels,
//   and prints each level on a new line.
// Return: None 
//========================================================
template<typename D, typename K>
void Graph<D, K>::bfs_tree(const K& s) {
    unordered_map<K, bool> visited; // Tracks which vertices have been visited
    queue<Vertex*> queue; // Manages the BFS queue

    // Start BFS with the root vertex
    visited[s] = true;
    queue.push(&vertices[s]);

    // Maps to track depth and vertices at each depth
    unordered_map<K, int> depth;
    depth[s] = 0;
    map<int, vector<K>> levels; // Sorted map to maintain levels ordered
    levels[0].push_back(s);

    while (!queue.empty()) {
        Vertex* vertex = queue.front();
        queue.pop();

        // Process each adjacent vertex
        for (auto i = vertex->adj.begin(); i != vertex->adj.end(); ++i) {
            if (!visited[(*i)->key]) {
                visited[(*i)->key] = true;
                depth[(*i)->key] = depth[vertex->key] + 1; // Set depth for each vertex
                levels[depth[(*i)->key]].push_back((*i)->key); // Add vertex to the appropriate level
                queue.push(*i);
            }
        }
    }

    // Print the BFS tree by levels
    for (auto it = levels.begin(); it != levels.end(); ++it) {
        for (size_t i = 0; i < it->second.size(); i++) {
            cout << it->second[i];
            if (i != it->second.size() - 1) {
                cout << " ";
            }
        }
        if (next(it) != levels.end()) {
            cout << endl;
        }
    }
}

// template<typename D, typename K>
// string edge_class(int u, int v, const vector<vector<int>>& adjList)
// {
//     map<int, int> level;
//     queue<int> q;
//     q.push(u);
//     level[u] = 0;

//     while (!q.empty())
//     {
//         int current = q.front();
//         q.pop();

//         for (int adj : adjList[current])
//         {
//             if (level.count(adj) == 0)
//             {
//                 q.push(adj);
//                 level[adj] = level[current] + 1;
//             }
//         }
//     }

//     if (level.count(v) == 0)
//     {
//         return "no edge";
//     }
//     else if (level[v] == level[u] + 1)
//     {
//         return "tree edge";
//     }
//     else if (level[v] < level[u])
//     {
//         return "back edge";
//     }
//     else if (level[v] > level[u] + 1)
//     {
//         return "forward edge";
//     }
//     else if (level[v] == level[u])
//     {
//         return "cross edge";
//     }
// }


template<typename D, typename K>
void Graph<D, K>::dfs(const K& s) {
    // Initialize all vertices as not visited
    for (auto& pair : vertices) {
        pair.second.color = false;
        pair.second.pi = "no parent"; // Initialize parent of all vertices as "no parent"
    }

    int time = 0; // Initialize time

    // Call the recursive helper function
    dfsUtil(s, "no parent", time); // Pass "no parent" as parent of source vertex
}


template<typename D, typename K>
void Graph<D, K>::dfsUtil(const K& v, const K& parent, int& time) {
    // Mark the current node as visited and set its parent
    vertices[v].color = true;
    vertices[v].pi = parent;

    // Update the discovery time
    vertices[v].distance = ++time;

    // Recur for all vertices adjacent to this vertex
    for (Vertex* i : vertices[v].adj) {
        if (!i->color) {
            dfsUtil(i->key, v, time);
        }
    }

    // Update the finish time
    vertices[v].f = ++time;
}

template <class D, class K> 
bool Graph<D, K>::is_descendant(K u, K v) 
{ 
    Vertex* v1 = get(u); 
    Vertex* v2 = get(v); 

    // Check if v2 is a descendant of v1
    while (v2 != nullptr && v2->key != v1->key) {
        v2 = get(v2->pi);
    }

    return v2 != nullptr;
}

template <class D, class K> 
string Graph<D, K>::edge_class(K u, K v) 
{ 
    Vertex* v1 = get(u); 
    Vertex* v2 = get(v); 

    // Determine the correct starting point for the DFS
    K start = (v1->distance < v2->distance) ? u : v;

    // Perform the DFS
    dfs(start);

    if (v1->color == false || v2->color == false) { 
        // If one of the vertices is not in the graph. 
        return "no edge"; 
    } 
    else if (v2->pi == v1->key && v2->distance > v1->distance) 
    { 
        // Tree edge, v2 is a direct descendant of v1
        return "tree edge";
    
    } 
    else if (v2->distance > v1->distance && v2->f < v1->f && is_descendant(u, v) && v2->pi != v1->key) 
    { 
        // Forward edge, v2 is a descendant of v1 but not a direct child
        return "forward edge";
    } 
    else if (v2->distance <= v1->distance && v2->f > v1->f)
    { 
        // Back edge, v2 is an ancestor of v1
        return "back edge";
    } 
    else if (v2->distance < v2->f && v1->distance < v1->f) 
    {
        // Cross edge, neither node is an ancestor or descendant to the other
        return "cross edge"; 
    }
    
    return "no edge"; 
}

