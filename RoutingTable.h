#ifndef ROUTINGTABLE_H
#define ROUTINGTABLE_H
#include "SinglyLinkedList.h"
//perfected------------------------------------------------------------------------
struct Entry{
    String destination;
    String next_router;// outgoing queue direction
    Entry(const String& dest = NULLstring, const String& next = NULLstring):destination(dest), next_router(next){}
    friend ostream& operator<<(ostream& out, const Entry& entry){
        out <<entry.destination << "," << entry.next_router;
        return out;
    }
    friend istream& operator>>(istream& in, Entry& entry){
        in >> entry.destination;
        in >> entry.next_router;
        return in;
    }
    Entry(const Entry& other):destination(other.destination), next_router(other.next_router){}
    Entry& operator=(const Entry& other){
        if(this != &other){
            destination = other.destination;
            next_router = other.next_router;
        }
        return *this;
    }
    Entry(Entry& other, bool kill=false):destination(other.destination), next_router(other.next_router){
        if(kill){other.~Entry();}
    }
    Entry(Entry* other):destination(other->destination), next_router(other->next_router){}
    ~Entry(){
        delete destination;
        delete next_router;
    }
};
struct RoutT{
    Linear_List<Entry> tabular;
    RoutT(){}
    bool add(const String& dest, const String& next){//add M4,R1
        Entry<rt_dtype11> new_entry(dest, next);
        return tabular.insert(new_entry);
    }
    bool remove(const String& dest, const String& next){// remove M4,R2
        for(int d=0;d<=tabular.nodes;d++){
            if((tabular[d].destination == dest) && (tabular[d].next_router == next)){
                return tabular.delete_entry(tabular[d]);
            }
        }
        return false;
    }
    bool add_csv(const String& file_to_read = NULLstring){// add rt_1.csv
        if(file_name==NULLstring)return false;
        ifstream file(file_to_read);
        if (!file.is_open()) {
            // cout << "Failed to open file." << endl;
            return false;
        }
        vector<vector<string>> temp_data;
        string line;
        // Read and skip the first row (column headers)
        getline(file, line); 
        while (getline(file, line)) {
            stringstream ss(line);
            string cell;
            vector<string> row;
            // Skip the first column (row header)
            // getline(ss, cell, ',');
            // Read remaining cells
            while (getline(ss, cell, ',')) {
                row.push_back(cell);
            }
            temp_data.push_back(row);
        }
        int n = temp_data.size(); // since it's square, row count = col count
        string** data = new string*[n];
        for (int i = 0; i < n; ++i) {
            data[i] = new string[2];
            for (int j = 0; j < 2; ++j) {
                data[i][j] = temp_data[i][j];
            }
        }
        for(int f=0;f<n;f++){
            for(int g=0;g<2;g++){
                add(data[f][0], data[f][1]);
            }
        }
        for(int i = 0; i < n; i++){
            delete[] data[i];
        }
        delete[] data;
        return true;
    }
    bool remove_csv(const String& file_to_read = NULLstring){// remove rt_2.csv
        if(file_name==NULLstring)return false;
        ifstream file(file_to_read);
        if (!file.is_open()) {
            // cout << "Failed to open file." << endl;
            return false;
        }
        vector<vector<string>> temp_data;
        string line;
        // Read and skip the first row (column headers)
        getline(file, line); 
        while (getline(file, line)) {
            stringstream ss(line);
            string cell;
            vector<string> row;
            // Skip the first column (row header)
            // getline(ss, cell, ',');
            // Read remaining cells
            while (getline(ss, cell, ',')) {
                row.push_back(cell);
            }
            temp_data.push_back(row);
        }
        int n = temp_data.size(); // since it's square, row count = col count
        string** data = new string*[n];
        for (int i = 0; i < n; ++i) {
            data[i] = new string[2];
            for (int j = 0; j < 2; ++j) {
                data[i][j] = temp_data[i][j];
            }
        }
        for(int f=0;f<n;f++){
            for(int g=0;g<2;g++){
                remove(data[f][0], data[f][1]);
            }
        }
        for(int i = 0; i < n; i++){
            delete[] data[i];
        }
        delete[] data;
        return true;
    }
    ~RoutT(){
        delete tabular;
    }
};
#endif