#include <vector>
#include <list>
#include <queue>         
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
// #include "proj2.h"

using namespace std;

int main() {
    string file;
    vector<vector<double>> data; // stores all data sets
    double value = 0.0; 
    string tempLine;
    int count = 0; // get line count
    vector<double> temp; // temp holding of values
    cout << "Input filename of data: "; // prompt for input of data
    cin >> file;
    ifstream inFile;
    inFile.open(file);
    if (!inFile) { // ensure that file is valid
        cout << "Error";
        cout << "check";
        exit(1);
    }
    
   // getline(inFile,line);
    while(getline(inFile,tempLine)) { // while data is present in the file
        temp.clear();
        stringstream line(tempLine);
        while(line >> value) {
            temp.push_back(value);
        }
        data.push_back(temp);
        count++;
    }
    inFile.close();
    
    for(int i = 0; i < data.size(); i++) {
        for(int j = 0; j < data[i].size();j++) {
            cout << data[i][j] << ' '; // print each line of the data vector
        }
        cout << endl;
               
    }
    cout << "Line count: " << count << endl;

    return 0;

}


