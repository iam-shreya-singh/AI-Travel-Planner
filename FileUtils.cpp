//Handle file operations for reading and writing trip data.

#include "FileUtils.h"
#include <fstream>

void loadTrips(std::vector<std::tuple<std::string, std::string, double>>& trips) {
    std::ifstream inFile("trips.txt");
    if (inFile) {
        std::string destination, travelDate;
        double budget;
        while (inFile >> std::ws && std::getline(inFile, destination) &&
            std::getline(inFile, travelDate) &&
            (inFile >> budget)) {
            trips.push_back(std::make_tuple(destination, travelDate, budget));
            inFile.ignore();
        }
        inFile.close();
    }
}

void saveTrips(const std::vector<std::tuple<std::string, std::string, double>>& trips) {
    std::ofstream outFile("trips.txt");
    for (const auto& trip : trips) {
        outFile << std::get<0>(trip) << std::endl;
        outFile << std::get<1>(trip) << std::endl;
        outFile << std::get<2>(trip) << std::endl;
    }
    outFile.close();
}