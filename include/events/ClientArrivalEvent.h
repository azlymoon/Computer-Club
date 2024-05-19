#ifndef EVENT_CLIENT_ARRIVAL_H
#define EVENT_CLIENT_ARRIVAL_H

#include "BaseEvent.h"
#include <string>
#include <ctime>

class ClientArrivalEvent : public BaseEvent {
private:
    std::string clientName;

public:
    ClientArrivalEvent(int id, time_t time, std::string clientName);
    void execute(Club& club) override;
    void printEvent() override;
};

#endif // EVENT_CLIENT_ARRIVAL_H