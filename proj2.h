#include <vector>
#include <list>
#include <queue>         
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;
class bigData {
    public:
        vector<vector<double>> data;
};
int normalizer(vector<vector<double>> test) {
    for(int i = 0; i < test.size(); i++) {
        for(int j = 1; j < test.size(); j++) {
            test[i][j] = ( 1 / (1 + exp(-test[i][j])));
        }
    }
    //return test;
}
void parse_data() {
    vector<vector<double>> data; // stores all data sets
    vector< pair<double,double>> vect;
    vector<double> temp;
    double lowestVal = 0.0;
    double value = 0.0;
    double a=0.0,b=0.0;
    int count = 0;
    double checkVal = 0.0;
    int feature = 0;
    string tempLine;
    string file;
    cout << "Input filename of data: "; // prompt for input of data
    cin >> file;
    ifstream inFile;
    inFile.open(file);
    if (!inFile) { // ensure that file is valid
        cout << "Error";
        cout << "check";
        exit(1);
    }
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
    //data = normalizer(data);
    // for(int i = 0; i < data.size(); i++) {
    //     for(int j = 1; j < data.size(); j++) {
    //         data[i][j] = (1 / (1 + exp(-data[i][j])));
    //     }
    // }

    //sort(data.begin(),data.end());
    for(int i = 0; i < data.size(); i++) {
        for(int j = 0; j < data[i].size();j++) {
            if (j == 0) {
                cout << data[i][j] + 0.0 << ' ';
            }
            else{
                cout << data[i][j] << ' '; // print each line of the data vector
            }
        }
        cout << endl;
               
    }

    
    for (int i = 0; i < data.size(); i++) {
        cout << "On the " << i <<"th level of the search tree " << endl;
        //lowestVal = data[i][1];
        for(int j = 1; j < data[i].size(); j++) {
            cout << "--Considering adding the " << j << " feature" << endl;
            // if(data[i][j] < 0) {
            //    checkVal = abs(data[i][j] - lowestVal);
            //   if (checkVal < lowestVal) {

            //    }

            // }
           feature = rand() % 10;
        }
       cout << "On level " << i << " I added feature " << feature << " to current set" << endl;
    }
    cout << "Line count: " << count << endl;

}

// leave_one_out_cross_validation(vector<vector<double>> crossData, vector<double>currentSet, double featureToAdd) {
//     vector<double>trainSet;
//     for(int i = 0; i < crossData.size(); i++) {
        
//     }
// }

