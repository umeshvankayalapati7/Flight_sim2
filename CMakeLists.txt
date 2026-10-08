cmake_minimum_required(VERSION 3.16)
project(aircraft_sim CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core simulation code, shared by the executable and the tests
add_library(simcore
    src/aircraft.cpp
    src/pid.cpp
    src/simulation.cpp)
target_include_directories(simcore PUBLIC src)
target_compile_options(simcore PRIVATE -Wall -Wextra)

# The simulator program
add_executable(sim src/main.cpp)
target_link_libraries(sim PRIVATE simcore)
target_compile_options(sim PRIVATE -Wall -Wextra)

# Tests
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(sim_tests
    tests/test_aircraft.cpp
    tests/test_pid.cpp
    tests/test_closed_loop.cpp)
target_link_libraries(sim_tests PRIVATE simcore GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(sim_tests)