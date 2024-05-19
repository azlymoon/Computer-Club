cmake_minimum_required(VERSION 3.10)
project(ComputerClub)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(ComputerClub main.cpp src/Client.cpp src/Club.cpp
        src/Utils.cpp
        src/events/ErrorEvent.cpp
        src/events/ClientArrivalEvent.cpp
        src/events/ClientLeaveEvent.cpp
        src/events/ClientSitEvent.cpp
        src/events/ClientWaitEvent.cpp)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(TestComputerClub test/testComputerClub.cpp src/Client.cpp src/Club.cpp
        src/Utils.cpp
        src/events/ErrorEvent.cpp
        src/events/ClientArrivalEvent.cpp
        src/events/ClientLeaveEvent.cpp
        src/events/ClientSitEvent.cpp
        src/events/ClientWaitEvent.cpp)

target_link_libraries(TestComputerClub gtest gtest_main)

enable_testing()
add_test(NAME TestComputerClub COMMAND TestComputerClub)