#include "Utils.h"

time_t parseTime(const std::string& timeStr) {
    tm time = {};
    std::istringstream ss(timeStr);
    ss >> std::get_time(&time, "%H:%M");
    return mktime(&time);
}

std::string formatTime(time_t _time) {
    tm* time = localtime(&_time);
    std::ostringstream ss;
    ss << std::put_time(time, "%H:%M");
    return ss.str();
}

std::string formatTimeDuration(time_t _time) {
    size_t hours = _time / 3600;
    size_t minutes = (_time % 3600) / 60;
    std::ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes;
    return ss.str();
}

size_t calculateProfitFromDuration(int hourlyRate, time_t startTime, time_t endTime) {
    time_t duration = endTime - startTime;

    size_t profit = duration / 3600 * hourlyRate;
    if ((duration % 3600) / 60 > 0) {
        profit += hourlyRate;
    }

    return profit;
}