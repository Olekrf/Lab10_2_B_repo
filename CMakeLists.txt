cmake_minimum_required(VERSION 3.20)
project(lab10_2_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab10_2_3 main.cpp)

find_package(GTest REQUIRED)

add_executable(runTests test.cpp)
target_link_libraries(runTests PRIVATE GTest::gtest GTest::gtest_main)