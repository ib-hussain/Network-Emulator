#include "Graph.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//CLI commands
    // take all the data in the commas as input
    // but do parse the whole line and the way i have shown, extract data from it

    
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


int find_substring(const string& str, const string& target, size_t start = 0)
 {
    for (size_t i = start; i <= str.length() - target.length(); ++i) 
    // this loop will run till the end of the string
    // and check if the target string is present in the string
    {
        if (str.substr(i, target.length()) == target) 
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Helper function to extract quoted substrings from input
void extraction(const string& str, string results[], int& count) 
{
    count = 0;
    size_t pos = 0;

    while (true) {
        int start = find_substring(str, "\"", pos);
        if (start == -1) break;
        int end = find_substring(str, "\"", start + 1);
        if (end == -1) break;

        results[count++] = str.substr(start + 1, end - start - 1);
        pos = end + 1;
    }
}

// Function to display the menu
void show_menu() {
    cout<<"_________________________ Network Emulator Commands_________________________\n";
    cout<<"1. change edge \"file.csv\"  OR  \"Router1\",\"Router2\",\"Weight\"\n";
    cout<<"2. send msg \"file.txt\"\n";
    cout<<"3. send msgs \"file.txt\"\n";
    cout<<"4. change RT add/remove \"file.csv\"  OR  \"Machine\",\"Router\"\n";
    cout<<"5. print path \"Machine1\" to \"Machine2\"\n";
    cout<<"6. exit\n";
    cout<<"_____________________________________________________________________________\n";
}

void start_engine() 

{
    string command;

    // Step 1: Force "change edge" first
    while (true) 
    {
        cout<<"\nBefore anything else, you MUST enter a 'change edge' command.\n> ";
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
                    cout<<"Changing edges using file: "<<tokens[0]<<cout<<"\n";

                    // Graph::ChangeEdgeFromFile(tokens[0]);
                } 
                
                else if (count >= 3)
                 {
                   
                    cout<<"Changing edge between "<<tokens[0]<<" and "<<tokens[1]<<" with weight "<<tokens[2]<<cout<<"\n";
                    // Graph::ChangeEdge(tokens[0], tokens[1], stoi(tokens[2]));
                }
                
                else 
                
                {
                    cout<<"Invalid parameters for change edge.\n";


                    continue;
                }
                break;
            }
        } else 
        

            cout<<"You must enter a valid 'change edge' command first.\n";
        }
    }

    // Step 2: Normal Command Flow
    show_menu();

    while (true)
    
    {
        cout<<"\nEnter command:\n> ";
        getline(cin, command);

        if (find_substring(command, "send msg") == 0) 
        {
    string tokens[10];


    int count = 0;
    extraction(command, tokens, count);
    if (count > 0) {
        cout << "Sending message from file: "<<tokens[0]<<"\n";
        // Placeholder for Send_Message function
        // Send_Message(tokens[0]);
    }
} else if (find_substring(command, "send msgs") == 0) 
{
    string tokens[10];
    int count = 0;

    extraction(command, tokens, count);

    if (count > 0)
     {
        cout << "Sending multiple messages from file: "<<tokens[0]<<"\n";
        // Placeholder for Send_Message_S function
        // Send_Message_S(tokens[0]);
    }
}

else if (find_substring(command, "change RT") == 0) 

{
    string tokens[10];
    int count = 0;
    extraction(command, tokens, count);
    if (count == 0) continue;

    if (find_substring(command, "add") != -1) 
    {
        if (find_substring(tokens[0], ".csv") != -1) 

        {
            cout << "Adding RT entries from file: "<<tokens[0]<<"\n";
            // Placeholder for ChangeRT_AddFromFile function
            // ChangeRT_AddFromFile(tokens[0]);
        } else if (count >= 2) 
        
        {
            cout << "Adding Machine: " << tokens[0]<<" to Router: "<<tokens[1]<<"\n";

            // Placeholder for ChangeRT_AddMachine function
            // ChangeRT_AddMachine(tokens[0], tokens[1]);
        }

    } 
    
    else if (find_substring(command, "remove") != -1) 
    {
        if (find_substring(tokens[0], ".csv") != -1)
         {
            cout << "Removing RT entries from file: "<<tokens[0]<<"\n";

            // Placeholder for ChangeRT_RemoveFromFile function
            // ChangeRT_RemoveFromFile(tokens[0])
        } 
        
        else if (count >= 2)
         {
            cout << "Removing Machine: " << tokens[0]<<" from Router: " <<tokens[1]<<"\n";


            // Placeholder for ChangeRT_RemoveMachine function
            // ChangeRT_RemoveMachine(tokens[0], tokens[1]);
        }
    }
} else if (find_substring(command, "print path") == 0)
 {
    string tokens[10];

    int count = 0;
    
    extraction(command, tokens, count);

    if (count >= 2) 
    {
        cout << "Printing path from " <<tokens[0]<<"to "<<tokens[1]<< "\n";

        // Placeholder for Print_Path function
        // Print_Path(tokens[0], tokens[1]);
    } 
    
    else 

    {
        cout << "Invalid format. Usage: print path \"MachineA\" to \"MachineB\"\n";
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


            cout <<"Changing edges using file: " <<tokens[0]<<"\n";

            // Placeholder for Graph::ChangeEdgeFromFile function
            // Graph::ChangeEdgeFromFile(tokens[0]);
        } 
        
        else if (count >= 3)
        
        {
            cout<<"Changing edge between " <<tokens[0] <<" and " <<tokens[1]<<" with weight " << tokens[2]<< "\n";
            // Placeholder for Graph::ChangeEdge function
            // Graph::ChangeEdge(tokens[0], tokens[1], stoi(tokens[2]));
        } 
        
        else {

            cout<<"Invalid parameters for change edge.\n";
        }
    }
}

else if (find_substring(command, "exit") == 0) 
{
    cout << "Exiting the program.\n";
    break;
} else
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
