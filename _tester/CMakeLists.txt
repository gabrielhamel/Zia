cmake_minimum_required(VERSION 3.0)
project(dynloader_tester)

add_executable(tester main.cpp main.cpp Interface.hpp)

add_subdirectory(../dynloader dynloader)
target_link_libraries(tester dynloader)
