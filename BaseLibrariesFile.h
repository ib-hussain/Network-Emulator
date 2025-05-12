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
#define UNDERint -32765
#define NULLchar '\0'
#define NULLstring ""
#define NULLbool NULL
#define NULLdouble 0.0000
#define NULLfloat 0.0000
#define NULLpointer nullptr

// ALL DECLARATIONS:
struct LLNode;
struct D2LL;
struct String;
struct GPtrsNode;
struct GPtrs;
struct GraphNode;
struct Graph;
struct Router;
struct Machine;
struct Message;
struct Queue;
struct PQ;
struct RoutT;
struct box_LL;
struct Entry;
struct Linear_List;
struct STree;
void start_engine();

// GLOBAL CONSTANTS/VARIABLES:
const unsigned short int latency_queue_forwarding = 0;
unsigned long long int global_ID_declare = FULLint;
const bool debug = true;
D2LL<String> all_connections;
all_connections.read_whole_csv();
ofstream clearFile2("recieved_messages.txt", std::ios::trunc);
clearFile2.close();
ofstream clearFile4("path.txt", std::ios::trunc);
clearFile4.close();
// GLOBAL FUNCTIONS:
void writeMessage(const Message &msg) {
    ofstream file("recieved_messages.txt", std::ios::app); // append mode
    if (file.is_open()) {
        file << msg;
        file.close();
    }
    else{
        if(debug)cout << "Failed to open recieved_messages.txt for writing." << endl;
    }
}
void writePath(const Message &msg) {
    ofstream file("path.txt", std::ios::app);
    if (file.is_open()) {
        file << msg.toPathString() << endl;
        file.close();
    } else {
        if(debug) cout << "Failed to open path.txt for writing." << endl;
    }
}
void wait(){
    auto startTime = std::chrono::steady_clock::now();
    std::srand(static_cast<unsigned int>(std::time(NULLpointer)));
    std::this_thread::sleep_for(std::chrono::milliseconds(latency_queue_forwarding));
}
Message *&Send_Message(String filename1)
{
    // send msg //command
    // read only one message
    Message *msg = new Message("source", "destination", "payload", 1);
    return msg;
}
Message *Send_Message_S(String filename1)
{
    // send msgs //command
    // read all messages and send them
}
String Print_Path(String start, String end)
{
    // print path
    // take start and end and scan it from the output messsages file and
    // put it in the path.txt
    if ()
    {

        return String(NULLstring);
    }
    else
    {
        return String("No message found");
    }
}

#endif