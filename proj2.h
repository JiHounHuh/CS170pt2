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

vector<double> trueSet;
double bestDist = 0.0;
double cDistance = 0.0;
int bestLoc = 0;
double total = 0.0;
int counter = 0;

double leaveOneOut(vector<vector<double>> test, vector<int>goodSet) 
{
    counter = 0;
    total = 0.0;
    cout << "Size of GoodSet= " << goodSet.size() << endl;
    for(int i = 0; i < test.size(); i++) 
    { // get row
        bestDist = 99999.9999;
        bestLoc = -1;
        for(int j = 0; j < test.size(); j++) 
        { // get row 
            cDistance = 0.0;
            if(i != j) 
            {
                //cout << "Size of GoodSet  = " << goodSet.size() << endl;
                for(int k = 0; k < goodSet.size()-1; k++) 
                {
                    cDistance += pow((test[i][goodSet[k]] - test[j][goodSet[k]]),2);
                    //cDistance = cDistance + ((test[i][goodSet[k]] - test[j][goodSet[k]]) * (test[i][goodSet[k]] - test[j][goodSet[k]]));
                }
                cDistance = double(sqrt(cDistance));
                if(cDistance < bestDist) 
                {
                    bestDist = cDistance;
                    bestLoc = j;
                }
            }
        }
        if(test[i][0] == test[bestLoc][0]) {
            counter++;
            cout << "I got exemplar " << i + 1 << " correct" << endl;
        }
    }
    //cout << "Test size is: " << test.size() << endl;
    total = (double(counter) / double(test.size()));
    cout << "total is: " << total << endl;
    return total;
}

void forward_search(vector<vector<double>> data) {
    cout << "This is feature size: " << data[0].size()-1 << endl;
    cout << "Data size: " << data.size() << endl;
    double bestAccuracy = 0.0;
    double accuracy = 0.0;
    double bestestAccuracy = 0.0;
    vector<int> temp;
    vector<int> current_set_of_features;
    vector<int> testerSet;
    vector<int> feature_to_add;
    vector<int> master_list;
    int goodFeature = 0;
    master_list.clear();
    for(int i = 1; i < data[0].size(); i++) 
    { // starting from 1, # of features is 10
        cout << "On the " << i  << "th level of the search tree " << endl;
        feature_to_add.clear();
        //current_set_of_features.clear();
        temp.clear();
        testerSet.clear();
        bestAccuracy = 0.0;
        for(int j = 1; j < data[0].size(); j++) 
        {
            if(!(find(current_set_of_features.begin(),current_set_of_features.end(),j) != current_set_of_features.end())) 
            { // Consider if it does not exist
                cout << "--Considering adding the " << j << " feature" << endl;
                //testerSet.clear();
                testerSet.push_back(j);
                testerSet.insert(testerSet.end(),current_set_of_features.begin(),current_set_of_features.end());
                testerSet.insert(testerSet.end(),feature_to_add.begin(),feature_to_add.end());
                sort(testerSet.begin(),testerSet.end());
                testerSet.erase(unique(testerSet.begin(),testerSet.end()),testerSet.end());
                cout << "Tester Set: ";
                for(int yelp = 0; yelp < testerSet.size();yelp++) {
                    cout << testerSet[yelp] << " ";
                }
                cout << endl << "current set: ";

                for (int kek = 0; kek < current_set_of_features.size();kek++)
                {
                    cout << current_set_of_features[kek] << " ";
                }
                cout << endl;
                
                accuracy = leaveOneOut(data,testerSet);
                cout << "Accuracy: " << accuracy << endl;
                if(accuracy > bestAccuracy) 
                {
                    cout << "time to update best: " << accuracy << endl;
                    bestAccuracy = accuracy;
                    goodFeature = j;
                    if(bestAccuracy > bestestAccuracy) {
                        master_list = current_set_of_features;
                    }
                }
            }
        }
        current_set_of_features.push_back(goodFeature);
        testerSet.clear();
        if (bestestAccuracy < bestAccuracy) 
        {
            bestestAccuracy = bestAccuracy;
            //master_list.clear();
            master_list = current_set_of_features;
        }
        cout << "$##################################pushing goodFeature: " << goodFeature << endl;
        
        cout << "On level " << i+1 << " I added feature " << goodFeature << " to current set" << endl;
        cout << "The best accuracy is: " << bestestAccuracy << endl;
        cout << "Pure Set: ";
        for(int pure = 0; pure < current_set_of_features.size();pure++) {
            if (pure != current_set_of_features.size()-1) {
                cout << current_set_of_features[pure] << " ";
            }
            else {
                cout << current_set_of_features[pure] << endl;
            }
        }
        cout << "Master List: " << endl;
        for(int curr = 0; curr < master_list.size(); curr++) {
            cout << master_list[curr] << " " << endl;
        }
    }
    //cout << "Line count: " << count << endl;
    return;
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
    forward_search(data);
}



    // for(int i = 0; i < data.size(); i++) { // choose rows to initiate the rows
    //     for(int l = 1; l < data[i].size(); l++) { //add each feature to the comparison list
    //         checkup.push_back(data[i][l]);
    //     }
    //     for(int j = 0; j < data.size();j++) { // go through all the rows 
    //         // for(int k = 0; k < data[j].size();k++) { // go through each feature of compared rows

    //         // }
    //         if (i != j) {
    //             for(int m = 0; m < data[j].size(); m++) {
    //                 cout << data[j][m] << ' ';
    //             }
                
    //         }

    //     }
    //     cout << endl;
    // }