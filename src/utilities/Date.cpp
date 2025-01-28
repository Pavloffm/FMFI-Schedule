#include "Date.h"

#include <stdexcept>
#include <iomanip>
#include <sstream>

Date::Date() : year(0), month(0), day(0), hour(0), minute(0), second(0) {}

Date::Date(int year, int month, int day, int hour, int minute, int second) {
    putDate(year, month, day, hour, minute, second);
}


std::string Date::ToString() {
    std::ostringstream oss;

    oss << std::setw(4) << std::setfill('0') << year << "-"
        << std::setw(2) << std::setfill('0') << month << "-"
        << std::setw(2) << std::setfill('0') << day << " "
        << std::setw(2) << std::setfill('0') << hour << ":"
        << std::setw(2) << std::setfill('0') << minute << ":"
        << std::setw(2) << std::setfill('0') << second;

    return oss.str();
}

void Date::putDate(int year0, int month0, int day0, int hour0, int minute0, int second0) {
    if (year0 < CURRENT_YEAR || year0 > CURRENT_YEAR + MAX_YEAR_OFFSET) throw std::invalid_argument("Year out of limits");

    if (month0 < 1 || month0 > 12) throw std::invalid_argument("Month out of limits");

    int maxDays = MonthDays[month0 - 1];
    if (month0 == 2 && ((year0 % 4 == 0 && year0 % 100 != 0) || (year0 % 400 == 0))) ++maxDays;

    if (1 > day0 || day0 > maxDays) throw std::invalid_argument("Day out of limits");

    if (0 > hour0 || hour0 > 23) throw std::invalid_argument("Hour out of limits");
    if (0 > minute0 || minute0 > 59) throw std::invalid_argument("Minute out of limits");
    if (0 > second0 || second0 > 59) throw std::invalid_argument("Second out of limits");

    year = year0, month = month0, day = day0, hour = hour0, minute = minute0, second = second0;
}

bool Date::operator==(const Date& other) const {
    return year == other.year &&
           month == other.month &&
           day == other.day &&
           hour == other.hour &&
           minute == other.minute &&
           second == other.second;
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    if (day != other.day) return day < other.day;
    if (hour != other.hour) return hour < other.hour;
    if (minute != other.minute) return minute < other.minute;
    return second < other.second;
}

bool Date::operator>(const Date& other) const { return !(*this < other) && !(*this == other); }


