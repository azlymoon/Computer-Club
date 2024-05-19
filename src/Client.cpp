#include "Client.h"
#include <string>
#include <utility>
#include <stdexcept>

Client::Client(std::string name, time_t start_time) :
        name(std::move(name)), startTime(start_time), table(-1) {
}

int Client::getTable() const {
    return table;
}

std::string Client::getName() const {
    return name;
}

time_t Client::getStartTime() const {
    return startTime;
}

void Client::setName(std::string _name) {
    if (_name.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }
    name = std::move(_name);
}

void Client::setStartTime(time_t _startTime) {
    startTime = _startTime;
}

void Client::setTable(int _table) {
    if (_table <= 0) {
        throw std::invalid_argument("Table number cannot be negative");
    }
    table = _table;
}