#ifndef TRIP_H
#define TRIP_H

#include <string>
#include <vector>
#include <tuple>

// Class to represent a single trip
class Trip {
private:
    std::string destination;
    std::string travelDate;
    double budget;

public:
    // Constructors
    Trip() = default;
    Trip(const std::string& destination, const std::string& travelDate, double budget);

    // Getters
    std::string getDestination() const;
    std::string getTravelDate() const;
    double getBudget() const;

    // Methods to display and manage trip
    void displayTripDetails() const;

    // Static method to display all trips
    static void displayAllTrips(const std::vector<Trip>& trips);
};

#endif
