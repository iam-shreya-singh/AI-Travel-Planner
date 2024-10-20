
//This file will contain the declarations for functions related to trips and some utility functions

#ifndef TRIP_H
#define TRIP_H

#include <string>
#include <vector>
#include <tuple>

using namespace std;

// Function declarations
bool validateDate(const string& date);
bool validateBudget(double budget);
string trim(const string& str);

void loadTrips(vector<tuple<string, string, double>>& trips);
void saveTrips(const vector<tuple<string, string, double>>& trips);

#endif // TRIP_H
