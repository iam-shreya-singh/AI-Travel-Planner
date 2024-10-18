#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <regex>
#include <fstream>
#include <iomanip>    // Allows control of how data is displayed

using namespace std;

// Function to validate date format, extract day, month, and year
bool validateDate(const string& date) {
    regex datePattern(R"((\d{2})/(\d{2})/(\d{4}))");  // Regex pattern to extract day, month, year
    smatch match;

    if (!regex_match(date, match, datePattern)) {   // Check if input matches the pattern
        return false;  // Invalid format
    }

    // Convert the strings into integers (day, month, year)
    int day = stoi(match[1].str());
    int month = stoi(match[2].str());
    int year = stoi(match[3].str());

    cout << "Day: " << day << ", Month: " << month << ", Year: " << year << endl;

    // Check if the month is valid
    if (month < 1 || month > 12) {
        return false;  // Invalid month
    }

    // Check if the day is valid based on month and year
    bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    int daysInMonth[] = { 31, (isLeapYear ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // Days per month

    if (day < 1 || day > daysInMonth[month - 1]) {
        return false; // Invalid day for the given month
    }

    return true; // Date is valid
}

// Function to validate budget (positive number)
bool validateBudget(double budget) {
    return budget > 0;
}

// Function to trim leading and trailing whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to read trips data from trips.txt file
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

// Function to save trip data to trips.txt file
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

    vector<tuple<string, string, double>> trips;   // Vector to store multiple trip details
    string destination, travelDate;
    double budget;
    char addMore;

    // Load previously saved trips
    loadTrips(trips);
    cout << "Welcome to the AI Travel Planner Project, WIP, stay-tuned!" << endl;

    // Display previously loaded trips (if any)
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
        // Clear buffer before taking input for destination
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Take travel destination input
        cout << "\nEnter your Travel Destination: ";
        getline(cin, destination);  // Get the destination name (supports spaces)

        // Input and validate travel date
        bool validDate = false;
        do {
            cout << "Enter your travel date in format DD/MM/YYYY: ";
            getline(cin, travelDate);
            if (!validateDate(travelDate)) {
                cout << "Invalid date format! Please enter the date in format DD/MM/YYYY." << endl;
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

            // Clear the buffer to ensure no leftover characters interfere with the next input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!validateBudget(budget)) {
                cout << "Invalid budget! Please enter a positive value." << endl;
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
        cout << "Are these details correct? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            // Store the trip details
            trips.push_back(make_tuple(destination, travelDate, budget));

            // Display summary of the newly added trip
            cout << "\nHurray! You are planning to travel to " << destination
                << " on " << travelDate << " with a Budget of INR " << budget << "." << endl;
        }
        else {
            cout << "Let's re-enter the trip details.\n";
        }

        // Ask if the user wants to add another trip
        cout << "Do you want to add another trip? (y/n): ";
        cin >> addMore;

    } while (addMore == 'y' || addMore == 'Y');

    cout << "\nSummary of Your Planned Trips\n"; // Display a summary of all trips
    for (size_t i = 0; i < trips.size(); ++i) {
        cout << "Trip " << (i + 1) << ": "
            << "Destination: " << get<0>(trips[i]) << ", "
            << "Date: " << get<1>(trips[i]) << ", "
            << "Budget: INR " << get<2>(trips[i]) << endl;
    }

    // Save trips to file before exiting
    saveTrips(trips);

    // Wait for the user to press Enter before exiting
    cout << "\nPress Enter to exit...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer fully
    cin.get();  // Wait for Enter key

    return 0;
}
