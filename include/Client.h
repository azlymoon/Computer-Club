#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <ctime>

class Client {
private:
    std::string name;
    int table;
    time_t startTime;

public:
    Client(std::string name, time_t start_time);

    std::string getName() const;
    int getTable() const;
    time_t getStartTime() const;
    time_t getEndTime() const;

    void setName(std::string);
    void setTable(int);
    void setStartTime(time_t);
};

#endif // CLIENT_H