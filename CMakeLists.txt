cmake_minimum_required(VERSION 3.5)

project(zia LANGUAGES CXX)

# Set c++ version
set(CMAKE_CXX_STANDARD 17)

# Conan
include(build/conanbuildinfo.cmake)
conan_basic_setup()

# Server
add_executable(zia
  # Sources
  Server/main.cpp
)

target_include_directories(zia PUBLIC
  # Include directories
  Server
)

target_link_libraries(zia PRIVATE ${CONAN_LIBS})
