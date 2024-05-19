#include "events/ClientSitEvent.h"
#include <iostream>
#include <utility>
#include "Utils.h"

ClientSitEvent::ClientSitEvent(int id, time_t startTime, std::string clientName, int table) :
        BaseEvent{id, startTime}, clientName(std::move(clientName)), table(table) {};

void ClientSitEvent::printEvent() {
    std::cout << formatTime(time) << ' ' << id << ' ' << clientName << ' ' << table << std::endl;
}

void ClientSitEvent::execute(Club &club) {
    printEvent();
    club.clientSit(clientName, time, table);
}