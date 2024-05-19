#ifndef EVENT_CLIENT_SIT_H
#define EVENT_CLIENT_SIT_H

#include "BaseEvent.h"
#include <string>
#include <ctime>

class ClientSitEvent : public BaseEvent {
private:
    std::string clientName;
    int table;

public:
    ClientSitEvent(int id, time_t startTime, std::string clientName, int table);
    void execute(Club& club) override;
    void printEvent() override;
};

#endif // EVENT_CLIENT_SIT_H