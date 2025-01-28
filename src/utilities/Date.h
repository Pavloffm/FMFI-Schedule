#pragma once
#include <string>

const int CURRENT_YEAR = 2025;
const int MAX_YEAR_OFFSET = 10;

const std::string MonthNames[12] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

const int MonthDays[12] = {
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31,
};


class Date {
private:
    int year, month, day, hour, minute, second;
public:
    Date();
    Date(int year, int month, int day, int hour, int minute, int second);

    std::string ToString();
    void putDate(int year0, int month0, int day0, int hour0, int minute0, int second0);

    int getYear() const { return year; };
    int getMonth() const { return month; };
    int getDay() const { return day; };
    int getHour() const { return hour; };
    int getMinute() const { return minute; };
    int getSecond() const { return second; };

    bool operator==(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
};
