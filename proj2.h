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
        vector<double> compare;
};

// int normalizer(vector<vector<double>> test) {
//     for(int i = 0; i < test.size(); i++) {
//         for(int j = 1; j < test.size(); j++) {
//             test[i][j] = ( 1 / (1 + exp(-test[i][j])));
//         }
//     }
//     //return test;
// }

vector<double> trueSet;
double bestDist = 0.0;
double cDistance = 0.0;
int bestLoc = 0;

double leaveOneOut(vector<vector<double>> test, vector<int>goodSet) {
    int count = 0;
    for(int i = 0; i < test.size(); i++) {
        bestDist = 99999999.9999;
        bestLoc = -1;
        for(int j = 0; j < test.size(); j++) {
            cDistance = 0;
            if(i != j) {
                for(int k = 0; k < goodSet.size(); k++) {
                    cDistance += pow((test[i][k] - test[j][k]),2);
                }
                if(cDistance < bestDist) {
                    bestDist = cDistance;
                    bestLoc = j;
                }
            }
        }
        if(test[i][0] == test[bestLoc][0]) count++;

    }
    return (count / test.size());
}

void parse_data() {
    vector<vector<double>> data; // stores all data sets
    vector< pair<double,double>> vect;
    vector<double> temp;
    vector<double> checkup;
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

    
    //sort(data.begin(),data.end());
    cout << "This is data size: " << data[0].size() << endl;
    cout << "Data size: " << data.size() << endl;
    cin >> value;
    double bestAccuracy = 0.0;

    for(int i = 0; i < data.size(); i++) { // choose rows to initiate the rows
        for(int l = 1; l < data[i].size(); l++) { //add each feature to the comparison list
            checkup.push_back(data[i][l]);
        }
        for(int j = 0; j < data.size();j++) { // go through all the rows 
            // for(int k = 0; k < data[j].size();k++) { // go through each feature of compared rows

            // }
            if (i != j) {
                for(int m = 0; m < data[j].size(); m++) {
                    cout << data[j][m] << ' ';
                }
                
            }
            // else{
            //     cout << data[i][j] << ' '; // print each line of the data vector
            // }
        }
        cout << endl;
    }

    
    // for (int i = 0; i < data.size(); i++) {
    //     cout << "On the " << i <<"th level of the search tree " << endl;
    //     //lowestVal = data[i][1];
    //     for(int j = 1; j < data[i].size(); j++) {
    //         //cout << "--Considering adding the " << j << " feature" << endl;
    //         // if(data[i][j] < 0) {
    //         //    checkVal = abs(data[i][j] - lowestVal);
    //         //   if (checkVal < lowestVal) {

    //         //    }

    //         // }
    //        feature = rand() % 10;
    //     }
    //    cout << "On level " << i << " I added feature " << feature << " to current set" << endl;
    // }
    cout << "Line count: " << count << endl;
}

// leave_one_out_cross_validation(vector<vector<double>> crossData, vector<double>currentSet, double featureToAdd) {
//     vector<double>trainSet;
//     for(int i = 0; i < crossData.size(); i++) {
        
//     }
// }

