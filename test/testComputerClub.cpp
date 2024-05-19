#include <gtest/gtest.h>
#include <fstream>
#include <memory>
#include "Club.h"
#include "events/ClientArrivalEvent.h"
#include "events/ClientWaitEvent.h"
#include "events/ClientSitEvent.h"
#include "events/ClientLeaveEvent.h"
#include "Utils.h"

Club* getClubFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    std::string line;

    std::getline(inFile, line);
    int tableCount = std::stoi(line);

    std::string startTime, endTime;
    std::getline(inFile, line);
    std::istringstream iss(line);
    iss >> startTime >> endTime;

    std::getline(inFile, line);
    int hourlyRate = std::stoi(line);

    Club* club = new Club(tableCount, parseTime(startTime), parseTime(endTime), hourlyRate);

    while (std::getline(inFile, line)) {
        std::istringstream eventStream(line);
        std::string time, clientName;
        int eventId;
        eventStream >> time >> eventId;
        time_t formatTime = parseTime(time);

        switch (eventId) {
            case 1:
                eventStream >> clientName;
                club->addEvent(std::make_unique<ClientArrivalEvent>(eventId, formatTime, clientName));
                break;
            case 2:
                int tableNumber;
                eventStream >> clientName >> tableNumber;
                club->addEvent(std::make_unique<ClientSitEvent>(eventId, formatTime, clientName, tableNumber));
                break;
            case 3:
                eventStream >> clientName;
                club->addEvent(std::make_unique<ClientWaitEvent>(eventId, formatTime, clientName));
                break;
            case 4:
                eventStream >> clientName;
                club->addEvent(std::make_unique<ClientLeaveEvent>(eventId, formatTime, clientName));
                break;
        }
    }

    return club;
}

std::string processClub(Club* club) {
    std::stringstream ss;
    std::streambuf* originalCout = std::cout.rdbuf();
    std::cout.rdbuf(ss.rdbuf());

    std::cout << formatTime(club->getStartTime()) << std::endl;
    club->processEvents();
    club->closeClub();
    std::cout << formatTime(club->getEndTime()) << std::endl;
    club->statistic();

    std::cout.rdbuf(originalCout);

    return ss.str();
}

std::string readCorrectOutput(const std::string& correctOutput) {
    std::ifstream outputFile(correctOutput);
    std::stringstream buffer;
    buffer << outputFile.rdbuf();

    return buffer.str();
}

TEST(ComputerClubTest, Example) {
    Club* club = getClubFromFile("../test/data/example_input.txt");
    std::string result = processClub(club);
    std::string correct = readCorrectOutput("../test/data/example_output.txt");
    EXPECT_EQ(result, correct);
    delete club;
}

TEST(ComputerClubTest, CorrectData) {
    Club* club = getClubFromFile("../test/data/correct_input.txt");
    std::string result = processClub(club);
    std::string correct = readCorrectOutput("../test/data/correct_output.txt");
    EXPECT_EQ(result, correct);
    delete club;
}

TEST(ComputerClubTest, TableBusy) {
    Club* club = getClubFromFile("../test/data/table_busy_input.txt");
    std::string result = processClub(club);
    std::string correct = readCorrectOutput("../test/data/table_busy_output.txt");
    EXPECT_EQ(result, correct);
    delete club;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}