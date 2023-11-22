#include <iostream>
#include <ctime>
#include <string>
#include <unordered_map>

void numToMonthAndDay(unsigned num, unsigned & m, unsigned & d) {
    if (num < 31) {
        m = 1;
        return;
    }
    if (num < 59) {
        m = 2;
        d -= 31;
        return;
    }
    if (num < 90) {
        m = 3;
        d -= 59;
        return;
    }
    if (num < 120) {
        m = 4;
        d -= 90;
        return;
    }
    if (num < 151) {
        m = 5;
        d -= 120;
        return;
    }
    if (num < 181) {
        m = 6;
        d -= 151;
        return;
    }
    if (num < 212) {
        m = 7;
        d -= 181;
        return;
    }
    if (num < 243) {
        m = 8;
        d -= 212;
    }
    if (num < 273) {
        m = 9;
        d -= 243;
        return;
    }
    if (num < 304) {
        m = 10;
        d -= 273;
        return;
    }
    if (num < 334) {
        m = 11;
        d -= 304;
        return;
    }
    else {
        m = 12;
        d -= 334;
        return;
    }
}

void assignTime(unsigned unix, unsigned & m, unsigned & d, unsigned & y, unsigned & h, unsigned & min, unsigned & s) {
    s = unix % 60;
    min = (unix / 60) % 60;
    h = (unix / 3600) % 24;
    unsigned daysSinceUnix = (unix / 86400);
    y = 0;
    m = 0;
    d;
    unsigned daysSinceYearStart = 0;
    if (daysSinceUnix < 365) {
        daysSinceYearStart = daysSinceUnix;
        y = 1970;
    }
    else if (daysSinceUnix < 730) {
        daysSinceYearStart = daysSinceUnix - 365;
        y = 1971;
    }
    else if (daysSinceUnix < 1096) {
        daysSinceYearStart = daysSinceUnix - 730;
        y = 1972;
    }
    else {
        daysSinceYearStart = daysSinceUnix - 1096;
        y = 1973;
        daysSinceYearStart -= 1461 * ((daysSinceUnix - 1096) / 1461); 
        y += 4 * ((daysSinceUnix - 1096) / 1461);
        daysSinceYearStart -= 365 * (((daysSinceUnix - 1096) % 1461) / 365);
        y += ((daysSinceUnix - 1096) % 1461) / 365;
    }
    d = daysSinceYearStart + 1;
    if (daysSinceYearStart < 59 || y % 4 != 0) {
        numToMonthAndDay(daysSinceYearStart, m, d);
    }
    else {
        if (daysSinceYearStart == 59) {
            m = 2;
            d = 29;
        }
        else { 
            numToMonthAndDay(daysSinceYearStart - 1, m, d);
        }
    }
}

bool check(std::string input) {
    bool check = true;
    if (input.size() >= 5 && input[0] == 'U' && input[1] == 'T' && input[2] == 'C' && std::isdigit(input[4]) && (input[3] == '+' || input[3] == '-')) {
        if (input.size() == 5) {
            if (input[4] <= '9') {
                check = false;
            }
        }
        else if (input.size() == 6 && std::isdigit(input[5])) {
            if (input[4] == '1' && input[5] < '4') {
                        check = false;
            }
            else if (input[4] == '0' && input[5] < '9') {
                check = false;
            }
        }
        else if (input.size() == 8) {
            if (input[5] == ':' && std::isdigit(input[6]) && std::isdigit(input[7])) {
                if (input[4] <= '9' && input[6] <= '5' && input[7] <= '9') {
                    check = false;
                }
            }
        }
        else if (input.size() == 9) {
            if (input[6] == ':' && std::isdigit(input[5]) && std::isdigit(input[7]) && std::isdigit(input[8])) {
                if (input[4] == '1' && input[5] > '2' && input[3] == '-') {
                    //
                }
                else if ((input[4] == '1' && input[5] < '4') || (input[4] == '0' && input[5] < '9')) {
                    if (input[6] <= '5' && input[7] <= '9') {
                        check = false;
                    }
                }
            }
        }
    }
    return check;
}
int main() {
    unsigned currentTime;
    unsigned seconds;
    unsigned minutes;
    unsigned hours;
    unsigned year;
    unsigned month;
    unsigned day;
    int numToChange = 0;
    std::string yesNo;
    std::cout << "Currently using UTC. Would you like to adjust to a different time zone? y/n\n";
    std::cin >> yesNo;
    for (unsigned i = 0; i < yesNo.size(); i++) {
        yesNo[i] = std::tolower(yesNo[i]);
    }
    while (yesNo != "y" && yesNo != "yes" && yesNo != "n" && yesNo != "no") {
        std::cout << "Invalid input. Please respond with y/n" << std::endl;
        std::cin >> yesNo;
        for (unsigned i = 0; i < yesNo.size(); i++) {
            yesNo[i] = std::tolower(yesNo[i]);
        }
    }
    if (yesNo[0] == 'y') {
        std::cout << "Please input your desired timezone in the form \"UTC+HH:MM\" or \"UTC-HH:MM\":\n";
        std::string input;
        std::cin >> input;
        for (unsigned i = 0; i < input.size(); i++) {
            input[i] = std::toupper(input[i]);
        }
        while (check(input)) {
            std::cout << "Invalid input. Please respond with a valid timezone in the form \"UTC+HH:MM\" or \"UTC-HH:MM\":\n";
            std::cin >> input;
            for (unsigned i = 0; i < input.size(); i++) {
                input[i] = std::toupper(input[i]);
            }
        }
        if (input.size() == 5) {
            numToChange = std::stoi(input.substr(3, 2)) * 3600;
        }
        else if (input.size() == 6) {
            numToChange = std::stoi(input.substr(3, 3)) * 3600;
        }
        else if (input.size() == 8) {
            numToChange = std::stoi(input.substr(3, 2)) * 3600;
            if (input[3] == '+') {
                numToChange += std::stoi(input.substr(6,2)) * 60;
            }
            else {
                numToChange -= std::stoi(input.substr(6,2)) * 60;
            }
        }
        else if (input.size() == 9) {
            numToChange = std::stoi(input.substr(3, 3)) * 3600;
            if (input[3] == '+') {
                numToChange += std::stoi(input.substr(7,2)) * 60;
            }
            else {
                numToChange -= std::stoi(input.substr(7,2)) * 60;
            }
        }
    }
    std::cout << "Currently using MM/DD/YYYY format. Would you like to change to DD/MM/YYYY format? y/n\n";
    std::string dmYesNo;
    std::cin >> dmYesNo;
    for (unsigned i = 0; i < yesNo.size(); i++) {
        dmYesNo[i] = std::tolower(dmYesNo[i]);
    }
    while (dmYesNo != "y" && dmYesNo != "yes" && dmYesNo != "n" && dmYesNo != "no") {
        std::cout << "Invalid input. Please respond with y/n" << std::endl;
        std::cin >> dmYesNo;
        for (unsigned i = 0; i < dmYesNo.size(); i++) {
            dmYesNo[i] = std::tolower(dmYesNo[i]);
        }
    }
    std::cout << "Currently using 24-hour format. Would you like to change to 12-hour? y/n\n";
    std::string hrYesNo;
    std::cin >> hrYesNo;
    for (unsigned i = 0; i < hrYesNo.size(); i++) {
        hrYesNo[i] = std::tolower(hrYesNo[i]);
    }
    while (hrYesNo != "y" && hrYesNo != "yes" && hrYesNo != "n" && hrYesNo != "no") {
        std::cout << "Invalid input. Please respond with y/n" << std::endl;
        std::cin >> hrYesNo;
        for (unsigned i = 0; i < hrYesNo.size(); i++) {
            hrYesNo[i] = std::tolower(hrYesNo[i]);
        }
    }
    currentTime = std::time(nullptr);
    currentTime += numToChange;
    assignTime(currentTime, month, day, year, hours, minutes, seconds);
    char marker[4] = {'\0', '\0', '\0', '\0'};
    if (hrYesNo[0] == 'y') {
        marker[0] = ' ';
        marker[1] = 'A';
        marker[2] = 'M';
        if (hours == 0) {
            hours -= 12;
        }
        else if (hours >= 12) {
            marker[1] = 'P';
            if (hours > 12) {
                hours -= 12;
            }
        }
    }
    if (dmYesNo[0] == 'y') {
        unsigned temp = month;
        month = day;
        day = temp;
    }
    std::cout << "Current date and time:\n";
    std::printf("%02d/%02d/%02d %02d:%02d:%02d%s\n", month, day, year, hours, minutes, seconds, marker);
    return 0;
}