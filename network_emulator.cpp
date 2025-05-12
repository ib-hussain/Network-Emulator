#include "Graph.h"
// all files are included on backend
// CLI commands
//  take all the data in the commas as input
//  but do parse the whole line and the way i have shown, extract data from it

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
// add a menu in this whole function
Graph<Router> graph;
bool graph_ready = false;

int find_substring(const string &str, const string &target, size_t start = 0)
{
    for (size_t i = start; i <= str.length() - target.length(); ++i)
    {
        if (str.substr(i, target.length()) == target)
            return static_cast<int>(i);
    }
    return -1;
}

void extraction(const string &str, string results[], int &count)
{
    count = 0;
    size_t pos = 0;
    while (true)
    {
        int start = find_substring(str, "\"", pos);
        if (start == -1)
            break;
        int end = find_substring(str, "\"", start + 1);
        if (end == -1)
            break;
        results[count++] = str.substr(start + 1, end - start - 1);
        pos = end + 1;
    }
}

void show_menu()
{
    cout << "\n_________________________ Network Emulator Commands _________________________\n";
    cout << "1. change edge \"FILE_NAME.csv\" OR \"Router1\",\"Router2\",\"Weight\"\n";
    cout << "2. send msg \"FILE_NAME.txt\"\n";
    cout << "3. send msgs \"FILE_NAME.txt\"\n";
    cout << "4. change RT add/remove \"FILE_NAME.csv\" OR \"Machine\",\"Router\"\n";
    cout << "5. print path \"Machine1\" to \"Machine2\"\n";
    cout << "6. exit\n";
    cout << "_____________________________________________________________________________\n";
}

void build_routing_system()
{
    graph.make_graph();
    for (int i = 0; i < graph.nodes; i++)
    {
        Router &r = graph.nodes_array->get(i, 0);
        r.add_machines_from_all_connections();
        r.build_routing_table_from_graph(graph, i);
    }
    graph_ready = true;
}

void start_engine()
{
    string command;
    while (true)
    {
        cout << "\nBefore anything else, you MUST enter a 'change edge' command.\n> ";
        getline(cin, command);

        if (find_substring(command, "change edge") == 0)
        {
            string tokens[10];
            int count = 0;
            extraction(command, tokens, count);

            if (count > 0)
            {
                if (find_substring(tokens[0], ".csv") != -1)
                {
                    all_connections.read_whole_csv(tokens[0]);
                    build_routing_system();
                }
                else if (count >= 3)
                {
                    graph.change_edge(tokens[0], tokens[1], stringToInt(tokens[2]));
                    build_routing_system();
                }
                break;
            }
        }
        else
        {
            cout << "You must enter a valid 'change edge' command first.\n";
        }
    }

    show_menu();

    while (true)
    {
        cout << "\nEnter command:\n> ";
        getline(cin, command);

        if (find_substring(command, "send msg") == 0)
        {
            string tokens[10];
            int count = 0;
            extraction(command, tokens, count);
            if (count > 0)
            {
                Message *msg = Send_Message(tokens[0]);
                if (!msg)
                    continue;
                for (int i = 0; i < graph.nodes; i++)
                {
                    Router &r = graph.nodes_array->get(i, 0);
                    if (r.machine_tree.search(msg->source_address))
                    {
                        r.machine_tree.get_node(msg->source_address)->outgoing.Enqueue(*msg);
                        r.process_outgoing_queue(graph);
                        break;
                    }
                }
            }
        }
        else if (find_substring(command, "send msgs") == 0)
        {
            string tokens[10];
            int count = 0;
            extraction(command, tokens, count);
            if (count > 0)
            {
                Message *msg = Send_Message_S(tokens[0]);
                if (!msg)
                    continue;
                for (int i = 0; i < graph.nodes; i++)
                {
                    Router &r = graph.nodes_array->get(i, 0);
                    if (r.machine_tree.search(msg->source_address))
                    {
                        r.machine_tree.get_node(msg->source_address)->outgoing.Enqueue(*msg);
                        r.process_outgoing_queue(graph);
                        break;
                    }
                }
            }
        }
        else if (find_substring(command, "change RT") == 0)
        {
            string tokens[10];
            int count = 0;
            extraction(command, tokens, count);
            for (int i = 0; i < graph.nodes; i++)
            {
                Router &r = graph.nodes_array->get(i, 0);
                if (r.name == tokens[0])
                {
                    if (find_substring(command, "add") != -1)
                    {
                        if (count == 2)
                            r.routing_table.add(tokens[1], tokens[2]);
                        else
                            r.routing_table.add_csv(tokens[1]);
                    }
                    else if (find_substring(command, "remove") != -1)
                    {
                        if (count == 2)
                            r.routing_table.remove(tokens[1], tokens[2]);
                        else
                            r.routing_table.remove_csv(tokens[1]);
                    }
                }
            }
        }
        else if (find_substring(command, "print path") == 0)
        {
            string tokens[10];
            int count = 0;
            extraction(command, tokens, count);
            if (count >= 2)
            {
                String path = Print_Path(tokens[0], tokens[1]);
                cout << "Path: " << path << "\n";
            }
            else
            {
                cout << "Usage: print path \"MachineA\" to \"MachineB\"\n";
            }
        }
        else if (find_substring(command, "change edge") == 0)
        {
            string tokens[10];
            int count = 0;
            extraction(command, tokens, count);
            if (count > 0)
            {
                if (find_substring(tokens[0], ".csv") != -1)
                {
                    all_connections.read_whole_csv(tokens[0]);
                    build_routing_system();
                }
                else if (count >= 3)
                {
                    graph.change_edge(tokens[0], tokens[1], stringToInt(tokens[2]));
                    build_routing_system();
                }
            }
        }
        else if (find_substring(command, "exit") == 0)
        {
            cout << "Exiting the program.\n";
            break;
        }
        else
        {
            cout << "Invalid command. Please try again.\n";
        }
    }
}

int main()
{
    start_engine();
    return 0;
}