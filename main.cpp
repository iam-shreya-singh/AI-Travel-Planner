#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <regex>
#include <fstream>

using namespace std;

// function to validate date format
bool validateDate(const string& date) {
    regex datePattern("\\d{2}/\\d{2}/\\d{4}");
    return regex_match(date, datePattern);
}

// Function to validate budget (positive number)
bool validateBudget(double budget) {
    return budget > 0;
}

//Function to read trips data from trips.txt file
void loadTrips(vector<tuple<string, string, double>>& trips) {
    ifstream inFile("trips.txt");
    if (inFile) {
        string destination, travelDate;
        double budget;
        while (inFile >> ws && getline(inFile, destination) &&
            getline(inFile, travelDate) &&
            (inFile >> budget)) {
            trips.push_back(make_tuple(destination, travelDate, budget));
            inFile.ignore();  // Ignore the newline after budget
        }
        inFile.close();
    }
}

//Function to save trip data to trips.txt file
void saveTrips(const vector<tuple<string, string, double>>& trips) {
    ofstream outFile("trips.txt");
    for (const auto& trip : trips) {
        outFile << get<0>(trip) << endl;
        outFile << get<1>(trip) << endl;
        outFile << get<2>(trip) << endl;
    }
    outFile.close();
}

int main() {


    vector <tuple<string, string, double>> trips;   // Vector to store multiple trip details
    //taking user info like destination,travel dates and Budgets using std input
    string destination, travelDate;
    double budget;
    char addMore;

    //Load previously saved trips
    loadTrips(trips);
    cout << "Welcome to the AI Travel Planner Project, WIP, stay-tuned !" << endl;  //Intro line for user

    // Display previously loaded trips if any
    if (!trips.empty()) {
        cout << "\nPreviously Saved Trips:\n";
        for (size_t i = 0; i < trips.size(); i++) {
            cout << "Trip " << (i + 1) << ": "
                << "Destination: " << get<0>(trips[i]) << ", "
                << "Date: " << get<1>(trips[i]) << ", "
                << "Budget: INR " << get<2>(trips[i]) << endl;
        }
    }

    do {
        //take travel destination input
        cout << "Enter your Travel Destination: ";
        cin.ignore();                              // clears the input buffer preventing issues with getline
        getline(cin, destination);                //getline helps in accepting multi-line input 

        //input and validate travel date
        bool validDate = false;
        do {
            cout << "Enter your travel dates in format DD/MM/YYYY: "; //take travel date input
            getline(cin, travelDate);
            if (!validateDate(travelDate)) {
                cout << "Invalid date format! Please enter the date in format DD/MM/YYYY." << endl;;
            }
            else {
                validDate = true;
            }
        } while (!validDate);


        //input and validate budget 
        bool validBudget = false;
        do {
            cout << "Enter your Budget (in INR): ";  // take Budget input in INR
            cin >> budget;
            if (!validateBudget(budget)) {
                cout << "Invalid budget! Please enter a positive value." << endl;

            }
            else {
                validBudget = true;
            }
        } while (!validBudget);

        // Store the trip details
        trips.push_back(make_tuple(destination, travelDate, budget));

        // Ask if user wants to add another trip
        cout << "Do you want to add another trip? (y/n): ";
        cin >> addMore;

    } while (addMore == 'y' || addMore == 'Y');

    // Display a summary of all trips
    cout << "\nSummary of Your Planned Trips:\n";
    for (size_t i = 0; i < trips.size(); ++i) {
        cout << "Trip " << (i + 1) << ": "
            << "Destination: " << get<0>(trips[i]) << ", "
            << "Date: " << get<1>(trips[i]) << ", "
            << "Budget: INR " << get<2>(trips[i]) << endl;
    }

    // Save trips to file before exiting
    saveTrips(trips);

    //Display user input after doing above validations of date and budget
    cout << "\nHurray! You are planning to travel to " << destination << " on " << travelDate << " with a Budget of INR " << budget << "." << endl;


    cout << "\nPress Enter to exit...";       //Waits for the user to hit enter before exiting
    cin.ignore();                           //Clears input buffer
    cin.get();                              //Waits for Enter key

    return 0;
}




