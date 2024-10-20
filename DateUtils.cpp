#include "DateUtils.h"
#include <regex>
#include <iostream>

bool validateDate(const std::string& date) {
    std::regex datePattern(R"((\d{2})/(\d{2})/(\d{4}))");
    std::smatch match;

    if (!std::regex_match(date, match, datePattern)) {
        return false;
    }

    int day = std::stoi(match[1].str());
    int month = std::stoi(match[2].str());
    int year = std::stoi(match[3].str());

    // Leap year check and month validation
    bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    int daysInMonth[] = { 31, (isLeapYear ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return month >= 1 && month <= 12 && day >= 1 && day <= daysInMonth[month - 1];
}
