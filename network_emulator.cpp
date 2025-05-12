#include "Graph.h"
//all files are included on backend
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
//also ask user if they want to use splay tree or not
void show_menu() {// these should be 13 conditions here, not just 8
    cout<<"_________________________ Network Emulator Commands_________________________\n";
    cout<<"1. change edge \"FILE_NAME.csv\"  OR  \"Router1\",\"Router2\",\"Weight\"\n";
    cout<<"2. send msg \"FILE_NAME.txt\"\n";
    cout<<"3. send msgs \"FILE_NAME.txt\"\n";
    cout<<"4. change RT add/remove \"FILE_NAME.csv\"  OR  \"Machine\",\"Router\"\n";
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
        Message *&Send_Message(String filename1)
{
    // send msg //command
    // read only one message
    Message *msg = new Message("source", "destination","payload",1);
    ifstream file(filename1);
    if (!file.is_open()) 
    {
        cout<< "Could not open this file: "<<filename1<<endl;
        return NULLpointer;
    }
    String line;
    if (getline(file, line)) 
    {
        // Expected format: ID:PRIORITY:SRC:DEST:"PAYLOAD":"PATH"
        String id, priority, src, dest, payload, path;
        int stage=0;
        String current;
        bool in_quotes=false;

        for (char c : line)
         {
            if (c == ':' && !in_quotes)
             {  
                switch (stage)
                 {
                    case 0: id = current;
                     break;
                    case 1: priority = current;
                     break;
                    case 2: src = current;
                     break;
                    case 3: dest = current; 
                    break;
                    case 4: 
                        payload = current.substr(1, current.length() - 2); 
                        break;
                }
                current.clear();
                stage++;
            }
             else if (c == '"') 
            {
                
            in_quotes = !in_quotes;
            if (stage == 5 && !in_quotes)
            {
             path = current.substr(1, current.length() - 2);
            }

            }
             else 
            {
                current=current+c;
            }
        }

        
        if (stage < 5)
         {
            cerr << "Invalid format" << endl;
            return NULLpointer;
        }
        Message *msg = new Message(src, dest, payload, stringToInt(priority));
        msg->path = path;      
        file.close();
        return msg;
    }

    file.close();
    return NULLpointer;
 
}

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
        Message *Send_Message_S(String filename1)
{
    // send msgs //command
    // read all messages and send them
    ifstream file(filename1);
if (!file.is_open())
 {
    cout<<"could not open this file: " <<filename1<<endl;
    return NULLpointer;
}

Message *first_message=NULLpointer;
String line;
int message_count = 0;

while (getline(file, line))
 {
    String id, priority, src, dest, payload, path;
    int stage = 0;
    String current;
    bool in_quotes = false;

    for (char c : line)
     {
        if (c == ':' && !in_quotes) 
        {
            switch (stage) {
                case 0: id = current; 
                break;
                case 1: priority = current;
                 break;
                case 2: src = current; 
                break;
                case 3: dest = current;
                 break;
                case 4: payload = current.substr(1, current.length() - 2); 
                break;
            }
            current.clear();
            stage++;
        } 
        else if (c == '"') 
        {
            in_quotes = !in_quotes;
            if (stage == 5 && !in_quotes)
             {
                path = current.substr(1, current.length() - 2);
            }
        } 
        else
         {
            current =current+c;
        }
    }

    if (stage < 5) 
    {
        cerr << "Invalid format: " <<line <<endl;
        continue;
    }

    Message *msg = new Message(src, dest, payload, stringToInt(priority));
    msg->path = path;

    if (message_count == 0) 
    {
        first_message = msg;
    }
    message_count++;
}
file.close();
return first_message;

}
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
       String Print_Path(String start, String end)
{
        ifstream file("received_messages.txt");

    if (!file.is_open())
     {
        if(debug)cout << "could not open received messages file " <<endl;
        return NULLstring;
    }

    String line;
    String found_path;
    bool path_found = false;

    while (getline(file, line)) 
    {
        String id, priority, src, dest, payload, path;
        int stage = 0;
        String current;
        bool in_quotes = false;

        for (char c : line)
         {
            if (c == ':' && !in_quotes)
             {
                
                switch (stage)
                 {
                    case 0: id = current; 
                    break;
                    case 1: priority = current; 
                    break;
                    case 2: src = current;
                     break;
                    case 3: dest = current;
                     break;
                    case 4: 
                        payload = current.substr(1, current.length() - 2); 
                        break;
                }
                current.clear();
                stage++;
            } 
            else if (c == '"') 
            {
                
                in_quotes = !in_quotes;
                if (stage == 5 && !in_quotes)
                 {
                    path = current.substr(1, current.length() - 2);
                }
            }
             else 
            {
                current =current+c;
            }
        }
        if (path.find(start)!=String::npos && path.find(end) != String::npos)
         {
            found_path = path;
            path_found = true;
            break;
        }
    }
    file.close();
    if (path_found) 
    {
        ofstream path_file("path.txt");
        if (path_file.is_open())
         {
            path_file << found_path;
            path_file.close();
            return found_path;
        }
        return NULLstring;
    }

    return NULLstring;
}

{
        ifstream file("received_messages.txt");

    if (!file.is_open())
     {
        if(debug)cout << "could not open received messages file " <<endl;
        return NULLstring;
    }

    String line;
    String found_path;
    bool path_found = false;

    while (getline(file, line)) 
    {
        String id, priority, src, dest, payload, path;
        int stage = 0;
        String current;
        bool in_quotes = false;

        for (char c : line)
         {
            if (c == ':' && !in_quotes)
             {
                
                switch (stage)
                 {
                    case 0: id = current; 
                    break;
                    case 1: priority = current; 
                    break;
                    case 2: src = current;
                     break;
                    case 3: dest = current;
                     break;
                    case 4: 
                        payload = current.substr(1, current.length() - 2); 
                        break;
                }
                current.clear();
                stage++;
            } 
            else if (c == '"') 
            {
                
                in_quotes = !in_quotes;
                if (stage == 5 && !in_quotes)
                 {
                    path = current.substr(1, current.length() - 2);
                }
            }
             else 
            {
                current =current+c;
            }
        }
        if (path.find(start)!=String::npos && path.find(end) != String::npos)
         {
            found_path = path;
            path_found = true;
            break;
        }
    }
    file.close();
    if (path_found) 
    {
        ofstream path_file("path.txt");
        if (path_file.is_open())
         {
            path_file << found_path;
            path_file.close();
            return found_path;
        }
        return NULLstring;
    }

    return NULLstring;
}

        // Print_Path(tokens[0], tokens[1]);
        String Print_Path(String start, String end)
{
        ifstream file("received_messages.txt");

    if (!file.is_open())
     {
        if(debug)cout << "could not open received messages file " <<endl;
        return NULLstring;
    }

    String line;
    String found_path;
    bool path_found = false;

    while (getline(file, line)) 
    {
        String id, priority, src, dest, payload, path;
        int stage = 0;
        String current;
        bool in_quotes = false;

        for (char c : line)
         {
            if (c == ':' && !in_quotes)
             {
                
                switch (stage)
                 {
                    case 0: id = current; 
                    break;
                    case 1: priority = current; 
                    break;
                    case 2: src = current;
                     break;
                    case 3: dest = current;
                     break;
                    case 4: 
                        payload = current.substr(1, current.length() - 2); 
                        break;
                }
                current.clear();
                stage++;
            } 
            else if (c == '"') 
            {
                
                in_quotes = !in_quotes;
                if (stage == 5 && !in_quotes)
                 {
                    path = current.substr(1, current.length() - 2);
                }
            }
             else 
            {
                current =current+c;
            }
        }
        if (path.find(start)!=String::npos && path.find(end) != String::npos)
         {
            found_path = path;
            path_found = true;
            break;
        }
    }
    file.close();
    if (path_found) 
    {
        ofstream path_file("path.txt");
        if (path_file.is_open())
         {
            path_file << found_path;
            path_file.close();
            return found_path;
        }
        return NULLstring;
    }

    return NULLstring;
}

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
