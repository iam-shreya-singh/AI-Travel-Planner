#include <iostream>
#include <string>
#include <regex>                  //for date validations DD/MM/YYYY format
using namespace std;


// function to validate date format
      bool validateDate (const string& date){
      regex datePattern ("\\d{2}/\\d{2}/\\d{4}");
          return regex_match(date, datePattern);
      }

//function to validate Budget format 
      bool validateBudget (double Budget){
          return Budget > 0;
      }

int main() {       
   
    //taking user info like destination,travel dates and Budgets using std input
    string destination;
    string travelDate;
    double budget;

    cout << "Welcome to the AI Travel Planner Project, WIP, stay-tuned !" << endl;  //Intro line for user

    cout << "Enter your Travel Destination: "; //take travel destination input
    getline(cin, destination);                //getline helps in accepting multi-line input 
    

    //input and validate travel date
    bool validDate = false;
    do {
        cout << "Enter your travel dates in format DD/MM/YYYY: "; //take travel date input
        getline(cin, travelDate);
        if (!validateDate(travelDate)) {
            cout << "Invalid date format! Please enter the date in format DD/MM/YYYY ";
            }
        else {
            validDate = true;
        }
    } while (!validDate);


    //input and validate Budget 
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
    
    //Display user input after doing above validations of date and budget
    cout << "Hurray! You are planning to travel to " << destination  // displaying above user input or information collected on output screen to user
        << " on " << travelDate
        << " with a Budget of INR." << budget << "." << endl;

cout << "Press Enter to exit...";       //Waits for the user to hit enter before exiting
cin.ignore();                           //Clears input buffer
cin.get();                              //Waits for Enter key

return 0;
}




