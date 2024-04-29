#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

#include "vertex.h"
#include "graph.h"

using namespace std;
//========================================================
// Constructor: Graph
// Purpose: Constructs a graph data structure by initializing vertices with provided data and connecting them according to the specified adjacency lists.
// Parameters:
//   - vertexKeys
//   - vertexData 
//   - adjacencyLists
// Preconditions:
//   - The size of vertexKeys, vertexData, and adjacencyLists must be the same, ensuring that each vertex key has an associated data entry and an adjacency list.
//   - Each key within the sub-vectors of adjacencyLists should exist within vertexKeys to ensure all connections refer to valid vertices.
// Postconditions:
//   - A graph is created with vertices initialized with corresponding keys and data. Each vertex is connected to others as specified by the adjacencyLists.
//   - If the precondition is not met (e.g., mismatched vector sizes or invalid keys in adjacencyLists), the constructor may throw an exception or result in an incomplete or invalid graph construction.
// Return: None 
//========================================================

template <typename DataType, typename KeyType>
Graph<DataType, KeyType>::Graph(vector<KeyType> vertexKeys, vector<DataType> vertexData, vector<vector<KeyType>> adjacencyLists)
{
    Vertex<DataType, KeyType> *newVertex;
    for (int i = 0; i < vertexKeys.size(); ++i)
    {
        newVertex = new Vertex<DataType, KeyType>(vertexData[i], vertexKeys[i]); // Create a new vertex with data and key
        newVertex->bfsProps.adjacencyList = adjacencyLists[i]; // Assign the adjacency list to the vertex's BFS properties
        this->vertices.push_back(newVertex); // Add the new vertex to the graph's vertex list
    }
}

//========================================================
// Method: get
// Purpose: Retrieves a vertex from the graph based on the specified search key.
// Parameters:
//   - searchKey (KeyType)
// Preconditions: None
// Postconditions: None
// Returns:
//   - Vertex<DataType, KeyType>*: A pointer to the vertex with the matching key, if found.
//   - nullptr: If no vertex with the specified key is found in the graph.
//========================================================

template <typename DataType, typename KeyType>
Vertex<DataType, KeyType>* Graph<DataType, KeyType>::get(KeyType searchKey)
{
    for (int index = 0; index < vertices.size(); ++index)
    {
        if (vertices[index]->key == searchKey)
        {
            return vertices[index]; // Return the vertex if the key matches
        }
    }

    return nullptr; // Return nullptr if no vertex matches the search key
}


//========================================================
// Method: bfs
// Purpose: Performs a breadth-first search (BFS) on the graph starting from the specified vertex.
// Parameters:
//   - startKey
// Precondition: None
// Postcondition: None
// Return: None
//========================================================

template <typename DataType, typename KeyType>
void Graph<DataType, KeyType>::bfs(KeyType startKey)
{
    Vertex<DataType, KeyType> *nextVertex;
    queue<Vertex<DataType, KeyType> *> vertexQueue;
    Vertex<DataType, KeyType> *currentVertex = this->get(startKey);

    // Reset all vertices to default state
    for (Vertex<DataType, KeyType> *vertex : this->vertices)
    {
        vertex->color = false;
        vertex->distance = -1;
        vertex->p = nullptr;
    }

    // Initialize the starting vertex
    currentVertex->color = true;
    currentVertex->distance = 0;
    currentVertex->p = nullptr;
    vertexQueue.push(currentVertex);

    while (!vertexQueue.empty())
    {
        currentVertex = vertexQueue.front();
        vertexQueue.pop();

        // Process each adjacent vertex
        for (KeyType adjacentKey : currentVertex->adj)
        {
            nextVertex = this->get(adjacentKey);

            if (!nextVertex->color)
            {
                nextVertex->color = true;
                nextVertex->distance = currentVertex->distance + 1;
                nextVertex->p = currentVertex;
                vertexQueue.push(nextVertex);
            }
        }
    }
}


//========================================================
// Function: print_path
// Purpose: Prints the shortest path from a starting vertex to a destination vertex.
// Parameters:
//   - startKey
//   - endKey 
// Pre-condition:
//   - Both startKey and endKey must be valid vertex keys in the graph.
// Post-condition:
//   - Outputs the path from vertex `u` to vertex `v` if a path exists.
//   - If no path is found, prints a message indicating non-existence of a path.
// Return: None
//========================================================

template <typename DataType, typename KeyType>
void Graph<DataType, KeyType>::print_path(KeyType startKey, KeyType endKey)
{
    if (isReachable(startKey, endKey))
        print_path(startKey, endKey, "");
}

template <typename DataType, typename KeyType>
void Graph<DataType, KeyType>::print_path(KeyType startKey, KeyType endKey, string suffix)
{
    Vertex<DataType, KeyType> *destinationVertex = this->get(endKey);

    stringstream output;
    if (startKey == endKey)
    {
        output << startKey;
        cout << output.str() << " -> ";
    }
    else if (destinationVertex->p == nullptr)
    {
        cout << "No path available." << endl;
    }
    else
    {
        print_path(startKey, destinationVertex->p->key, " -> ");
        output << endKey;
        cout << output.str() << suffix;
    }
    output.str("");  // Clear the contents of the stringstream
}

//========================================================
// Function: reachable
// Purpose: Determines if a vertex 'v' is reachable from another vertex 'u' using Breadth-First Search (BFS).
// Parameters:
//   - startKey 
//   - targetKey
// Preconditions:
//   - Both `startKey` and `targetKey` should be valid keys of vertices within the graph.
// Postconditions:
//   - The method does not modify the graph but updates the visitation state of the vertices.
//   - Returns a boolean indicating whether the target vertex is reachable from the start vertex.
// Return:
//   - true: If a path from `startKey` to `targetKey` exists.
//   - false: If no such path exists or if either vertex key does not correspond to an existing vertex.
//========================================================

template <typename DataType, typename KeyType>
bool Graph<DataType, KeyType>::reachable(KeyType startKey, KeyType targetKey)
{
    bfs(startKey);  // Perform BFS starting from startKey to mark all reachable vertices
    Vertex<DataType, KeyType>* targetVertex = this->get(targetKey);
    Vertex<DataType, KeyType>* startVertex = this->get(startKey);

    if (targetVertex == nullptr || startVertex == nullptr) {
        return false;  // Return false if either vertex does not exist, indicating one or both keys are invalid
    }

    return targetVertex->color;  // Return the visited state of the target vertex, true if reachable, false otherwise
}

//========================================================
// Function: bfs_tree
// Purpose: Constructs a BFS tree starting from a given vertex and prints the tree level by level.
// Parameters:
//   - startKey
// Preconditions:
//   - `startKey` must be a valid key of a vertex within the graph. If not, the method may not function correctly.
// Postconditions:
//   - Outputs the BFS tree, showing vertices grouped by their depth levels.
//   - Each depth level is printed on a new line.
// Return: None
//========================================================

template <typename DataType, typename KeyType>
void Graph<DataType, KeyType>::bfs_tree(KeyType startKey)
{
    vector<KeyType> verticesAtCurrentLevel;
    int currentLevel = 0;
    int maximumLevel = 0;

    this->bfs(startKey);  // Perform BFS to set distances and determine tree structure

    // Determine the maximum distance level from the start vertex
    for (Vertex<DataType, KeyType> *vertex : this->vertices) {
        if (vertex->distance > maximumLevel) {
            maximumLevel = vertex->distance;
        }
    }

    // Loop through each level and gather vertices at that level
    while (currentLevel <= maximumLevel) {
        verticesAtCurrentLevel.clear();
        for (Vertex<DataType, KeyType> *vertex : this->vertices) {
            if (vertex->distance == currentLevel) {
                verticesAtCurrentLevel.push_back(vertex->key);
            }
        }

        // If no vertices at the current level, break the loop
        if (verticesAtCurrentLevel.empty()) {
            break;
        }

        // Print all vertices at the current level
        cout << verticesAtCurrentLevel.front();
        for (KeyType key : verticesAtCurrentLevel) {
            if (key != verticesAtCurrentLevel.front()) {
                cout << " " << key;
            }
        }

        // Print newline unless it's the last level
        if (currentLevel != maximumLevel) {
            cout << endl;
        }

        currentLevel++;
    }
}

//========================================================
// Function: dfs_visit
// Purpose: Recursively visits vertices in a depth-first search (DFS) manner from a given vertex.
// Parameters:
//   - currentVertex 
//   - currentTime
// Preconditions:
//   - `currentVertex` should not be null and should be part of the graph.
//   - `currentTime` should be initialized prior to the first call to this method.
// Postconditions:
//   - `currentVertex` and potentially other vertices in the graph have their visited status set to true.
//   - Discovery and finishing times are set for vertices as they are visited.
// Return: None
//========================================================

template <typename DataType, typename KeyType>
void Graph<DataType, KeyType>::dfs_visit(Vertex<DataType, KeyType>* currentVertex, int* currentTime)
{
    (*currentTime)++; // Increment the global time counter
    currentVertex->discoveryTime = *currentTime; // Set the discovery time for the vertex
    currentVertex->visited = true; // Mark the vertex as visited

    Vertex<DataType, KeyType>* adjacentVertex = nullptr;

    // Explore each adjacent vertex
    for (KeyType adjacentKey : currentVertex->adj)
    {
        adjacentVertex = get(adjacentKey); // Retrieve the adjacent vertex
        if (!adjacentVertex->visited)
        {
            adjacentVertex->predecessor = currentVertex; // Set predecessor for depth-first tree
            dfs_visit(adjacentVertex, currentTime); // Recursively visit the unvisited adjacent vertex
        }
    }

    (*currentTime)++; // Increment the global time again
    currentVertex->finishingTime = *currentTime; // Set the finishing time for the vertex
}

//========================================================
// Function: dfs
// Purpose: Initiates a depth-first search (DFS) for the entire graph from a specified start vertex.
// Parameters:
//   - startKey
// Preconditions:
//   - `startKey` must be a valid key of a vertex within the graph. The vertex serves as the starting point for DFS.
// Postconditions:
//   - All vertices in the graph are visited and marked as such.
//   - Discovery and finishing times are assigned to each vertex.
//   - The graph's DFS forest (set of DFS trees) is formed, with `predecessor` links showing the paths taken during the search.
// Return: None
//========================================================

template <typename DataType, typename KeyType>
void Graph<DataType, KeyType>::dfs(KeyType startKey)
{
    // Initialize all vertices
    for (Vertex<DataType, KeyType>* vertex : this->vertices) {
        vertex->visited = false;
        vertex->predecessor = nullptr;
        vertex->discoveryTime = 0;
    }

    int* currentTime = new int(0);  // Using dynamic allocation to manage time during DFS

    // Start DFS from each unvisited vertex, to ensure all components of the graph are explored
    for (Vertex<DataType, KeyType>* vertex : this->vertices) {
        if (!vertex->visited) {
            dfs_visit(vertex, currentTime);  // Call the recursive DFS visit method
        }
    }

    delete currentTime;  // Clean up the dynamically allocated time to prevent memory leaks
}


//========================================================
// Function: edge_class
// Purpose: Classifies the type of edge between two vertices in a graph after performing a DFS.
// Parameters:
//   - startKey 
//   - endKey 
// Preconditions:
//   - Both startKey and endKey must be valid vertex keys within the graph.
// Postconditions:
//   - Returns a string representing the classification of the edge between the given vertices.
// Return:
//   - A string representing the type of edge: "tree edge", "back edge", "forward edge", "cross edge", or "no edge".
//========================================================

template <typename DataType, typename KeyType>
string Graph<DataType, KeyType>::edge_class(KeyType startKey, KeyType endKey)
{
    dfs(startKey);  // Perform DFS to determine the structure of the graph and relationships

    Vertex<DataType, KeyType>* sourceVertex = get(startKey);
    Vertex<DataType, KeyType>* targetVertex = get(endKey);

    Vertex<DataType, KeyType>* ancestor = nullptr;

    // Tree Edge: Direct parent-child relationship
    ancestor = targetVertex->predecessor;
    if (ancestor && ancestor->key == sourceVertex->key) {
        return "tree edge";
    }

    // Back Edge: Source is a descendant of the target
    ancestor = sourceVertex->predecessor;
    while (ancestor) {
        if (ancestor->key == targetVertex->key) {
            return "back edge";
        }
        ancestor = ancestor->predecessor;
    }

    // Forward Edge: Target is a descendant of the source but not a direct child
    ancestor = targetVertex->predecessor;
    while (ancestor) {
        if (ancestor->key == sourceVertex->key) {
            return "forward edge";
        }
        ancestor = ancestor->predecessor;
    }

    // No Edge: Check if there's a direct connection
    bool hasDirectConnection = false;
    for (KeyType adjacentKey : sourceVertex->adj) {
        if (adjacentKey == targetVertex->key) {
            hasDirectConnection = true;
            break;
        }
    }
    if (!hasDirectConnection) {
        return "no edge";
    }

    // If none of the above, it's a cross edge
    return "cross edge";
}

