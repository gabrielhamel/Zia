cmake_minimum_required(VERSION 3.5)

project(zia_project LANGUAGES CXX)

# Set c++ version
set(CMAKE_CXX_STANDARD 17)

# Conan
include(build/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(zia
  # DynLib
  Sources/src/Core/DynLib/exception/DLException.cpp
  Sources/src/Core/DynLib/DynLib.cpp

  # HttpParser
  Sources/src/Core/Http/HttpRequest.cpp

  # Network
  Sources/src/Network/BoostNetworkClient.cpp
  Sources/src/Network/BoostNetworkServer.cpp
  Sources/src/Network/NetworkManager.cpp
  Sources/src/Network/User.cpp

  # Jsp encore
  Sources/src/main.cpp
  Sources/src/Core/Parser.cpp
)

target_include_directories(zia PUBLIC
  # DynLib
  Sources/include/Core/DynLib/exception
  Sources/include/Core/DynLib

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
