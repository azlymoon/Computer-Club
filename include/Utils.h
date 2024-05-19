#ifndef COMPUTERCLUB_UTILS_H
#define COMPUTERCLUB_UTILS_H

#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>

time_t parseTime(const std::string& timeStr);
std::string formatTime(time_t _time);
std::string formatTimeDuration(time_t _time);
size_t calculateProfitFromDuration(int hourlyRate, time_t startTime, time_t endTime);

#endif //COMPUTERCLUB_UTILS_H
