cmake_minimum_required(VERSION 3.0)

add_library(dynloader STATIC src/DynLib.cpp include/DynLib.hpp src/exception/DLException.cpp include/exception/DLException.hpp include/Lib.hpp)

target_link_libraries(dynloader PRIVATE dl)
target_include_directories(dynloader PUBLIC include/)
