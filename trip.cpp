//Implementation File - This file will contain the actual function definitions.

#include "trip.h"
#include <iostream>
#include <regex>
#include <fstream>
#include <iomanip>

using namespace std;

// Function to validate date format
bool validateDate(const string& date) {
    regex datePattern(R"((\d{2})/(\d{2})/(\d{4}))");
    smatch match;

    if (!regex_match(date, match, datePattern)) {
        return false;
    }

    int day = stoi(match[1].str());
    int month = stoi(match[2].str());
    int year = stoi(match[3].str());

    cout << "Day: " << day << ", Month: " << month << ", Year: " << year << endl;

    if (month < 1 || month > 12) {
        return false;
    }

    bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    int daysInMonth[] = { 31, (isLeapYear ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return (day >= 1 && day <= daysInMonth[month - 1]);
}

// Function to validate budget
bool validateBudget(double budget) {
    return budget > 0;
}

// Function to trim whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to load trips from file
void loadTrips(vector<tuple<string, string, double>>& trips) {
    ifstream inFile("trips.txt");
    if (inFile) {
        string destination, travelDate;
        double budget;
        while (inFile >> ws && getline(inFile, destination) &&
            getline(inFile, travelDate) && (inFile >> budget)) {
            trips.push_back(make_tuple(destination, travelDate, budget));
            inFile.ignore();
        }
        inFile.close();
    }
}

// Function to save trips to file
void saveTrips(const vector<tuple<string, string, double>>& trips) {
    ofstream outFile("trips.txt");
    for (const auto& trip : trips) {
        outFile << get<0>(trip) << endl;
        outFile << get<1>(trip) << endl;
        outFile << get<2>(trip) << endl;
    }
    outFile.close();
}
