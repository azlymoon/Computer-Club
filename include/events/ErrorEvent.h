#ifndef EVENT_CLIENT_ERROR_H
#define EVENT_CLIENT_ERROR_H

#include "BaseEvent.h"
#include <string>
#include <ctime>
#include "Club.h"

class ErrorEvent : public BaseEvent {
private:
    std::string detail;

public:
    ErrorEvent(int id, time_t time, std::string detail);
    void execute(Club& club) override;
    void printEvent() override;
};

#endif // EVENT_CLIENT_ERROR_H