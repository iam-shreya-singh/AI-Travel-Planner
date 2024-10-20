//main.cpp - Handles user interaction 
// and uses the modularized functions from trip.h, BudgetUtils.h, FileUtils.h, DateUtils.h

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <iomanip>

#include "DateUtils.h"
#include "BudgetUtils.h"
#include "FileUtils.h"

using namespace std;

int main() {
    vector<tuple<string, string, double>> trips;
    string destination, travelDate;
    double budget;
    char addMore;

    // Load previously saved trips
    loadTrips(trips);
    cout << "Welcome to the AI Travel Planner Project, WIP, stay-tuned!" << endl;

    // Display previously loaded trips
    if (!trips.empty()) {
        cout << "\nPreviously Saved Trips:\n";
        for (size_t i = 0; i < trips.size(); ++i) {
            cout << "Trip " << (i + 1) << ": "
                << "Destination: " << get<0>(trips[i]) << ", "
                << "Date: " << get<1>(trips[i]) << ", "
                << "Budget: INR " << get<2>(trips[i]) << endl;
        }
    }

    do {
        // Take input for destination
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter your Travel Destination: ";
        getline(cin, destination);

        // Input and validate travel date
        bool validDate = false;
        do {
            cout << "Enter your travel date in format DD/MM/YYYY: ";
            getline(cin, travelDate);
            if (!validateDate(travelDate)) {
                cout << "Invalid date format! Please try again.\n";
            }
            else {
                validDate = true;
            }
        } while (!validDate);

        // Input and validate budget
        bool validBudget = false;
        do {
            cout << "Enter your Budget (in INR): ";
            cin >> budget;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!validateBudget(budget)) {
                cout << "Invalid budget! Please enter a positive value.\n";
            }
            else {
                validBudget = true;
            }
        } while (!validBudget);

        // Confirm trip details before saving
        char confirm;
        cout << "\nPlease review your trip details:" << endl;
        cout << "Destination: " << destination << endl;
        cout << "Travel Date: " << travelDate << endl;
        cout << "Budget: INR " << fixed << setprecision(2) << budget << endl;

        char confirm;
        cout << "Are these details correct? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            trips.push_back(make_tuple(destination, travelDate, budget));
            cout << "\nTrip added successfully!" << endl;
        }

        cout << "Do you want to add another trip? (y/n): ";
        cin >> addMore;

    } while (addMore == 'y' || addMore == 'Y');

    cout << "\nSummary of Your Planned Trips\n";
    for (size_t i = 0; i < trips.size(); ++i) {
        cout << "Trip " << (i + 1) << ": "
            << "Destination: " << get<0>(trips[i]) << ", "
            << "Date: " << get<1>(trips[i]) << ", "
            << "Budget: INR " << get<2>(trips[i]) << endl;
    }

    saveTrips(trips);

    cout << "\nPress Enter to exit...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    return 0;
}
