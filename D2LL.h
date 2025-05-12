#ifndef D2LL_H
#define D2LL_H
#include "LLNode.h"

template <class D_Grphi6 = String>
struct D2LL{
private:
    LLNode<D_Grphi6>** o0_0o;
    bool ExtractRouterMatrix(const string& input_file = "network.csv", const string& output_file = "routers.csv") {
        ifstream file(input_file);
        ofstream out(output_file);
        if (!file.is_open()) {
            if(debug)cout << "Could not open input file." << endl;
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
            if(debug)cout << "Router labels not found in rows/columns." << endl;
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
        if(debug)cout << "Router matrix written to " << output_file << " with empty (0,0) cell." << endl;
        return true;
    }
    bool ExtractMachineMatrix(const string& input_file = "network.csv", const string& output_file = "machines.csv") {
        ifstream file(input_file);
        ofstream out(output_file);
        if (!file.is_open()) {
            if(debug)cout << "Could not open input file." << endl;
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
            if (!all_data[i][0].empty() && all_data[i][0][0] == 'M') {
                row_start = i;
                break;
            }
        }
        // Find first 'R' column
        for (int j = 1; j < all_data[0].size(); ++j) {
            if (!all_data[0][j].empty() && all_data[0][j][0] == 'M') {
                col_start = j;
                break;
            }
        }
        if (row_start == -1 || col_start == -1) {
            if(debug)cout << "Router labels not found in rows/columns." << endl;
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
        if(debug)cout << "Machine matrix written to " << output_file << " with empty (0,0) cell." << endl;
        return true;
    }
public:
    int rows;
    int columns;
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
            if(debug)cout << "Failed to open file." << endl;
            return false;
        }
        if(!ExtractRouterMatrix())return false;
        if(!ExtractMachineMatrix())return false;
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
        const string file_to_read = (file_name == NULLstring) ? "routers.csv" : csv_file_name;
        ifstream file(file_to_read);
        if (!file.is_open()) {
            if(debug)cout << "Failed to open file." << endl;
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

#endif