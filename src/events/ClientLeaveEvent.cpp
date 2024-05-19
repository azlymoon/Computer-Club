#include "events/ClientLeaveEvent.h"
#include <iostream>
#include <utility>
#include "Utils.h"

ClientLeaveEvent::ClientLeaveEvent(int id, time_t endTime, std::string clientName) :
        BaseEvent{id, endTime}, clientName(std::move(clientName)) {};

void ClientLeaveEvent::printEvent() {
    std::cout << formatTime(time) << ' ' << id << ' ' << clientName << std::endl;
}

void ClientLeaveEvent::execute(Club &club) {
    printEvent();
    club.clientLeave(clientName, time);
}
