//Handle file operations for reading and writing trip data.

#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <vector>
#include <tuple>
#include <string>

void loadTrips(std::vector<std::tuple<std::string, std::string, double>>& trips);
void saveTrips(const std::vector<std::tuple<std::string, std::string, double>>& trips);

#endif