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

void test_is_descendant(Graph<string, string> *G)
{
    try
    {
        if (!G->is_descendant("T", "V"))
        {
            cout << "Incorrectly identified \"V\" as not a descendant of \"T\"" << endl;
        }
        if (G->is_descendant("V", "T"))
        {
            cout << "Incorrectly identified \"T\" as a descendant of \"V\"" << endl;
        }
        if (G->is_descendant("S", "A"))
        {
            cout << "Incorrectly identified non-existant vertex \"A\" as a descendant of \"S\"" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing is_descendant : " << e.what() << endl;
    }
}

void test_dfs(Graph<string, string> *G)
{
    try
    {
        G->dfs("T");
        string vertices[8] = {"V", "R", "S", "W", "T", "X", "U", "Y"};
        int discovery_times[8] = {1, 2, 3, 4, 5, 6, 7, 8}; // replace with actual discovery times
        int finish_times[8] = {16, 15, 14, 13, 12, 11, 10, 9}; // replace with actual finish times
        for (int i = 0; i < 8; i++)
        {
            if (G->get(vertices[i]) == nullptr || G->get(vertices[i])->d != discovery_times[i] || G->get(vertices[i])->f != finish_times[i])
            {
                cout << "Incorrect dfs result. Vertex " << vertices[i] << " should have discovery time " << discovery_times[i] << " and finish time " << finish_times[i] << endl;
            }
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing is_descendant : " << e.what() << endl;
    }

}

void test_get(Graph<string, string> *G)
{
    try
    {
        if (G->get("S") == nullptr || G->get("S")->data != "S data")
        {
            cout << "Incorrect result getting vertex \"S\"" << endl;
        }
        if (G->get("A") != nullptr)
        {
            cout << "Incorrect result getting non-existent vertex \"A\"" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
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
        if (!G->reachable("T", "W"))
        {
            cout << "Incorrectly identified \"W\" as unreachable from \"T\"" << endl;
        }
        if (G->reachable("S", "A"))
        {
            cout << "Incorrectly identified non-existent vertex \"A\" as reachable from \"S\"" << endl;
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
        int distances[8] = {3, 2, 1, 1, 0, 2, 1, 2}; // replace with actual distances
        for (int i = 0; i < 8; i++)
        {
            if (G->get(vertices[i]) == nullptr || G->get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"T\"" << endl;
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

void test_edge_class(Graph<string, string> *G)
{
    try
    {
        string e_class = G->edge_class("R", "V"); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        }
        e_class = G->edge_class("X", "U"); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("R", "U"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existent edge (\"R\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "W"); // forward edge
        if (e_class != "forward edge")
        {
            cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "S"); // cross edge
        if (e_class != "cross edge")
        {
            cout << "Misidentified cross edge (\"T\", \"S\") as : " << e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
}

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
        cerr << "Error bfstree : " << e.what() << endl;
    }
}

void test_edge_exists(Graph<string, string> *G)
{
    try
    {
        if (!G->edge_exists("R", "V"))
        {
            cout << "Incorrectly identified edge (\"R\", \"V\") as non-existent" << endl;
        }
        if (G->edge_exists("V", "R"))
        {
            cout << "Incorrectly identified non-existent edge (\"V\", \"R\") as existent" << endl;
        }
        if (G->edge_exists("S", "A"))
        {
            cout << "Incorrectly identified edge to non-existent vertex (\"S\", \"A\") as existent" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing edge_exists : " << e.what() << endl;
    }
}

int main()
{
    Graph<string, string> *G = generate_graph("graph_description.txt");
    test_get(G);
    test_reachable(G);
    test_bfs(G);
    test_print_path(G);
    test_edge_class(G);
    test_bfs_tree(G);
    test_is_descendant(G);
    
    test_edge_exists(G);

    cout << "Testing completed" << endl;

    delete G;

    return 0;
}
