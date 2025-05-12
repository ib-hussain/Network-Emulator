#ifndef GRAPH_H
#define GRAPH_H
#include "D2LL.h"
// D2LL<RT_type_connects> LANS;
template <class D_Grphi4 = Router>
struct Graph{
private:
    bool newGraph;
public:
    GraphNode<D_Grphi4>* top;
    long long int nodes;
    Graph():top(NULLpointer){
        nodes=-1; newGraph =true;
    }
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
        // read from router.csv and return the number of routers
    }
    //make the whole graph of routers, join them,then make another csv which has all the IDs of the routers, and weights and -1 instead of ?
    void make_djikstra_matrix() {
    long long int num_routers = calculate_routers(); // e.g., 5
    LANS.initialise(num_routers, num_routers);
        ifstream file("router.csv");
        if (!file.is_open()) {
            if(debug) cout << "Error: Cannot open file\n";
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
    bool make_graph(){
        


        newGraph = false;
        return true;
    }
    //make a whole array for djikstra
    // pass that fucking matrix to every machine so it makes its all_connection
    // pass that to every fucking router
    // use the ID's for tracking maybe
    bool add_node(){
        
    }
    bool delete_node(long long int IDi){}
    ~Graph(){
        finish_graph();
        delete all_connections;
        (!top)? return : if(debug)cout<<"Top node isnt deleted still"<<endl;
        delete top;
    }
    void finish_graph(){}
    GraphNode<D_Grphi4>& operator[](long long int IDi){
        static GraphNode<D_Grphi4> NullNode7;
        if((IDi < 0)||(IDi > global_ID_declare+1)) return NullNode7;
        

    }
};


#endif