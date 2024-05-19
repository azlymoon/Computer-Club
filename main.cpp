#include "Club.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "Utils.h"
#include "events/ClientSitEvent.h"
#include "events/ClientLeaveEvent.h"
#include "events/ClientArrivalEvent.h"
#include "events/ClientWaitEvent.h"

void handleErrorAndExit(const std::string& errorLine) {
    std::cerr << errorLine << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return 1;
    }

    std::string line;

    try {
        if (!std::getline(inFile, line)) throw std::runtime_error(line);
        int tableCount = std::stoi(line);

        if (!std::getline(inFile, line)) throw std::runtime_error(line);
        std::istringstream iss(line);
        std::string startTime, endTime;
        if (!(iss >> startTime >> endTime)) throw std::runtime_error(line);

        if (!std::getline(inFile, line)) throw std::runtime_error(line);
        int hourlyRate = std::stoi(line);

        Club club(tableCount, parseTime(startTime), parseTime(endTime), hourlyRate);

        while (std::getline(inFile, line)) {
            std::istringstream eventStream(line);
            std::string time, clientName;
            int eventId;
            if (!(eventStream >> time >> eventId)) throw std::runtime_error(line);
            time_t formatTime = parseTime(time);

            switch (eventId) {
                case 1:
                    if (!(eventStream >> clientName)) throw std::runtime_error(line);
                    club.addEvent(std::make_unique<ClientArrivalEvent>(eventId, formatTime, clientName));
                    break;
                case 2: {
                    int tableNumber;
                    if (!(eventStream >> clientName >> tableNumber)) throw std::runtime_error(line);
                    club.addEvent(std::make_unique<ClientSitEvent>(eventId, formatTime, clientName, tableNumber));
                    break;
                }
                case 3:
                    if (!(eventStream >> clientName)) throw std::runtime_error(line);
                    club.addEvent(std::make_unique<ClientWaitEvent>(eventId, formatTime, clientName));
                    break;
                case 4:
                    if (!(eventStream >> clientName)) throw std::runtime_error(line);
                    club.addEvent(std::make_unique<ClientLeaveEvent>(eventId, formatTime, clientName));
                    break;
                default:
                    throw std::runtime_error(line);
            }
        }

        std::cout << startTime << std::endl;
        club.processEvents();
        club.closeClub();
        std::cout << endTime << std::endl;
        club.statistic();

    } catch (const std::runtime_error& e) {
        handleErrorAndExit(e.what());
    } catch (const std::invalid_argument& e) {
        handleErrorAndExit("Invalid argument: " + std::string(e.what()));
    } catch (const std::exception& e) {
        handleErrorAndExit("Error: " + std::string(e.what()));
    }

    return 0;
}
