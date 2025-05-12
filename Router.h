#ifndef ROUTER_H
#define ROUTER_H
#include "PriorityQueuee.h"
#include "RoutingTable.h"
#include "Message.h"
#include "SplayTree.h"
template <class incoming0 = Message, class outgoing0 = Message>
struct Router{
    const long long int ID;
    const String name;
    PQ<incoming0> incoming_Queue;
    Queue<outgoing0> outgoing_Queue;
    RoutT routing_table;
    STree<Machine> machine_tree; 
    Router(const String& namei = NULLstring):name(namei), ID(++global_ID_declare), incoming_Queue(), outgoing_Queue(), routing_table(), machine_tree(){}
    Router():name("Default"), ID(NULLint){}
    bool receive_message(incoming0& newmessage){
        if(!incoming_Queue.Enqueue(newmessage))return false;
        return outgoing_Queue.Enqueue(incoming_Queue.Dequeue());
    }
    bool receive_message(incoming0* newmessage){
        if(!incoming_Queue.Enqueue((*newmessage)))return false;
        delete newmessage;
        return outgoing_Queue.Enqueue(incoming_Queue.Dequeue());
    }
    bool receive_message(String src, String dest = NULLstring, String pl, short int p = NULLint){
        if(!incoming_Queue.Enqueue(Message(src, dest, pl, p)))return false;
        return outgoing_Queue.Enqueue(incoming_Queue.Dequeue());
    }
    outgoing0& send_message(outgoing0& newmessage){
        return outgoing_Queue.Dequeue();
    }
    bool add_machines_from_all_connections() {
        int router_row = -1;

        // Find router's row in all_connections
        for (int i = 0; i < all_connections.rows; ++i) {
            if (all_connections.get(i, 0) == name) {
                router_row = i;
                break;
            }
        }
        if (router_row == -1) return false;

        // Loop through all columns to find connected machines
        for (int j = 1; j < all_connections.columns; ++j) {
            String target = all_connections.get(0, j);
            if (target[0] == 'M') {
                String weight_str = all_connections.get(router_row, j);
                if (weight_str != "?" && weight_str != " ?" && weight_str != "") {
                    int weight = stringToInt(weight_str);
                    Machine m(target, weight);
                    machine_tree.insert(m);
                }
            }
        }
        return true;
    }
    bool process_outgoing_queue(Graph<Router>& graph) {
        while (!outgoing_Queue.isEmpty()) {
            Message msg = outgoing_Queue.Dequeue();

            // Get destination machine name
            String destination = msg.destination_address;

            // Decide the next router using routing table
            String next_router = routing_table_find_next(destination);
            if (next_router == NULLstring) {
                if (debug) cout << "No route found for message to " << destination << endl;
                continue;
            }

            msg(msg.source_address); // update path

            // Try to forward to a machine connected to this router
            if (machine_tree.search(destination)) {
                Machine* m_ptr = machine_tree.get_node(destination);
                m_ptr->recieve_message(msg);
                if (debug) cout << "Delivered to machine " << destination << endl;
                continue;
            }

            // Otherwise, send to the next router
            for (int i = 0; i <= graph.nodes; i++) {
                if (graph.nodes_array->get(i, 0).name == next_router) {
                    Router& next_r = graph.nodes_array->get(i, 0);
                    next_r.receive_message(msg);
                    if (debug) cout << "Forwarded to router " << next_router << endl;
                    break;
                }
            }
        }
        return true;
    }
    String routing_table_find_next(const String& dest) {
        if (use_splaytree()) {
            for (int d = 0; d <= global_ID_declare + 1; d++) {
                if (routing_table.tree[d].destination == dest) {
                    return routing_table.tree[d].next_router;
                }
            }
        } else {
            for (int d = 0; d <= global_ID_declare + 1; d++) {
                if (routing_table.tabular[d].destination == dest) {
                    return routing_table.tabular[d].next_router;
                }
            }
        }
        return NULLstring;
    }
    bool build_routing_table_from_graph(Graph<Router>& graph, int self_index) {
        int dist[100];
        bool visited[100];
        int prev[100];

        for (int i = 0; i < graph.nodes; i++) {
            dist[i] = FULLint;
            visited[i] = false;
            prev[i] = -1;
        }

        dist[self_index] = 0;

        for (int count = 0; count < graph.nodes; count++) {
            int u = -1;
            int min_dist = FULLint;
            for (int i = 0; i < graph.nodes; i++) {
                if (!visited[i] && dist[i] < min_dist) {
                    min_dist = dist[i];
                    u = i;
                }
            }
            if (u == -1) break;
            visited[u] = true;

            for (int v = 0; v < graph.nodes; v++) {
                int weight = LANS.get(u, v);
                if (weight > 0 && !visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                }
            }
        }

        // Add entries to routing table
        for (int dest = 0; dest < graph.nodes; dest++) {
            if (dest == self_index || dist[dest] == FULLint) continue;

            // Find next router on path
            int hop = dest;
            while (prev[hop] != self_index && prev[hop] != -1) {
                hop = prev[hop];
            }

            String next_router = graph.nodes_array->get(hop, 0).name;
            String destination = graph.nodes_array->get(dest, 0).name;
            routing_table.add(destination, next_router);
        }
        return true;
    }

    ~Router(){
        while(!incoming_Queue.isEmpty()){
            incoming_Queue.Dequeue();
        }
        while(!outgoing_Queue.isEmpty()){
            outgoing_Queue.Dequeue();
        }
        delete name;
        delete incoming_Queue;
        delete outgoing_Queue;
    }
    bool add_machine(const String& namei = NULLstring){
        return machine_tree.insert(Machine(namei,));
    }
};
#endif
//CLI commands
    // take all the data in the fucking commas as input but do parse the whole line and the way i have shown, extract data from it
    // send msg "FILE_NAME.txt"                         //1 type // it will give file name
    // send msgs "FILE_NAME.txt"                        //1 type // it will give file name
    // change RT //4 types:
        // change RT "ROUTER_NAME" add "MACHINE_NAME","ROUTER_NAME"          // gives a name of machine and router & router name
        // change RT "ROUTER_NAME" remove "MACHINE_NAME","ROUTER_NAME"       // gives a name of machine and router & router name
        // change RT "ROUTER_NAME" add "FILE_NAME.csv"                      // gives file name & router name
        // change RT "ROUTER_NAME" remove "FILE_NAME.csv"                   // gives file name & router name
    // print path // 3 types:
        //  has a " to " in between
            // print path "MACHINE_NAME" to "MACHINE_NAME"                  // gives a name of machine and another machine
            // print path "MACHINE_NAME" to "*"                             // gives a name of machine and any other machine
            // print path "*" to "MACHINE_NAME"                             // gives a name of machine and any other machine
    // change egde // implement this in graph.h
        // 4 types:
            // change egde "FILE_NAME.csv"                                  // gives file name
            // change egde "ROUTER_NAME","ROUTER_NAME","WEIGHT"             // gives a name of router and router and weight
            // change egde "MACHINE_NAME","ROUTER_NAME","WEIGHT"            // gives a name of router and router and weight
            // change egde "ROUTER_NAME","MACHINE_NAME","WEIGHT"            // gives a name of router and router and weight
    //add a menu in this whole function