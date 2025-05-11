#ifndef GRAPH_H
#define GRAPH_H
#include "Router.h"
template <class D_Grphi1 = Router>
struct GraphNode{
    D_Grphi1 data;// this will have the name and the id itself
    GPtrs<D_Grphi1> pointers;
    // i am making 1 graph node and making a linked list in it that holds the pointers to the other nodes in the graph
    // this is a singly circular linked list of pointers to the other nodes in the graph
    GraphNode(D_Grphi1 datai):data(datai), pointers(){}// this is the only constructor
    ~GraphNode(){
        delete data;
        delete pointers;
    }
};
// friend pair 1:
template <class D_Grphi2 = Router>
struct GPtrsNode{
    int weight;
    GraphNode<D_Grphi2>* connection;
    GPtrsNode(): weight(NULLint), connection(NULLpointer),  nextnode(NULLpointer) {}
    GPtrsNode(int weighti, GraphNode<D_Grphi2>* nexti): weight(weighti), connection(nexti) , nextnode(NULLpointer) {}
    //xfcvgh
    friend class GPtrs<D_Grphi2>;
    ~GPtrsNode(){
        weight = NULLint;
        connection= NULLpointer ;
        nextnode = NULLpointer;
    }
    int& operator*(){
        return weight;
    }
    GraphNode<D_Grphi2>* operator>>(int i=NULLint){
        return connection;
    }
private:
    GPtrsNode<D_Grphi2>* nextnode;
};
template <class D_Grphi3 = Router>
struct GPtrs{
private:
    // this is a singly circular linked list that stores the pointers to the other nodes in the graph
    GPtrsNode<D_Grphi3>* tail;
    int nodes;
    bool insert(GraphNode<D_Grphi3>* newNode, int weighti){
        if(!tail){
            tail = new GPtrsNode<D_Grphi3>(weighti, newNode);//fix this constructor call here
            tail->nextnode = tail;
            nodes++;
            return true;
        }
        else{
            GPtrsNode* newNode = new GPtrsNode<D_Grphi3>(weighti, newNode);
            newNode->nextnode = tail->nextnode;
            tail->nextnode = newNode;
            tail = newNode;
            nodes++;
            return true;
        }
        return false;
    }
    bool remove(GraphNode<D_Grphi3>* node){
        if(!tail) return false;
        GPtrsNode<D_Grphi3>* current = tail->nextnode;
        GPtrsNode<D_Grphi3>* previous = tail;
        do{
            if(current->connection == node){
                if(current == tail){
                    tail = previous;
                }
                previous->nextnode = current->nextnode;
                delete current;
                nodes--;
                return true;
            }
            previous = current;
            current = current->nextnode;
        }while(current != tail->nextnode);
        return false;
    }
    bool ifempty(){
        return (tail == NULLpointer);
    }
public:
    GPtrs(): head(NULLpointer), tail(NULLpointer), nodes(-1) {}
    GPtrsNode<D_Grphi3>& operator[](int i){
        static GPtrsNode<D_Grphi3> NullNode;
        if(i < 0 || i >= nodes) return NullNode;
        GPtrsNode<D_Grphi3>* current = tail->nextnode;
        for(int j = 0; j < i; j++){
            current = current->nextnode;
        }
        return (*current);
    }
    GPtrsNode<D_Grphi3>& operator[](GraphNode<D_Grphi3>* node){
        static GPtrsNode<D_Grphi3> NullNode;
        if(ifempty()) return NullNode;
        GPtrsNode<D_Grphi3>* current = tail->nextnode;
        do{
            if(current->connection == node) return (*current);
            current = current->nextnode;
        }while(current != tail->nextnode);
        return NullNode;
    }
    ~GPtrs(){
        GPtrsNode<D_Grphi3>* current = tail->nextnode;
        GPtrsNode<D_Grphi3>* next = NULLpointer;
        do{
            next = current->nextnode;
            delete current;
            current = next;
        }while(current != tail->nextnode);
        delete tail;
    }
};
//friend pair 2:
template <class D_Grphi5 = String>
struct LLNode{
    D_Grphi5 data;//make this template later
    LLNode():data(NULLint-1), left(NULLpointer), right(NULLpointer), up(NULLpointer), down(NULLpointer){}
    LLNode(D_Grphi5 datai):data(datai), left(NULLpointer), right(NULLpointer), up(NULLpointer), down(NULLpointer){}
    ~LLNode(){
        left = NULLpointer;
        right = NULLpointer;
        up = NULLpointer;
        down = NULLpointer;
        delete data;
    }
    LLNode<D_Grphi5>& operator=(const LLNode<D_Grphi5>& other){
        data = other.data;
        return *this;
    }
    LLNode<D_Grphi5>& operator=(const D_Grphi5& other){
        data = other;
        return *this;
    }
    friend class D2LL<D_Grphi5>;
private:
    LLNode* left;
    LLNode* right;
    LLNode* up;
    LLNode* down;
};
template <class D_Grphi6 = String>
struct D2LL{
private:
    LLNode<D_Grphi6>** o0_0o;
    int rows;
    int columns;
    bool ExtractRouterMatrix(const string& input_file = "network.csv", const string& output_file = "routers.csv") {
        ifstream file(input_file);
        ofstream out(output_file);
        if (!file.is_open()) {
            // cout << "Could not open input file." << endl;
            return false;
        }
        vector<vector<string>> all_data;
        string line;
        // Read all rows into memory
        while (getline(file, line)) {
            stringstream ss(line);
            string cell;
            vector<string> row;
            while (getline(ss, cell, ',')) {
                row.push_back(cell);
            }
            all_data.push_back(row);
        }
        // Identify start index for rows and columns with label starting with 'R'
        int row_start = -1, col_start = -1;
        // Find first 'R' row
        for (int i = 1; i < all_data.size(); ++i) {
            if (!all_data[i][0].empty() && all_data[i][0][0] == 'R') {
                row_start = i;
                break;
            }
        }
        // Find first 'R' column
        for (int j = 1; j < all_data[0].size(); ++j) {
            if (!all_data[0][j].empty() && all_data[0][j][0] == 'R') {
                col_start = j;
                break;
            }
        }
        if (row_start == -1 || col_start == -1) {
            // cout << "Router labels not found in rows/columns." << endl;
            return false;
        }
        // Write header row with empty (0,0) cell
        out << ""; // top-left cell left empty
        for (int j = col_start; j < all_data[0].size(); ++j) {
            out << "," << all_data[0][j];
        }
        out << endl;
        // Write remaining router matrix with row labels
        for (int i = row_start; i < all_data.size(); ++i) {
            out << all_data[i][0]; // row label
            for (int j = col_start; j < all_data[i].size(); ++j) {
                out << "," << all_data[i][j];
            }
            out << endl;
        }
        file.close();
        out.close();
        // cout << "Router matrix written to " << output_file << " with empty (0,0) cell." << endl;
        return true;
    }
public:
    friend class Graph<D_Grphi6>;
    friend ostream& operator<<(ostream& os, const D2LL<D_Grphi6>& obj){
        for(int i = 0; i < obj.rows; i++){
            for(int j = 0; j < obj.columns; j++){
                os << obj.o0_0o[i][j].data << ",";
            }
            os << endl;
        }
        return os;
    }
    bool read_whole_csv(const String& file_name = NULLstring){// use for string
        // read the csv file and fill the all_connections
        // return true if successful, false otherwise
        const string file_to_read = (file_name == NULLstring) ? "network.csv" : csv_file_name;
        ifstream file(file_to_read);
        if (!file.is_open()) {
            // cout << "Failed to open file." << endl;
            return false;
        }
        vector<vector<string>> temp_data;
        string line;
        // Read and skip the first row (column headers)
        // getline(file, line); 
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
            data[i] = new string[n];
            for (int j = 0; j < n; ++j) {
                data[i][j] = temp_data[i][j];
            }
        }
        initialise(n, n);
        for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    // get(i,j) =((data[i][j]=="?")?(-1):(stoi(data[i][j])));
                    get(i,j) =data[i][j];
                }
            }
        for(int i = 0; i < n; i++){
            delete[] data[i];
        }
        delete[] data;
        return true;
    }
    bool read_almost_all_csv(const String& file_name = NULLstring){// use for int
        if(!ExtractRouterMatrix())return false;
        const string file_to_read = (file_name == NULLstring) ? "routers.csv" : csv_file_name;
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
            getline(ss, cell, ',');
            // Read remaining cells
            while (getline(ss, cell, ',')) {
                row.push_back(cell);
            }
            temp_data.push_back(row);
        }
        int n = temp_data.size(); // since it's square, row count = col count
        string** data = new string*[n];
        for (int i = 0; i < n; ++i) {
            data[i] = new string[n];
            for (int j = 0; j < n; ++j) {
                data[i][j] = temp_data[i][j];
            }
        }
        initialise(n, n);
        for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    get(i,j) =((data[i][j]=="?")?(-1):(stoi(data[i][j])));
                    // get(i,j) =data[i][j];
                }
            }
        for(int i = 0; i < n; i++){
            delete[] data[i];
        }
        delete[] data;
        return true;
    }
    D2LL(){
        o0_0o = NULLpointer;
    }
    bool initialise(int rows1, int columns1){
        if(rows1 <= 0 || columns1 <= 0) return false;
        rows = rows1;
        columns = columns1;
        o0_0o = new LLNode<D_Grphi6>*[rows];
        for(int i = 0; i < rows; i++){
            o0_0o[i] = new LLNode[columns];
            for(int j = 0; j < columns; j++){
                o0_0o[i][j].left = (j == 0) ? NULLpointer : &o0_0o[i][j-1];
                o0_0o[i][j].right = (j == columns-1) ? NULLpointer : &o0_0o[i][j+1];
                o0_0o[i][j].up = (i == 0) ? NULLpointer : &o0_0o[i-1][j];
                o0_0o[i][j].down = (i == rows-1) ? NULLpointer : &o0_0o[i+1][j];
            }
        }
        return true;
    }
    bool resize(int rows1, int columns1){
        if(rows1 <= 0 || columns1 <= 0) return false;
        LLNode<D_Grphi6>** new_o0_0o = new LLNode<D_Grphi6>*[rows1];
        for(int i = 0; i < rows1; i++){
            new_o0_0o[i] = new LLNode<D_Grphi6>[columns1];
            for(int j = 0; j < columns1; j++){
                if(i < rows && j < columns){
                    new_o0_0o[i][j] = o0_0o[i][j];
                }
                else{
                    new_o0_0o[i][j].left = (j == 0) ? NULLpointer : &new_o0_0o[i][j-1];
                    new_o0_0o[i][j].right = (j == columns1-1) ? NULLpointer : &new_o0_0o[i][j+1];
                    new_o0_0o[i][j].up = (i == 0) ? NULLpointer : &new_o0_0o[i-1][j];
                    new_o0_0o[i][j].down = (i == rows1-1) ? NULLpointer : &new_o0_0o[i+1][j];
                }
            }
        }
        for(int i = 0; i < rows; i++){
            delete[] o0_0o[i];
        }
        delete[] o0_0o;
        o0_0o = new_o0_0o;
        rows = rows1;
        columns = columns1;
        return true;
    }
    LLNode<D_Grphi6>& get(int i, int j){
        if(i < 0 || i >= rows || j < 0 || j >= columns) return NULLpointer;
        return o0_0o[i][j];
    }
    D_Grphi6& get(int i, int j){
        if(i < 0 || i >= rows || j < 0 || j >= columns) return NULLpointer;
        return (o0_0o[i][j].data);
    }
    ~D2LL(){
        for(int i = 0; i < rows; i++){
            delete[] o0_0o[i];
        }
        delete[] o0_0o;
    }
};
template <class D_Grphi4 = Router, class Adj_List_type = String, class RT_type_connects = int>
struct Graph{
    GraphNode<D_Grphi4>* top;
    D2LL<Adj_List_type> all_connections;
    D2LL<RT_type_connects> LANS;
    int nodes;
    Graph():top(NULLpointer){
        nodes=-1;
        if(all_connections.read_whole_csv() && LANS.read_almost_all_csv()){
            make_graph();
        }
        else{
            finish_graph();
        }
    }
    bool make_graph(){
        int r=0, c=0;
        for(;r;r++){
            for(;c;c++){

            }
        }
    }
    bool add_node(){
        if(!top){
            D_Grphi4* datai = new D_Grphi4();
            top = new GraphNode<D_Grphi4>();
            nodes++;
            return true;
        }
        else{

        }
        return false;
    }
    bool delete_node(){}
    ~Graph(){
        finish_graph();
        delete all_connections;
        (!top)?() : delete top;
    }
    void finish_graph(){
        if(!top) return;
    }
    GraphNode<D_Grphi4>& operator[](long long int IDi){
        static GraphNode<D_Grphi4> NullNode7;
        if((IDi < 0)||(IDi > global_ID_declare+1)) return NullNode7;
        

    }
};


#endif