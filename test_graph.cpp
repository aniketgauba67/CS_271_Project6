//
//  test_graph_example.cpp
//  CS 271 Graph Project: Example Test File
//
//  Created by Dr. Stacey Truex
//

#include <fstream>
#include <sstream>
#include "graph.cpp"

Graph<string, string> *generate_graph(string fname)
{
    string line;
    ifstream infile(fname);
    vector<string> keys = {};
    vector<string> data = {};
    vector<vector<string>> adjs = {};
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            size_t delim = line.find(":");
            string key = line.substr(0, delim);
            string adj = line.substr(delim + 1);

            keys.push_back(key);
            data.push_back(key + " data");
            delim = adj.find(",");
            vector<string> adj_lst = {};
            while (delim != string::npos)
            {
                adj_lst.push_back(adj.substr(0, delim));
                adj = adj.substr(delim + 1);
                delim = adj.find(",");
            }
            adj_lst.push_back(adj);
            adjs.push_back(adj_lst);
        }
        infile.close();
    }
    Graph<string, string> *G = new Graph<string, string>(keys, data, adjs);
    return G;
}

void test_get(Graph<string, string> *G)
{
    try
    {
        if (G->get("S") == nullptr || G->get("S")->data != "S data")
        {
            cout << "Incorrect result getting vertex \"s\"" << endl;
        }
        if (G->get("a") != nullptr)
        {
            cout << "Incorrect result getting non-existant vertex \"a\"" << endl;
        }
    }
    // Testing with string keys and string data
    Graph<string, string> stringGraph;
    stringGraph.addVertex("S", "S data");
    stringGraph.addVertex("T", "T data");

    try {
        const auto sResult = stringGraph.get("S");
        const auto tResult = stringGraph.get("T");
        const auto noResult = stringGraph.get("A");

        if (sResult == nullptr || sResult->data != "S data") {
            cout << "Incorrect result getting vertex \"S\"" << endl;
        }
        if (tResult == nullptr || tResult->data != "T data") {
            cout << "Incorrect result getting vertex \"T\"" << endl;
        }
        if (noResult != nullptr) {
            cout << "Incorrect result: Non-existent vertex \"A\" was found" << endl;
        }
    }
    catch (exception& e) {
        cerr << "Error testing string graph: " << e.what() << endl;
    }

    // Testing with int keys and double data
    Graph<double, int> intDoubleGraph;
    intDoubleGraph.addVertex(1, 1.1);
    intDoubleGraph.addVertex(2, 2.2);

    try {
        const auto oneResult = intDoubleGraph.get(1);
        const auto twoResult = intDoubleGraph.get(2);
        const auto noIntResult = intDoubleGraph.get(3);

        if (oneResult == nullptr || oneResult->data != 1.1) {
            cout << "Incorrect result getting vertex 1" << endl;
        }
        if (twoResult == nullptr || twoResult->data != 2.2) {
            cout << "Incorrect result getting vertex 2" << endl;
        }
        if (noIntResult != nullptr) {
            cout << "Incorrect result: Non-existent vertex 3 was found" << endl;
        }
    }
    catch (exception& e) {
        cerr << "Error testing int-double graph: " << e.what() << endl;
    }

    // Empty graph test
    Graph<int, string> emptyGraph;
    try {
        const auto emptyResult = emptyGraph.get("Empty");
        if (emptyResult != nullptr) {
            cout << "Error: Got a vertex from an empty graph" << endl;
        }
    }
    catch (exception& e) {
        cerr << "Error testing empty graph: " << e.what() << endl;
    }
}


void test_reachable(Graph<string, string> *G)
{
    try
    {
        if (!G->reachable("R", "V"))
        {
            cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"R\"" << endl;
        }
        if (!G->reachable("X", "W"))
        {
            cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
        }
        if (G->reachable("S", "A"))
        {
            cout << "Incorrectly identified non-existant vetex \"A\" as reachable from \"S\"" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing reachable : " << e.what() << endl;
    }
}

void test_bfs(Graph<string, string> *G)
{
    try
    {
        G->bfs("T");
        string vertices[8] = {"V", "R", "S", "W", "T", "X", "U", "Y"};
        int distances[8] = {3, 2, 1, 1, 0, 2, 1, 2};
        for (int i = 0; i < 8; i++)
        {
            if (G->get(vertices[i]) == nullptr || G->get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"t\"" << endl;
            }
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs : " << e.what() << endl;
    }
}

void test_print_path(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("T", "V");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T -> S -> R -> V")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: T -> S -> R -> V but got : " << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}

// void test_edge_class(Graph<string, string> *G)
// {
//     try
//     {
//         string e_class = G->edge_class("R", "V"); // tree edge
//         if (e_class != "tree edge")
//         {
//             cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
//         }
//         e_class = G->edge_class("X", "U"); // back edge
//         if (e_class != "back edge")
//         {
//             cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
//         }
//         e_class = G->edge_class("R", "U"); // no edge
//         if (e_class != "no edge")
//         {
//             cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
//         }
//         e_class = G->edge_class("T", "W"); // forward edge
//         if (e_class != "forward edge")
//         {
//             cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
//         }
//         e_class = G->edge_class("T", "S"); // cross edge
//         if (e_class != "cross edge")
//         {
//             cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
//         }
//     }
//     catch (exception &e)
//     {
//         cerr << "Error testing edge class : " << e.what() << endl;
//     }
// }

void test_bfs_tree(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T\nS U W\nR Y X\nV")
        {
            cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n"
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
}







// For the get function

void test_get_more_complex(Graph<int, string> *G) {
    // Test retrieval after multiple sequential modifications
    try {
        // Add multiple vertices
        G->add_vertex("AA", 12);
        G->add_vertex("BB", 13);
        G->add_vertex("CC", 14);

        // Remove vertex and then test retrieval of remaining vertices
        G->remove_vertex("BB");
        if (G->get("BB") != nullptr) {
            cout << "Test failed: 'get(\"BB\")' after removal should return nullptr" << endl;
        }

        if (G->get("AA") == nullptr || G->get("AA")->data != 12) {
            cout << "Test failed: 'get(\"AA\")' should return vertex with data 12" << endl;
        }
        
        if (G->get("CC") == nullptr || G->get("CC")->data != 14) {
            cout << "Test failed: 'get(\"CC\")' should return vertex with data 14" << endl;
        }

        // Re-add a vertex previously deleted and check its data retrieval
        G->add_vertex("BB", 15);
        auto result = G->get("BB");
        if (result == nullptr || result->data != 15) {
            cout << "Test failed: 'get(\"BB\")' after re-adding should return vertex with data 15" << endl;
        }
    } catch (exception &e) {
        cerr << "Error in more complex get test: " << e.what() << endl;
    }
}






// Test for the reachable function

void test_reachable_Ryan_test(Graph<int, string> *G) {
    // Testing reachability after complex graph manipulations
    try {
        G->add_edge("AA", "CC");
        G->add_edge("CC", "BB");
        G->add_vertex("DD", 16);
        G->add_edge("BB", "DD");

        if (!G->reachable("AA", "DD")) {
            cout << "Test failed: 'DD' should be reachable from 'AA' through 'CC' and 'BB'" << endl;
        }

        G->remove_edge("CC", "BB");
        if (G->reachable("AA", "DD")) {
            cout << "Test failed: 'DD' should not be reachable from 'AA' after removing 'CC' to 'BB' edge" << endl;
        }

        // Ensure reachability is correctly updated after re-adding the edge
        G->add_edge("CC", "BB");
        if (!G->reachable("AA", "DD")) {
            cout << "Test failed: 'DD' should be reachable from 'AA' after re-adding 'CC' to 'BB' edge" << endl;
        }
    } catch (exception &e) {
        cerr << "Error in more complex reachable test: " << e.what() << endl;
    }
}




int main()
{

    Graph<string, string> *G = generate_graph("graph_description.txt");
    test_get(G);
    test_reachable(G);
    test_bfs(G);
    test_print_path(G);
    //test_edge_class(G);
    test_bfs_tree(G);


    test_get_more_complex(G);
    test_reachable_Ryan_test(G);

    cout << "Testing completed" << endl;

    delete G;

    return 0;
}
