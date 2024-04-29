#include <fstream>
#include <sstream>
#include "graph.cpp"
#include <sstream>

// TODO: Get all other test cases running and uncommented.
Graph<string, string>* generate_graph(string fname){
    string line;
    ifstream infile(fname);
    vector<string> keys = {};
    vector<string> data = {};
    vector<vector<string>> adjs = {};
    if(infile.is_open()){
        while(getline(infile, line)){
            unsigned long delim = line.find(":");
            string key = line.substr(0, delim);
            string adj = line.substr(delim+1);

            keys.push_back(key);
            data.push_back(key + " data");
            delim = adj.find(",");
            vector<string> adj_lst = {};
            while(delim < adj.length()){
                adj_lst.push_back(adj.substr(0, delim));
                adj = adj.substr(delim+1);
                delim = adj.find(",");
            }
            adj_lst.push_back(adj);
            adjs.push_back(adj_lst);
        }
    }
    Graph<string,string>* G = new Graph<string, string>(keys, data, adjs);
    return G;
}

Graph<int, int>* generate_graph_int(string fname){
    string line;
    ifstream infile(fname);
    vector<int> keys = {};
    vector<int> data = {};
    vector<vector<int>> adjs = {};
    stringstream ss;
    if(infile.is_open()){
        while(getline(infile, line)){
            unsigned long delim = line.find(":");
            ss<<line.substr(0, delim);
            int key;
            ss >> key;
            ss.clear();
            ss.str("");
            string adj = line.substr(delim+1);
        

            keys.push_back(key);
            data.push_back(key + 100); //just a random data
            delim = adj.find(",");
            vector<int> adj_lst = {};
            int lastAdj;
            while(delim < adj.length()){
                int convertedAdj;
                ss<<adj.substr(0, delim);
                ss>>convertedAdj;
                adj_lst.push_back(convertedAdj);
                ss.clear();
                ss.str("");
                adj = adj.substr(delim+1);
                delim = adj.find(",");
            }
            ss<<adj;
            ss>>lastAdj;
            adj_lst.push_back(lastAdj);
            ss.clear();
            ss.str("");
            adjs.push_back(adj_lst);
        }
    }
    Graph<int,int>* G_int = new Graph<int, int>(keys, data, adjs);
    return G_int;
}

void test_get_int(Graph<int,int>* G) {
    //check graph with int type
    try {
        if(G->get(1)==nullptr || G->get(1)->data != 101) {
            cout << "Incorrect result getting vertex \"1\"" <<endl;
        }
        if(G->get(6) != nullptr) {
            cout << "Incorrect result getting non-existant vertex \"6\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }
}

void test_get(Graph<string,string>* G) {
    try {
        if(G->get("S")==nullptr || G->get("S")->data != "S data") {
            cout << "Incorrect result getting vertex \"s\"" << endl;
        }
        if(G->get("a") != nullptr) {
            cout << "Incorrect result getting non-existant vertex \"a\"" << endl;
        }
    } catch(exception& e) {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }
}

 void test_bfs(Graph<string,string>* G) {
    try {
        G->bfs("T");
        string vertices[8] = {"V", "R", "S", "W", "T", "X", "U", "Y"};
        int distances[8] = {3,2,1,1,0,2,1,2};
        for(int i = 0; i < 8; i++){
            if(G->get(vertices[i])==nullptr || G->get(vertices[i])->distance!=distances[i]) {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i] << " from source vertex \"t\"" << endl;
            }
        }
    } catch(exception& e) {
        cerr << "Error testing bfs : " << e.what() << endl;
    }
 }

void test_print_path(Graph<string,string>* G) {
    try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
       G->print_path("T", "V");
        cout.rdbuf(prevbuf);
        if(buffer.str()!="T -> S -> R -> V") {
            cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: T -> S -> R -> V but got : " << buffer.str() << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}

void test_print_path_int(Graph<int,int>* G) {
    try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path(1, 4);
        cout.rdbuf(prevbuf);
        if(buffer.str()!="1 -> 2 -> 4") {
            cout << "Incorrect path from vertex \"1\" to vertex \"4\". Expected: 1 -> 2 -> 4 but got : " << buffer.str() << endl;
        }
        buffer.clear();
        buffer.str("");
        prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path(2, 3);
        cout.rdbuf(prevbuf);
        if(buffer.str()!="2 -> 3") {
            cout << "Incorrect path from vertex \"2\" to vertex \"3\". Expected: 2 -> 3 but got : " << buffer.str() << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}

void test_reachable_int(Graph<int, int> *G)
{
    try
    {
        if (!G->reachable(2, 4))
        {
            cout << "Incorrectly identified adjacent vertex \"2\" as unreachable from \"4\"" << endl;
        }
        if (!G->reachable(1, 4))
        {
            cout << "Incorrectly identified \"1\" as unreachable from \"4\"" << endl;
        }
        if (G->reachable(2, 6))
        {
            cout << "Incorrectly identified non-existant vetex \"6\" as reachable from \"2\"" << endl;
        }
        if (G->reachable(3, 5))
        {
            cout << "Incorrectly identified nonconnected vetex \"5\" as reachable from \"3\"" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing reachable : " << e.what() << endl;
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


void test_bfs_tree(Graph<string,string>* G) {
    try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if(buffer.str() != "T\nS U W\nR Y X\nV") {
            cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n" << buffer.str() << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }

}

void test_bfs_tree_int(Graph<int,int>* G) {
    try {
        stringstream buffer;
        streambuf* prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree(1);
        cout.rdbuf(prevbuf);
        if(buffer.str() != "1\n2\n3 4") {
            cout << "Incorrect bfs tree. Expected : 1\n2\n3 4 \nbut got :\n" << buffer.str() << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }
}



void test_edge_class(Graph<string,string>* G) {
    try {
        string e_class =  G->edge_class("R", "V"); // tree edge
        if(e_class != "tree edge") {
            cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        }
        e_class = G->edge_class("X", "U"); // back edge
        if(e_class != "back edge") {
            cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
        }
        e_class =  G->edge_class("R", "U"); // no edge
        if(e_class != "no edge") {
            cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "W"); // forward edge
        if(e_class != "forward edge") {
            cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "S"); // cross edge
        if(e_class != "cross edge") {
            cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing edge class : " << e.what() << endl;
    }

}

void test_edge_class_int(Graph<int,int>* G) {
    try {
        string e_class =  G->edge_class(1, 2); // tree edge
        if(e_class != "tree edge") {
            cout << "Misidentified tree edge (\"1\", \"2\") as : " << e_class << endl;
        }
        e_class = G->edge_class(3, 2); // back edge
        if(e_class != "back edge") {
            cout << "Misidentified back edge (\"3\", \"2\") as : " << e_class << endl;
        }
        e_class = G->edge_class(2, 4); // forward edge
        if(e_class != "forward edge") {
            cout << "Misidentified forward edge (\"2\", \"4\") as : " << e_class << endl;
        }
    } catch(exception& e) {
        cerr << "Error testing edge class : " << e.what() << endl;
    }

}

int main()
{
    Graph<string, string> *G = generate_graph("graph_description.txt");
    Graph<int, int>* G_int = generate_graph_int("graph_description_unreachable_int.txt");
    test_get_int(G_int);
    test_get(G);
    test_reachable_int(G_int);  
    test_reachable(G);
    test_bfs(G);
    test_print_path_int(G_int);
    test_print_path(G);
    // test_edge_class(G);
    // test_edge_class_int(G_int);
    test_bfs_tree(G);
    test_bfs_tree_int(G_int);

    cout << "Testing completed" << endl;

    delete G;

    return 0;
}
