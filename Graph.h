#ifndef GRAPH_H
#define GRAPH_H
#include "D2LL.h"

template <class D_Grphi4 = Router, class RT_type_connects = long long int>
struct Graph{
private:
    bool newGraph;
public:
    GraphNode<D_Grphi4>* top;
    D2LL<RT_type_connects> LANS;
    long long int nodes;
    Graph():top(NULLpointer){
        nodes=-1; newGraph =true;
    }
    bool make_graph(){
        
    }
    long long int calculate_routers(){
        // read from router.csv and return the number of routers
    }
    //make the whole graph of routers, join them,then make another csv which has all the IDs of the routers, and weights and -1 instead of ?
    void make_djikstra(){
        LANS.initialise((2*calculate_routers()), 3);

    }
    //make a whole array for djikstra
    // pass that fucking matrix to every machine so it makes its all_connection
    // pass that to every fucking router
    // use the ID's for tracking maybe
    bool add_node(){
        if(!top){
            D_Grphi4* datai = new D_Grphi4();
            top = new GraphNode<D_Grphi4>();
            nodes++;
            return true;
        }
        else{

        }
        return false;
    }
    bool delete_node(){}
    ~Graph(){
        finish_graph();
        delete all_connections;
        (!top)? return : if(debug)cout<<"Top node isnt deleted still"<<endl;
        delete top;
    }
    void finish_graph(){}
    // GraphNode<D_Grphi4>& operator[](long long int IDi){
    //     static GraphNode<D_Grphi4> NullNode7;
    //     if((IDi < 0)||(IDi > global_ID_declare+1)) return NullNode7;
        

    // }
};


#endif