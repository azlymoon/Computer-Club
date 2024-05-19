#include "events/ClientArrivalEvent.h"
#include <iostream>
#include <utility>
#include "Utils.h"

ClientArrivalEvent::ClientArrivalEvent(int id, time_t time, std::string clientName) :
        BaseEvent{id, time}, clientName(std::move(clientName)) {};

void ClientArrivalEvent::printEvent() {
    std::cout << formatTime(time) << ' ' << id << ' ' << clientName << std::endl;
}

void ClientArrivalEvent::execute(Club &club) {
    printEvent();
    club.clientArrival(clientName, time);
}