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
                for(int k = 0; k < goodSet.size(); k++) 
                {
                    cDistance += pow((test[i][goodSet[k]] - test[j][goodSet[k]]),2);
                }
                cDistance = sqrt(cDistance);
                if(cDistance <= bestDist) 
                {
                    bestDist = cDistance;
                    bestLoc = j;
                }
            }
        }
        if(test[i][0] == test[bestLoc][0]) {
            counter = counter + 1;
        }
    }
    //cout << "Test size is: " << test.size() << endl;
    cout << "Count is: " << counter << endl;
    total = (double(counter) / double(test.size()));
    cout << "total is: " << total << endl;
    return total;
}
vector<int> current_set_of_features;
vector<int> testerSet;
vector<int> feature_to_add;
vector<int> master_list;
double bestAccuracy = 0.0;
double accuracy = 0.0;
double bestestAccuracy = 0.0;
int goodFeature = 0;
void forward_search(vector<vector<double>> data) {
    cout << "This is feature size: " << data[0].size()-1 << endl;
    cout << "Data size: " << data.size() << endl;
    master_list.clear();
    for(int i = 1; i < data[0].size(); i++) 
    { // starting from 1, # of features is 10
        cout << "On the " << i  << "th level of the search tree " << endl;
        feature_to_add.clear();
        testerSet.clear();
        bestAccuracy = 0.0;
        for(int j = 1; j < data[0].size(); j++) 
        {
            if(!(find(current_set_of_features.begin(),current_set_of_features.end(),j) != current_set_of_features.end())) 
            { // Consider if it does not exist
                cout << "--Considering adding the " << j << " feature" << endl;
                testerSet = current_set_of_features;
                testerSet.push_back(j);
                cout << "Tester Set: ";
                for(int yelp = 0; yelp < testerSet.size();yelp++) { // output tester set
                    cout << testerSet[yelp] << " ";
                }
                cout << endl << "current set: ";

                for (int kek = 0; kek < current_set_of_features.size();kek++) // output current set of features 
                {
                    cout << current_set_of_features[kek] << " ";
                }
                cout << endl;
                
                accuracy = leaveOneOut(data,testerSet);
                cout << "Accuracy: " << accuracy << endl; // output the leave one out accuracy 
                if(accuracy > bestAccuracy) // check if to update accuracy
                {
                    cout << "time to update best: " << accuracy << endl; 
                    bestAccuracy = accuracy;
                    goodFeature = j;
                    // if(bestAccuracy > bestestAccuracy) {
                    //     master_list = current_set_of_features;
                    // }
                }
            }
        }
        current_set_of_features.push_back(goodFeature);
        testerSet.clear();
        if (bestestAccuracy < bestAccuracy) 
        {
            bestestAccuracy = bestAccuracy;
            master_list = current_set_of_features;
        }
        cout << "pushing goodFeature: " << goodFeature << endl;
        
        cout << "On level " << i << " I added feature " << goodFeature << " to current set" << endl;
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

double worstAccuracy,badAccuracy;
vector<int> feature_to_remove;
int badFeature = 0;

void backward_search (vector<vector<double>> bork) 
{
    worstAccuracy = 0.0;
    bestestAccuracy = 0.0;
    for(int po = 1; po < bork[0].size(); po++)
    {
        current_set_of_features.push_back(po);
        //cout << po << " ";
    }
    //cout << endl;
    cout << "Bork size: " << bork[0].size() << endl;
    for(int i = bork[0].size()-1; i > 0; i--) 
    {
        cout << "On the " << i << "th level of the search tree" << endl;
        feature_to_add.clear();
        worstAccuracy = 100.0;
        bestAccuracy = 0.0;
        testerSet.clear();
        for(int j = 1; j < bork[0].size();j++) 
        {
            if((find(current_set_of_features.begin(),current_set_of_features.end(),j) != current_set_of_features.end())) 
            {
                cout << "--Considering removing the " << j << " feature" << endl;
                testerSet = current_set_of_features;
                testerSet.erase(remove(testerSet.begin(),testerSet.end(),j), testerSet.end());
                cout << "Tester Set: ";
                for(int yelp = 0; yelp < testerSet.size();yelp++) { // output tester set
                    cout << testerSet[yelp] << " ";
                }
                cout << endl << "current set: ";
                for (int kek = 0; kek < current_set_of_features.size();kek++) // output current set of features 
                {
                    cout << current_set_of_features[kek] << " ";
                }
                cout << endl;
                accuracy = leaveOneOut(bork,testerSet);
                cout << "Accuracy: " << accuracy << endl;
                if(accuracy > bestAccuracy)
                {
                    cout << "time to update best: " << accuracy << endl;
                    bestAccuracy = accuracy;
                    badFeature = j;
                }
                // if(accuracy > badAccuracy) 
                // {
                //     badAccuracy = accuracy;
                //     badFeature = j;
                // }
            }
        }
        current_set_of_features.erase(remove(current_set_of_features.begin(),current_set_of_features.end(),badFeature),current_set_of_features.end());
        //cout <<"current features: ";
        testerSet.clear();
        if(bestestAccuracy < bestAccuracy)
        {
            bestestAccuracy = accuracy;
            master_list = current_set_of_features;
        }
        cout << "Removing badFeature: " << badFeature << endl;

        cout << "On level " << i << " I removed feature " << badFeature << " from current set." << endl;
        cout << "The best accuracy is: " << bestestAccuracy << endl;
        cout << "Current Set: ";
        for(int master = 0; master < current_set_of_features.size();master++) {
            if (master != current_set_of_features.size()-1) {
                cout << current_set_of_features[master] << " ";
            }
            else {
                cout << current_set_of_features[master] << endl;
            }
        }
        cout << "Master List: " << endl;
        for(int curr = 0; curr < master_list.size(); curr++) {
            cout << master_list[curr] << " ";
        }
    }
    return;
}

void custom_search(vector<vector<double>> troop) {
    return;
}
void parse_data() {
    vector<vector<double>> data; // stores all data sets
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
    cout << endl;
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
    //forward_search(data);
    backward_search(data);
}
