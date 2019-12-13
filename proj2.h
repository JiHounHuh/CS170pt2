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
int bestCounter = 100;
int errCounter = 0;
vector<double> allBest;
double leaveOneOut(vector<vector<double>> test, vector<int>goodSet, bool customCheck) 
{
    errCounter = 0;
    counter = 0;
    total = 0.0;
    //cout << "Size of GoodSet= " << goodSet.size() << endl;
    for(int i = 0; i < test.size(); i++) 
    { // get row
        bestDist = 99999.9999;
        bestLoc = -1;
        for(int j = 0; j < test.size(); j++) 
        { // get row 
            cDistance = 0.0;
            if(i != j) 
            {
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
        else
        {
            if(customCheck)
            {
                errCounter = errCounter + 1;
                if(bestCounter < errCounter)
                {
                    return 0.0;
                }
            }
        }
    }
    total = (double(counter) / double(test.size()));
    bestCounter = test.size() - counter;
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
                accuracy = leaveOneOut(data,testerSet,false);
               // cout << "Accuracy: " << accuracy << endl; // output the leave one out accuracy 
                if(accuracy > bestAccuracy) // check if to update accuracy
                {
                   // cout << "time to update best: " << accuracy << endl; 
                    bestAccuracy = accuracy;
                    goodFeature = j;
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
        cout << "The best accuracy is: " << bestestAccuracy * 100 << '%' << endl;
        allBest.push_back(bestAccuracy * 100); // grabs bestest Accuracies per feature
    }
    cout << "Finished search!! The best feature subset is {";
    for(int curr = 0; curr < master_list.size(); curr++) {
        if(curr != master_list.size()-1) {
            cout << master_list[curr] << ", ";
        }
        else {
            cout << master_list[curr] << "}, ";
        }
    }
    cout << "which has an accuracy of " << bestestAccuracy * 100 << '%' << endl;
    cout << "List of Bestest Accuracies: { ";
    for(int alpha = 0; alpha < allBest.size(); alpha++) {
        if(alpha != allBest.size()-1) {
            cout << '[' << alpha+1 << ", " << allBest[alpha] << "], ";
        }
        else {
            cout << '[' << alpha+1 << ", " << allBest[alpha] << "] }, ";
        }
    }
    return;
}

double badAccuracy;
vector<int> feature_to_remove;
int badFeature = 0;

void backward_search (vector<vector<double>> bork) {
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
        bestAccuracy = 0.0;
        testerSet.clear();
        for(int j = 1; j < bork[0].size();j++) 
        {
            if((find(current_set_of_features.begin(),current_set_of_features.end(),j) != current_set_of_features.end())) 
            {
                cout << "--Considering removing the " << j << " feature" << endl;
                testerSet = current_set_of_features;
                testerSet.erase(remove(testerSet.begin(),testerSet.end(),j), testerSet.end());
                accuracy = leaveOneOut(bork,testerSet,false);
                if(accuracy > bestAccuracy)
                {
                    bestAccuracy = accuracy;
                    badFeature = j;
                }
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
        cout << "The best accuracy is: " << bestestAccuracy * 100 << '%' << endl;
        allBest.push_back(bestAccuracy * 100); // grabs bestest Accuracies per feature
    }
    cout << "Finished search!! The best feature subset is {";
    for(int curr = 0; curr < master_list.size(); curr++) {
        if(curr != master_list.size()-1) {
            cout << master_list[curr] << ", ";
        }
        else {
            cout << master_list[curr] << "}, ";
        }
    }
    cout << "which has an accuracy of " << bestestAccuracy * 100 << '%' << endl;
    cout << "List of Bestest Accuracies: { ";
    for(int alpha = 0; alpha < allBest.size(); alpha++) {
        if(alpha != allBest.size()-1) {
            cout << '[' << alpha+1 << ", " << allBest[alpha] << "], ";
        }
        else {
            cout << '[' << alpha+1 << ", " << allBest[alpha] << "] }, ";
        }
    }
    return;
}

int count,bestCount;
void custom_search(vector<vector<double>> troop) {
    bestCount = 0;
    cout << "This is feature size: " << troop[0].size()-1 << endl;
    cout << "Data size: " << troop.size() << endl;
    master_list.clear();
    for(int i = 1; i < troop[0].size(); i++) 
    { // starting from 1, # of features is 10
        cout << "On the " << i  << "th level of the search tree " << endl;
        feature_to_add.clear();
        testerSet.clear();
        bestAccuracy = 0.0;
        for(int j = 1; j < troop[0].size(); j++) 
        {
            if(!(find(current_set_of_features.begin(),current_set_of_features.end(),j) != current_set_of_features.end())) 
            { // Consider if it does not exist
                cout << "--Considering adding the " << j << " feature" << endl;
                testerSet = current_set_of_features;
                testerSet.push_back(j);
                accuracy = leaveOneOut(troop,testerSet,true);
                if(accuracy > bestAccuracy) // check if to update accuracy
                {
                    bestAccuracy = accuracy;
                    goodFeature = j;
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
        bestCounter = 100;
        cout << "On level " << i << " I added feature " << goodFeature << " to current set" << endl;
        cout << "The best accuracy is: " << bestestAccuracy * 100 << '%' << endl;
        allBest.push_back(bestAccuracy * 100); // grabs bestest Accuracies per feature
    }
    cout << "Finished search!! The best feature subset is {";
    for(int curr = 0; curr < master_list.size(); curr++) {
        if(curr != master_list.size()-1) {
            cout << master_list[curr] << ", ";
        }
        else {
            cout << master_list[curr] << "}, ";
        }
    }
    cout << "which has an accuracy of " << bestestAccuracy * 100 << '%' << endl;
    cout << "List of Bestest Accuracies: { ";
    for(int alpha = 0; alpha < allBest.size(); alpha++) {
        if(alpha != allBest.size()-1) {
            cout << '[' << alpha+1 << ", " << allBest[alpha] << "], ";
        }
        else {
            cout << '[' << alpha+1 << ", " << allBest[alpha] << "] }, ";
        }
    }
}
void parse_data() 
{
    vector<vector<double>> data; // stores all data sets
    vector<double> temp;
    vector<double> checkup;
    double lowestVal = 0.0;
    double value = 0.0;
    double checkVal = 0.0;
    int a;
    int feature = 0;
    string tempLine;
    string file;
    cout << "Welcome to Ji Houn Huh's Feature Selection Algorithm." << endl;
    cout << "Type in the name of the file to test: "; // prompt for input of data
    cin >> file;
    cout << endl << endl;
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
    }
    inFile.close();
    cout << "Type the number of the algorithm you want to run." << endl;
    cout << "   1) Forward Selection"<<endl;
    cout << "   2) Backward Elimination" << endl;
    cout << "   3) Ji Houn's Special Algorithm." << endl;
    cin >> a;
    switch (a)
    {
        case 1: 
            forward_search(data);
            break;
        case 2:
            backward_search(data);
            break;
        case 3: 
            custom_search(data);
            break;
    }
}
