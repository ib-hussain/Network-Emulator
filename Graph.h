#ifndef GRAPH_H
#define GRAPH_H
#include "D2LL.h"

template <class D_Grphi4 = Router>
struct Graph{
private:
    bool newGraph;
public:
    D2LL<D_Grphi4>* nodes_array;
    long long int nodes;
    Graph():top(NULLpointer){
        nodes = -1;
        newGraph = true;
    }
    // Calculate number of routers from CSV file
    long long int calculate_routers(const string& filename = "router.csv") {
        ifstream file(filename);
        if (!file.is_open()) {
            if(debug)cout << "Error: Cannot open file " << filename << "\n";
            return -1;
        }
        string line;
        long long int count = 0;
        bool skip_header = true;
        if (skip_header && getline(file, line)){}
        while (getline(file, line)) {
            if (!line.empty()) ++count;
        }
        file.close();
        return count;
    }

    // Make the whole graph of routers and create a matrix for Dijkstra's algorithm
    void make_djikstra_matrix() {
        long long int num_routers = calculate_routers(); // e.g., 5
        if(num_routers <= 0) return;
        
        LANS.initialise(num_routers, num_routers);
        ifstream file("router.csv");
        if (!file.is_open()) {
            if(debug) cout << "Error: Cannot open file router.csv\n";
            return;
        }
        string line;
        bool skip_header = true;
        if (skip_header && getline(file, line)) {} // skip header
        
        long long int row = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            getline(ss, token, ','); // Skip the router label in first column (e.g., R1)
            long long int col = 0;
            while (getline(ss, token, ',')) {
                if (token == "?" || token == " ?" || token.empty()) {
                    LANS.get(row, col) = -1;
                } else {
                    LANS.get(row, col) = stoi(token);
                }
                ++col;
            }
            ++row;
        }
        file.close();
    }
    bool make_graph(){}
    bool add_node(D_Grphi4& router_data) {
    
    }
    // Delete a node from the graph
    bool delete_node(long long int IDi) {
        if (newGraph || !nodes_array) return false;
        
        return false;
    }
    ~Graph() {
        finish_graph();
    }
    void finish_graph() {
        if (nodes_array) {
            for (int i = 0; i < nodes; i++) {
                delete nodes_array[i];
            }
            delete[] nodes_array;
            nodes_array = nullptr;
        }
        top = nullptr;
        nodes = 0;
        newGraph = true;
    }
    GraphNode<D_Grphi4>& operator[](long long int IDi) {
        static GraphNode<D_Grphi4> NullNode7;
        if ((IDi < 0) || (IDi > global_ID_declare + 1)) return NullNode7;
        
        
        return NullNode7;
    }
    
    
};
#endif