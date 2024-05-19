#ifndef EVENT_CLIENT_LEAVE_H
#define EVENT_CLIENT_LEAVE_H

#include "BaseEvent.h"
#include <string>
#include <ctime>

class ClientLeaveEvent : public BaseEvent {
private:
    std::string clientName;

public:
    ClientLeaveEvent(int id, time_t endTime, std::string clientName);
    void execute(Club& club) override;
    void printEvent() override;
};

#endif // EVENT_CLIENT_LEAVE_H