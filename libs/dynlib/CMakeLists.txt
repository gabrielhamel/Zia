cmake_minimum_required(VERSION 3.0)

add_library(dynlib STATIC include/DynLib.hpp include/DLException.hpp include/Lib.hpp src/DLException.cpp src/DynLib.cpp)

target_include_directories(dynlib PUBLIC include)
