#ifndef BASELIBRARIESFILE_H
#define BASELIBRARIESFILE_H
// LIBRARIES:
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;

// MACROS:
#define NULLint 0
#define FULLint 32765
#define UNDERint INT_MIN
#define NULLchar '\0'
#define NULLstring ""
#define NULLbool NULL
#define NULLdouble 0.0000
#define NULLfloat 0.0000
#define NULLpointer nullptr

// GLOBAL CONSTANTS/VARIABLES:
const unsigned short int latency_queue_forwarding = 0;
unsigned long long int global_ID_declare = FULLint;
const bool debug = true;

// PRIMARY DATA STRUCTURES
#include "Queue/PriorityQueue.h"
#include "Queue/Queue.h"
#include "Stack/Stack.h"
#include "LinkedList/DoublyCircularLinkedList.h"
#include "LinkedList/DoublyLinkedList.h"
#include "LinkedList/SinglyCircularLinkedList.h"
#include "LinkedList/SinglyLinkedList.h"

// ALL DECLARATIONS:
void start_engine();

// GLOBAL VARIABLES:
bool use_splaytree(bool abc = true){
    static bool splayertree = abc;
    return splayertree;
}
void wait(){
    auto startTime = std::chrono::steady_clock::now();
    std::srand(static_cast<unsigned int>(std::time(NULLpointer)));
    std::this_thread::sleep_for(std::chrono::milliseconds(latency_queue_forwarding));
}
int stringToInt(const String &str){
    int result = 0;
    bool negative = false;
    int i = 0;
    int length = str.len();

    if (length == 0)
        return 0; // empty string check

    if (str[0] == '-')
    {
        negative = true;
        i = 1;
    }
    else if (str[0] == '+')
    {
        i = 1;
    }
    for (; i < length; i++)
    {
        char c = str[i];
        if (c < '0' || c > '9')
        {
            return 0; // invalid character found
        }
        result = result * 10 + (c - '0');
    }
    return negative ? -result : result;
}

D2LL<String> all_connections;
all_connections.read_whole_csv();
D2LL<long long int> LANS;
ofstream clearFile2("recieved_messages.txt", std::ios::trunc);
clearFile2.close();
ofstream clearFile4("path.txt", std::ios::trunc);
clearFile4.close();

// GLOBAL FUNCTIONS:
void writeMessage(const Message &msg){
    ofstream file("recieved_messages.txt", std::ios::app); // append mode
    if (file.is_open())
    {
        file << msg;
        file.close();
    }
    else
    {
        if (debug)
            cout << "Failed to open recieved_messages.txt for writing." << endl;
    }
}
void writePath(const Message &msg){
    ofstream file("path.txt", std::ios::app);
    if (file.is_open())
    {
        file << msg.toPathString() << endl;
        file.close();
    }
    else
    {
        if (debug)
            cout << "Failed to open path.txt for writing." << endl;
    }
}

Message *&Send_Message(String filename1){
    // send msg //command
    // read only one message
    Message *msg = new Message("source", "destination", "payload", 1);
    ifstream file(filename1);
    if (!file.is_open()){
        cout << "Could not open this file: " << filename1 << endl;
        return NULLpointer;
    }
    String line;
    if (getline(file, line)){
        // Expected format: ID:PRIORITY:SRC:DEST:"PAYLOAD":"PATH"
        String id, priority, src, dest, payload, path;
        int stage = 0;
        String current;
        bool in_quotes = false;
        for (char c : line){
            if (c == ':' && !in_quotes){
                switch (stage){
                case 0:
                    id = current;
                    break;
                case 1:
                    priority = current;
                    break;
                case 2:
                    src = current;
                    break;
                case 3:
                    dest = current;
                    break;
                case 4:
                    payload = current.substr(1, current.length() - 2);
                    break;
                }
                current.clear();
                stage++;
            }
            else if (c == '"'){
                in_quotes = !in_quotes;
                if (stage == 5 && !in_quotes){
                    path = current.substr(1, current.length() - 2);
                }
            }
            else{
                current = current + c;
            }
        }
        if (stage < 5){
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
Message *Send_Message_S(String filename1)
{
    // send msgs //command
    // read all messages and send them
    ifstream file(filename1);
    if (!file.is_open())
    {
        cout << "could not open this file: " << filename1 << endl;
        return NULLpointer;
    }

    Message *first_message = NULLpointer;
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
                switch (stage)
                {
                case 0:
                    id = current;
                    break;
                case 1:
                    priority = current;
                    break;
                case 2:
                    src = current;
                    break;
                case 3:
                    dest = current;
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
                current = current + c;
            }
        }

        if (stage < 5)
        {
            cerr << "Invalid format: " << line << endl;
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

String Print_Path(String start, String end)
{
    ifstream file("received_messages.txt");

    if (!file.is_open())
    {
        if (debug)
            cout << "could not open received messages file " << endl;
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
                case 0:
                    id = current;
                    break;
                case 1:
                    priority = current;
                    break;
                case 2:
                    src = current;
                    break;
                case 3:
                    dest = current;
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
                current = current + c;
            }
        }
        if (path.find(start) != String::npos && path.find(end) != String::npos)
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
#endif