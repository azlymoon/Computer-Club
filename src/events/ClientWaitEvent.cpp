#include "events/ClientWaitEvent.h"
#include <iostream>
#include <utility>
#include "Utils.h"

ClientWaitEvent::ClientWaitEvent(int id, time_t time, std::string clientName) :
        BaseEvent{id, time}, clientName(std::move(clientName)) {};

void ClientWaitEvent::printEvent() {
    std::cout << formatTime(time) << ' ' << id << ' ' << clientName << std::endl;
}

void ClientWaitEvent::execute(Club &club) {
    printEvent();
    club.clientWait(clientName, time);
}
