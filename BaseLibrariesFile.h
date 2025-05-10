#ifndef BASELIBRARIESFILE_H
#define BASELIBRARIESFILE_H

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
// any libraries that need to be added to the project should be included here and they will be included in all other files
using namespace std;
#define NULLint 0
#define FULLint -32767
#define NULLchar '\0'
#define NULLstring ""
#define NULLbool NULL
#define NULLdouble 0.0000
#define NULLfloat 0.0000
#define NULLpointer nullptr

// and also we need to define all constants here for the project
const short int latency_queue_forwarding = 0;
unsigned long long int global_ID_declare = 32767;
// make macro for reference to pointer type assignement maybe
struct String
{
private:
    mutable char *data;
public:
    String(const char *input = NULLstring)
    {
        int length = 0;
        while (input[length] != '\0')
            length++;
        data = new char[length + 1];
        for (int i = 0; i < length; i++)
            data[i] = input[i];
        data[length] = '\0';
    }
    String(const String &other)
    {
        int length = other.len();
        data = new char[length + 1];
        for (int i = 0; i < length; i++)
            data[i] = other.data[i];
        data[length] = '\0';
    }
    String(string& other){
        int length = other.length();
        data = new char[length + 1];
        for (int i = 0; i < length; i++)
            data[i] = other[i];
        data[length] = '\0';
    }
    String &operator=(const String &other)
    {
        if (this != &other)
        {
            delete[] data;
            int length = other.len();
            data = new char[length + 1];
            for (int i = 0; i < length; i++)
                data[i] = other.data[i];
            data[length] = '\0';
        }
        return *this;
    }
    String& operator=(const char *other)
    {
        delete[] data;
        int length = 0;
        while (other[length] != '\0')
            length++;
        data = new char[length + 1];
        for (int i = 0; i < length; i++)
            data[i] = other[i];
        data[length] = '\0';
        return *this;
    }
    String& operator=(string& other){
        delete[] data;
        int length = other.length();
        data = new char[length + 1];
        for (int i = 0; i < length; i++)
            data[i] = other[i];
        data[length] = '\0';
        return *this;
    }
    String &operator+(const String &other)
    {
        int length1 = len();
        int length2 = other.len();
        char *new_data = new char[length1 + length2 + 1];
        for (int i = 0; i < length1; i++)
            new_data[i] = data[i];
        for (int i = 0; i < length2; i++)
            new_data[length1 + i] = other.data[i];
        new_data[length1 + length2] = NULLchar;
        delete[] data;
        data = new_data;
        return *this;
    }
    String &operator+(char other)
    {
        int length = len();
        char *new_data = new char[length + 2];
        for (int i = 0; i < length; i++)
            new_data[i] = data[i];
        new_data[length] = other;
        new_data[length + 1] = NULLchar;
        delete[] data;
        data = new_data;
        return *this;
    }
    String& operator+(const char *other)
    {
        int length1 = len();
        int length2 = 0;
        while (other[length2] != '\0')
            length2++;
        char *new_data = new char[length1 + length2 + 1];
        for (int i = 0; i < length1; i++)
            new_data[i] = data[i];
        for (int i = 0; i < length2; i++)
            new_data[length1 + i] = other[i];
        new_data[length1 + length2] = NULLchar;
        delete[] data;
        data = new_data;
        return *this;
    }
    String &operator+(string& other)
    {
        int length1 = len();
        int length2 = other.length();
        char *new_data = new char[length1 + length2 + 1];
        for (int i = 0; i < length1; i++)
            new_data[i] = data[i];
        for (int i = 0; i < length2; i++)
            new_data[length1 + i] = other[i];
        new_data[length1 + length2] = NULLchar;
        delete[] data;
        data = new_data;
        return *this;
    }
    String &operator+=(const String &other)
    {
        return *this + other;
    }
    String &operator+=(char other)
    {
        return *this + other;
    }
    String &operator+=(const char *other)
    {
        return *this + other;
    }
    String &operator+=(string& other)
    {
        return *this + other;
    }
    bool operator==(const String &other)
    {
        int length1 = len();
        int length2 = other.len();
        if (length1 != length2)
            return false;
        for (int i = 0; i < length1; i++)
            if (data[i] != other.data[i])
                return false;
        return true;
    }
    bool operator!=(const String &other)
    {
        while(data[a] != NULLchar){
            if(data[a] == other.data[a]){
                return false;
            }
            a++;
        }
        return true;
    }
    operator string()
    {
        string result = NULLstring;
        int length = len();
        for (int i = 0; i < length; i++)
            result += data[i];
        return result;
    }
    operator char *()
    {
        return data;
    }
    operator String()
    {
        return *this;
    }
    ~String()
    {
        delete[] data;
    }
    char &operator[](int index)
    {
        if (index < 0)
            index = 0; // handle negative index
        if (index >= len())
            index = len() - 1; // handle out of bounds
        return data[index];    // no bounds checking
    }
    const char &operator[](int index)
    {
        return data[index];
    }
    int len()
    {
        int length = 0;
        while (data[length] != '\0')
            length++;
        return length;
    }
    friend ostream &operator<<(ostream &out, const String &s)
    {
        out << s.data;
        return out;
    }
    friend istream &operator>>(istream &in, String &s)
    {
        char temp[1000]; // temporary buffer
        in >> temp;

        delete[] s.data; // release old memory
        int length = 0;
        while (temp[length] != '\0')
            length++;

        s.data = new char[length + 1];
        for (int i = 0; i < length; i++)
            s.data[i] = temp[i];
        s.data[length] = '\0';
        return in;
    }
    String slice(int start, int end)
    {
        int length = len();

        // Bounds correction
        if (start < 0)
            start = 0;
        if (end > length)
            end = length;
        if (start > end)
            start = end;

        int new_len = end - start;
        char *sliced = new char[new_len + 1];

        for (int i = 0; i < new_len; i++)
            sliced[i] = data[start + i];
        sliced[new_len] = '\0';

        String result(sliced);
        delete[] sliced;
        return result;
    }
};
struct Message
{
    const long long int ID;
    short int priority;
    const String source_address;
    String destination_address;
    const String payload;
    String path;
    Message(String src, String dest = NULLstring, String pl, short int p = NULLint) : payload(pl), ID(++global_ID_declare), source_address(src), destination_address(dest), priority(p)
    {
        path = src;
    }
    Message &operator+(String &other)
    {
        path = path + ":" + other;
        return *this;
    }
    ~Message(){
        // destructor
        delete source_address;
        delete destination_address;
        delete payload;
        delete path;
    }
};
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