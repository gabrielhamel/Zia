cmake_minimum_required(VERSION 3.5)

project(zia_project LANGUAGES CXX)

# Set c++ version
set(CMAKE_CXX_STANDARD 17)

# Conan
include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(zia
  # HttpParser
  Sources/src/Core/Http/HttpRequest.cpp

  # Network
  Sources/src/Network/BoostNetworkClient.cpp
  Sources/src/Network/BoostNetworkServer.cpp
  Sources/src/Network/NetworkManager.cpp
  Sources/src/Network/User.cpp

  # Modules
  Sources/include/Core/Module/ModuleApi.hpp
  Sources/include/Core/Module/Module.hpp

  # Jsp encore
  Sources/src/main.cpp
  Sources/src/Core/Parser.cpp
        Sources/src/Core/Module/Module.cpp)

target_include_directories(zia PUBLIC
  # HttpParser
  Sources/include/Core/Http

  # Network
  Sources/include/Network/

  # Jsp encore
  Sources/include/
  Sources/include/Core/
)

target_link_libraries(zia PRIVATE ${CONAN_LIBS})
target_link_libraries(zia PRIVATE ${CMAKE_DL_LIBS})
