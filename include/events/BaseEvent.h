#ifndef BASE_EVENT_H
#define BASE_EVENT_H

#include <ctime>
#include <string>
#include "Club.h"

class Club;

class BaseEvent {
protected:
    int id;
    time_t time;

public:
    BaseEvent(int id, time_t time) : id(id), time(time) {};
    virtual void printEvent() = 0;
    virtual void execute(Club& club) = 0;
    virtual ~BaseEvent() = default;
};

#endif // BASE_EVENT_H