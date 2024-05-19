#ifndef CLUB_H
#define CLUB_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Client.h"
#include <memory>
#include <ctime>
#include "events/BaseEvent.h"
#include <queue>

class BaseEvent;

class Club {
private:
    int tableCount;
    time_t startTime;
    time_t endTime;
    int hourlyRate;
    std::vector<Client> clients;
    std::unordered_map<std::string, Client*> clientMap;
    std::vector<std::unique_ptr<BaseEvent>> events;
    std::vector<int> tableOccupancy;
    std::queue<Client*> waitingQueue;
    std::vector<size_t> tableProfit;
    std::vector<time_t> tableTime;

public:
    Club(int tableCount, time_t startTime, time_t endTime, int hourlyRate);
    void addEvent(std::unique_ptr<BaseEvent> event);
    void processEvents();

    void clientArrival(const std::string& clientName, time_t time);
    void clientLeave(const std::string& clientName, time_t time);
    void clientSit(const std::string& clientName, time_t time, int table);
    void clientWait(const std::string& clientName, time_t time);
    void closeClub();
    void statistic() const;
    time_t getStartTime() const;
    time_t getEndTime() const;

};

#endif // CLUB_H