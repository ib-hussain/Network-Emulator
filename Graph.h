#ifndef GRAPH_H
#define GRAPH_H
#include "D2LL.h"
// D2LL<RT_type_connects> LANS;

template <class D_Grphi4 = Router>
struct Graph{
private:
    bool newGraph;
    GraphNode<D_Grphi4>** nodes_array; // Array to store pointers to graph nodes
    
public:
    GraphNode<D_Grphi4>* top;
    long long int nodes;
    // Constructor
    Graph():top(NULLpointer){
        nodes = 0;
        newGraph = true;
        nodes_array = nullptr;
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
    // Create the graph structure based on the matrix
    bool make_graph() {
        if (!newGraph) return false; // Graph already made
        
        // First make the Dijkstra matrix
        make_djikstra_matrix();
        
        long long int numNodes = calculate_routers();
        if (numNodes <= 0) return false;
        
        // Create array to store router nodes
        nodes_array = new GraphNode<D_Grphi4>*[numNodes];
        for (int i = 0; i < numNodes; i++) {
            // Create router with name "R" + (i+1)
            string routerName = "R" + to_string(i+1);
            D_Grphi4 router(routerName);
            nodes_array[i] = new GraphNode<D_Grphi4>(router);
        }
        // Set top to the first router
        top = nodes_array[0];
        nodes = numNodes;
        // Connect routers based on matrix
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                int weight = LANS.get(i, j);
                if (weight > 0) {
                    // Add connection from router i to router j with weight
                    // Use the GPtrs structure to add this connection
                    nodes_array[i]->pointers.insert(nodes_array[j], weight);
                }
            }
        }
        newGraph = false;
        return true;
    }
    // Add a node to the graph
    bool add_node(D_Grphi4& router_data) {
        if (newGraph) {
            // If graph is new, make it first
            if (!make_graph()) return false;
        }
        // Create a new router node
        GraphNode<D_Grphi4>* new_node = new GraphNode<D_Grphi4>(router_data);
        // Make it top if there is no top
        if (!top) {
            top = new_node;
            nodes++;
            return true;
        }
        // Otherwise append to nodes_array
        GraphNode<D_Grphi4>** new_array = new GraphNode<D_Grphi4>*[nodes + 1];
        for (int i = 0; i < nodes; i++) {
            new_array[i] = nodes_array[i];
        }
        new_array[nodes] = new_node;
        
        // Delete old array and update
        delete[] nodes_array;
        nodes_array = new_array;
        nodes++;
        
        return true;
    }
    // Delete a node from the graph
    bool delete_node(long long int IDi) {
        if (newGraph || !nodes_array) return false;
        for (int i = 0; i < nodes; i++) {
            if (nodes_array[i]->data.ID == IDi) {
                // Remove connections from other nodes to this node
                for (int j = 0; j < nodes; j++) {
                    if (j != i) {
                        nodes_array[j]->pointers.remove(nodes_array[i]);
                    }
                }
                // Delete the node
                delete nodes_array[i];
                
                // Shift the array
                for (int j = i; j < nodes - 1; j++) {
                    nodes_array[j] = nodes_array[j + 1];
                }
                nodes--;
                // Update top pointer if needed
                if (i == 0 && nodes > 0) {
                    top = nodes_array[0];
                } else if (nodes == 0) {
                    top = nullptr;
                }
                return true;
            }
        }
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
        
        for (int i = 0; i < nodes; i++) {
            if (nodes_array[i]->data.ID == IDi) {
                return *(nodes_array[i]);
            }
        }
        
        return NullNode7;
    }
    GraphNode<D_Grphi4>* find_router(const string& router_name) {
        for (int i = 0; i < nodes; i++) {
            if (nodes_array[i]->data.name == router_name) {
                return nodes_array[i];
            }
        }
        return nullptr;
    }
    bool add_connection(const string& router1, const string& router2, int weight) {// Add connection between routers
        GraphNode<D_Grphi4>* r1 = find_router(router1);
        GraphNode<D_Grphi4>* r2 = find_router(router2);
        if (!r1 || !r2) return false;
        r1->pointers.insert(r2, weight);
        r2->pointers.insert(r1, weight); 
        
        return true;
    }
    // Dijkstra's algorithm implementation
    string find_shortest_path(const string& start_machine, const string& end_machine) {
        // First, find the routers connected to these machines
        GraphNode<D_Grphi4>* start_router = nullptr;
        GraphNode<D_Grphi4>* end_router = nullptr;
        
        // Check connections in all_connections (assumed to be a global variable)
        // This is a simplification - in practice, you'd need to implement machine-to-router mapping
        
        // If we can't find the mapping, return empty string
        if (!start_router || !end_router) {
            return "No path found";
        }
        
        // Create data structures for Dijkstra's algorithm
        bool* visited = new bool[nodes];
        int* distance = new int[nodes];
        int* previous = new int[nodes];
        
        // Initialize
        for (int i = 0; i < nodes; i++) {
            visited[i] = false;
            distance[i] = INT_MAX;
            previous[i] = -1;
        }
        
        // Find indices of start and end routers
        int start_idx = -1, end_idx = -1;
        for (int i = 0; i < nodes; i++) {
            if (nodes_array[i] == start_router) start_idx = i;
            if (nodes_array[i] == end_router) end_idx = i;
        }
        
        if (start_idx == -1 || end_idx == -1) {
            delete[] visited;
            delete[] distance;
            delete[] previous;
            return "No path found";
        }
        
        // Distance to start is 0
        distance[start_idx] = 0;
        
        // Main Dijkstra loop
        for (int count = 0; count < nodes - 1; count++) {
            // Find the vertex with minimum distance
            int min_dist = INT_MAX;
            int min_idx = -1;
            
            for (int i = 0; i < nodes; i++) {
                if (!visited[i] && distance[i] <= min_dist) {
                    min_dist = distance[i];
                    min_idx = i;
                }
            }
            
            if (min_idx == -1) break; // No path
            
            // Mark the vertex as visited
            visited[min_idx] = true;
            
            // Update distances of adjacent vertices
            for (int i = 0; i < nodes; i++) {
                int edge_weight = -1;
                // Check if there's an edge from min_idx to i
                GraphNode<D_Grphi4>* curr_node = nodes_array[min_idx];
                
                // This is where you'd use GPtrs to check connections
                // For simplicity, we'll use LANS matrix directly
                edge_weight = LANS.get(min_idx, i);
                
                if (!visited[i] && edge_weight > 0 && 
                    distance[min_idx] != INT_MAX && 
                    distance[min_idx] + edge_weight < distance[i]) {
                    distance[i] = distance[min_idx] + edge_weight;
                    previous[i] = min_idx;
                }
            }
        }
        
        // Reconstruct path
        string path = "";
        if (distance[end_idx] == INT_MAX) {
            path = "No path found";
        } else {
            vector<int> path_indices;
            for (int at = end_idx; at != -1; at = previous[at]) {
                path_indices.push_back(at);
            }
            
            // Reverse to get start to end
            reverse(path_indices.begin(), path_indices.end());
            
            // Convert to router names
            for (size_t i = 0; i < path_indices.size(); i++) {
                path += nodes_array[path_indices[i]]->data.name;
                if (i < path_indices.size() - 1) {
                    path += " -> ";
                }
            }
        }
        // Clean up
        delete[] visited;
        delete[] distance;
        delete[] previous;
        
        return path;
    }
};
#endif