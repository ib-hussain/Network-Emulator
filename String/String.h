#ifndef STRING_H
#define STRING_H
#include "../BaseLibrariesFile.h"
struct String {
private:
    mutable char* data;
    int cstrlen(const char* str) const {
        int len = 0;
        while (str[len] != NULLchar) len++;
        return len;
    }
public:
    String(const char* input = NULLstring) {
        int length = cstrlen(input);
        data = new char[length + 1];
        for (int i = 0; i < length; i++) data[i] = input[i];
        data[length] = NULLchar;
    }
    String(const String& other) {
        int length = other.len();
        data = new char[length + 1];
        for (int i = 0; i < length; i++) data[i] = other.data[i];
        data[length] = NULLchar;
    }
    String(string& other) {
        int length = other.length();
        data = new char[length + 1];
        for (int i = 0; i < length; i++) data[i] = other[i];
        data[length] = NULLchar;
    }
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            int length = other.len();
            data = new char[length + 1];
            for (int i = 0; i < length; i++) data[i] = other.data[i];
            data[length] = NULLchar;
        }
        return *this;
    }
    String& operator=(const char* other) {
        delete[] data;
        int length = cstrlen(other);
        data = new char[length + 1];
        for (int i = 0; i < length; i++) data[i] = other[i];
        data[length] = NULLchar;
        return *this;
    }
    String& operator=(string& other) {
        delete[] data;
        int length = other.length();
        data = new char[length + 1];
        for (int i = 0; i < length; i++) data[i] = other[i];
        data[length] = NULLchar;
        return *this;
    }
    String& operator+(const String& other) {
        int l1 = len(), l2 = other.len();
        char* new_data = new char[l1 + l2 + 1];
        for (int i = 0; i < l1; i++) new_data[i] = data[i];
        for (int i = 0; i < l2; i++) new_data[l1 + i] = other.data[i];
        new_data[l1 + l2] = NULLchar;
        delete[] data;
        data = new_data;
        return *this;
    }
    String& operator+(char other) {
        int l = len();
        char* new_data = new char[l + 2];
        for (int i = 0; i < l; i++) new_data[i] = data[i];
        new_data[l] = other;
        new_data[l + 1] = NULLchar;
        delete[] data;
        data = new_data;
        return *this;
    }
    String& operator+(const char* other) {
        int l1 = len(), l2 = cstrlen(other);
        char* new_data = new char[l1 + l2 + 1];
        for (int i = 0; i < l1; i++) new_data[i] = data[i];
        for (int i = 0; i < l2; i++) new_data[l1 + i] = other[i];
        new_data[l1 + l2] = NULLchar;
        delete[] data;
        data = new_data;
        return *this;
    }
    String& operator+(string& other) {
        int l1 = len(), l2 = other.length();
        char* new_data = new char[l1 + l2 + 1];
        for (int i = 0; i < l1; i++) new_data[i] = data[i];
        for (int i = 0; i < l2; i++) new_data[l1 + i] = other[i];
        new_data[l1 + l2] = NULLchar;
        delete[] data;
        data = new_data;
        return *this;
    }
    String& operator+=(const String& other) { return *this + other; }
    String& operator+=(char other) { return *this + other; }
    String& operator+=(const char* other) { return *this + other; }
    String& operator+=(string& other) { return *this + other; }
    bool operator==(const String& other) const {
        int l1 = len(), l2 = other.len();
        if (l1 != l2) return false;
        for (int i = 0; i < l1; i++) if (data[i] != other.data[i]) return false;
        return true;
    }
    bool operator!=(const String& other) const {
        return !(*this == other);
    }
    operator string() const {
        return string(data);
    }
    operator char*() const {
        return data;
    }
    operator String() const {
        return *this;
    }
    ~String() {
        delete[] data;
    }
    char& operator[](int index) {
        if (index < 0) index = 0;
        int l = len();
        if (index >= l) index = l - 1;
        return data[index];
    }
    int len() const {
        return cstrlen(data);
    }
    friend ostream& operator<<(ostream& out, const String& s) {
        out << s.data;
        return out;
    }
    friend istream& operator>>(istream& in, String& s) {
        char temp[1000];
        in >> temp;
        delete[] s.data;
        int l = s.cstrlen(temp);
        s.data = new char[l + 1];
        for (int i = 0; i < l; i++) s.data[i] = temp[i];
        s.data[l] = NULLchar;
        return in;
    }
    String slice(int start, int end) const {
        int length = len();
        if (start < 0) start = 0;
        if (end > length) end = length;
        if (start > end) start = end;
        int new_len = end - start;
        char* sliced = new char[new_len + 1];
        for (int i = 0; i < new_len; i++) sliced[i] = data[start + i];
        sliced[new_len] = NULLchar;
        String result(sliced);
        delete[] sliced;
        return result;
    }
};

#endif
