#include "Club.h"
#include "events/ErrorEvent.h"
#include "events/ClientSitEvent.h"
#include "events/ClientLeaveEvent.h"
#include "events/BaseEvent.h"
#include <algorithm>
#include <iostream>
#include <exception>
#include "Utils.h"

Club::Club(int tableCount, time_t startTime, time_t endTime, int hourlyRate) :
        tableCount(tableCount), startTime(startTime), endTime(endTime), hourlyRate(hourlyRate),
        tableOccupancy(tableCount, 0), tableProfit(tableCount, 0), tableTime(tableCount, 0) {
    if (tableCount <= 0) {
        throw std::invalid_argument("Number of tables must be greater than zero");
    }
    if (startTime >= endTime) {
        throw std::invalid_argument("Start time must be less than end time");
    }
    if (hourlyRate <= 0) {
        throw std::invalid_argument("Hourly rate must be greater than zero");
    }
}

void Club::addEvent(std::unique_ptr<BaseEvent> event) {
    if (!event) {
        throw std::invalid_argument("Event cannot be null");
    }
    events.push_back(std::move(event));
}

void Club::processEvents() {
    for (auto &event : events) {
        try {
            event->execute(*this);
        } catch (const std::exception &e) {
            std::cerr << "Error processing event: " << e.what() << std::endl;
        }
    }
}

void Club::clientArrival(const std::string &clientName, time_t time) {
    if (time < startTime || time > endTime) {
        ErrorEvent(13, time, "NotOpenYet").printEvent();
        return;
    }

    if (clientMap.find(clientName) != clientMap.end()) {
        ErrorEvent(13, time, "YouShallNotPass").printEvent();
        return;
    }

    clientMap.emplace(clientName, new Client{clientName, time});
}

void Club::clientSit(const std::string &clientName, time_t time, int table) {
    if (table < 1 || table > tableCount) {
        ErrorEvent(13, time, "PlaceIsBusy").printEvent();
        return;
    }

    auto it = clientMap.find(clientName);
    if (it == clientMap.end()) {
        ErrorEvent(13, time, "ClientUnknown").printEvent();
        return;
    }

    Client &client = *(it->second);
    if (tableOccupancy[table - 1] != 0) {
        ErrorEvent(13, time, "PlaceIsBusy").printEvent();
        return;
    }

    if (client.getTable() != -1) {
        tableOccupancy[client.getTable() - 1] = 0;
    }

    client.setTable(table);
    client.setStartTime(time);
    tableOccupancy[table - 1] = 1;
}

void Club::clientLeave(const std::string &clientName, time_t time) {
    auto it = clientMap.find(clientName);
    if (it == clientMap.end()) {
        ErrorEvent(13, time, "ClientUnknown").printEvent();
        return;
    }

    Client &client = *(it->second);
    if (client.getTable() != -1) {
        tableOccupancy[client.getTable() - 1] = 0;
        tableTime[client.getTable() - 1] += time - client.getStartTime();
        tableProfit[client.getTable() - 1] += calculateProfitFromDuration(hourlyRate, client.getStartTime(), time);
    }

    clientMap.erase(it);

    if (!waitingQueue.empty()) {
        Client &waitedClient = *waitingQueue.front();
        ClientSitEvent(12, time, waitedClient.getName(), client.getTable()).execute(*this);
        waitingQueue.pop();
    }
}

void Club::clientWait(const std::string &clientName, time_t time) {
    auto it = clientMap.find(clientName);
    if (it == clientMap.end()) {
        ErrorEvent(13, time, "ClientUnknown").printEvent();
        return;
    }

    size_t countFreeTable = std::count_if(tableOccupancy.begin(), tableOccupancy.end(),
                                          [](int _val) {
                                              return _val == 0;
                                          });
    if (countFreeTable != 0) {
        ErrorEvent(13, time, "ICanWaitNoLonger!").printEvent();
        return;
    }

    if (waitingQueue.size() >= tableCount) {
        ClientLeaveEvent(11, time, clientName).execute(*this);
        return;
    }

    waitingQueue.push(it->second);
}

void Club::closeClub() {
    std::vector<std::string> remainingClients;
    std::for_each(clientMap.begin(), clientMap.end(),
                  [&remainingClients](auto &item) {
                      remainingClients.push_back(item.first);
                  });
    std::sort(remainingClients.begin(), remainingClients.end());
    for (const auto &clientName : remainingClients) {
        ClientLeaveEvent(11, endTime, clientName).execute(*this);
    }
}

void Club::statistic() const {
    for (size_t i = 0; i < tableProfit.size(); i++) {
        std::cout << i + 1 << ' ' << tableProfit[i] << ' ' << formatTimeDuration(tableTime[i]) << std::endl;
    }
}

time_t Club::getStartTime() const {
    return startTime;
}

time_t Club::getEndTime() const {
    return endTime;
}
