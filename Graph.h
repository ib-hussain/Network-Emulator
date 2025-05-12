#ifndef GRAPH_H
#define GRAPH_H
#include "D2LL.h"

template <class D_Grphi4 = Router>
struct Graph{
public:
    D2LL<D_Grphi4> *nodes_array;
    long long int nodes;
    Graph() : top(NULLpointer)
    {
        nodes = -1;
    }
    // Calculate number of routers from CSV file
    long long int calculate_routers(const string &filename = "router.csv")
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            if (debug)
                cout << "Error: Cannot open file " << filename << "\n";
            return -1;
        }
        string line;
        long long int count = 0;
        bool skip_header = true;
        if (skip_header && getline(file, line))
        {
        }
        while (getline(file, line))
        {
            if (!line.empty())
                ++count;
        }
        file.close();
        return count;
    }

    // Make the whole graph of routers and create a matrix for Dijkstra's algorithm
    void make_djikstra_matrix(){
        long long int num_routers = calculate_routers(); // e.g., 5
        if (num_routers <= 0)
            return;

        LANS.initialise(num_routers, num_routers);
        ifstream file("router.csv");
        if (!file.is_open())
        {
            if (debug)
                cout << "Error: Cannot open file router.csv\n";
            return;
        }
        string line;
        bool skip_header = true;
        if (skip_header && getline(file, line))
        {
        } // skip header
        long long int row = 0;
        while (getline(file, line))
        {
            stringstream ss(line);
            string token;
            getline(ss, token, ','); // Skip the router label in first column (e.g., R1)
            long long int col = 0;
            while (getline(ss, token, ','))
            {
                if (token == "?" || token == " ?" || token.empty())
                {
                    LANS.get(row, col) = -1;
                }
                else{
                    LANS.get(row, col) = stoi(token);
                }
                ++col;
            }
            ++row;
        }
        file.close();
    }
    bool change_edge(const String& router1, const String& router2, int new_weight) {
        int index1 = -1, index2 = -1;
        for (int i = 0; i < all_connections.rows; ++i) {
            if (all_connections.get(i, 0) == router1) {
                index1 = i;
            }
            if (all_connections.get(0, i) == router2) {
                index2 = i;
            }
        }
        if (index1 == -1 || index2 == -1) {
            if (debug) cout << "Router name(s) not found.\n";
            return false;
        }
        // Update both LANS and all_connections
        LANS.get(index1, index2) = new_weight;
        LANS.get(index2, index1) = new_weight;
        all_connections.get(index1, index2) = to_string(new_weight);
        all_connections.get(index2, index1) = to_string(new_weight);
        return true;
    }
    bool make_graph() {
        long long int num_routers = calculate_routers();
        if (num_routers <= 0) return false;

        LANS.initialise(num_routers, num_routers);
        ifstream file("router.csv");
        if (!file.is_open()) return false;
        nodes_array = new D2LL<D_Grphi4>();
        string line;
        getline(file, line); // skip header

        //              router nodes
        long long int index = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            getline(ss, token, ','); //    router name  R6 
            Router new_router(token);
            GraphNode<Router>* new_node = new GraphNode<Router>(new_router);
            all_connections.get(index, 0) = token;
            all_connections.get(index, 1) = token;
            nodes_array->get(index, 0) = new_router;
            index++;
        }
        

        file.clear();
        file.seekg(0);
        getline(file, line); // skip header again

        long long int row = 0;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            getline(ss, token, ','); // skip router name

            long long int col = 0;
            while (getline(ss, token, ',')) {
                if (token == "?" || token.empty()) {
                    LANS.get(row, col) = -1;
                } else {
                    LANS.get(row, col) = stoi(token);
                }
                ++col;
            }
            ++row;
        }

        file.close();
        nodes = num_routers;
        // Let each router add its machines
        for (int i = 0; i < nodes; i++) {
            Router& router = nodes_array->get(i, 0);
            router.add_machines_from_all_connections();
        }
    //     for (int i = 0; i < nodes; ++i) {
    //     Router& src_router = nodes_array->get(i, 0);
    //     GraphNode<Router>* src_node = new GraphNode<Router>(src_router);

    //     for (int j = 0; j < nodes; ++j) {
    //         int weight = LANS.get(i, j);
    //         if (weight > 0) {
    //             Router& dest_router = nodes_array->get(j, 0);
    //             GraphNode<Router>* dest_node = new GraphNode<Router>(dest_router);
    //             src_node->pointers.insert(dest_node, weight);
    //         }
    //     }
    // }
        return true;
    }
    bool add_node(D_Grphi4& router_data) {
        if (!nodes_array) nodes_array = new D2LL<D_Grphi4>();
        nodes_array->get(++nodes, 0) = router_data;
        return true;
    }
    bool delete_node(long long int IDi) {
        if (!nodes_array) return false;
        for (int i = 0; i <= nodes; i++) {
            if (nodes_array->get(i, 0).ID == IDi) {
                nodes_array->get(i, 0) = NULLpointer;
                return true;
            }
        }
        return false;
    }
    ~Graph()
    {
        finish_graph();
    }
    void finish_graph() {
        if (nodes_array) {
            delete nodes_array;
            nodes_array = NULLpointer;
        }
        nodes = -1;
    }
    GraphNode<D_Grphi4>& operator[](long long int IDi) {
        static GraphNode<D_Grphi4> NullNode7;
        for (int i = 0; i <= nodes; i++) {
            if (nodes_array->get(i, 0).ID == IDi) {
                return *(new GraphNode<D_Grphi4>(nodes_array->get(i, 0)));
            }
        }
        return NullNode7;
    }
};
#endif