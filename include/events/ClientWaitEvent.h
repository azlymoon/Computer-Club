#ifndef EVENT_CLIENT_WAIT_H
#define EVENT_CLIENT_WAIT_H

#include "BaseEvent.h"
#include <string>
#include <ctime>

class ClientWaitEvent : public BaseEvent {
private:
    std::string clientName;

public:
    ClientWaitEvent(int id, time_t time, std::string clientName);
    void execute(Club& club) override;
    void printEvent() override;
};

#endif // EVENT_CLIENT_WAIT_H