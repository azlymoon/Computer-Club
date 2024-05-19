#include "events/ErrorEvent.h"

#include <utility>
#include "Utils.h"
#include <iostream>

ErrorEvent::ErrorEvent(int id, time_t time, std::string detail) :
        BaseEvent{id, time}, detail(std::move(detail)) {};

void ErrorEvent::execute(Club& club) {
    printEvent();
}

void ErrorEvent::printEvent() {
    std::cout << formatTime(time) << ' ' << id << ' ' << detail << std::endl;
}
