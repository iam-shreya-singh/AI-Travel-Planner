#include <iostream>
#include <strings>
using namespace std;

int main() {       
   
                                    //taking user info like destination,travel dates and budgets using std input
    string destination;
    string travelDate;
    double budget;

    cout << "Welcome to the AI Travel Planner Project, WIP, stay-tuned !" << endl;  //Intro line for user

    cout << "Enter your Travel Destination: "; //take travel destination input
    getline(cin, destination);                //getline helps in accepting multi-line input 

    cout << "Enter your travel dates in format DD/MM/YYYY: "; //take travel date input
    getline(cin, travelDate);

    cout << "Enter your Budget (in INR): ";  // take budget input in INR
    cin >> budget;

    cout << "Hurray! You are planning to travel to " << destination  // displaying above user input or information collected on output screen to user
        << " on " << travelDate
        << " with a budget of INR." << budget << "." << endl;

return 0;
}




