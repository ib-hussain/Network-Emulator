#ifndef BASELIBRARIESFILE_H
#define BASELIBRARIESFILE_H

#include <iostream>
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
// #define
// make macro for reference to pointer type assignement
// and also we need to define all constants here for the project

struct String
{
private:
    char *data;

public:
    String(const char *input = "")
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
    const char &operator[](int index) const
    {
        return data[index];
    }
    int len() const
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
    String slice(int start, int end) const
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

#endif