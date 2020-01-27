cmake_minimum_required(VERSION 3.5)

project(zia_project LANGUAGES CXX)

# Set c++ version
set(CMAKE_CXX_STANDARD 17)

# Conan
include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(zia
  # HttpParser
  src/Core/Http/HttpRequest.cpp
  src/Core/Http/HttpResponse.cpp

  # Network
  src/Network/BoostNetworkClient.cpp
  src/Network/BoostNetworkServer.cpp
  src/Network/NetworkManager.cpp
  src/Network/Request.cpp

  # Modules
  inc/Core/Module/ModuleApi.hpp
  inc/Core/Module/Module.hpp

  # yml-config
  src/ConfigNode.cpp
  inc/yconf/ConfigNode.hpp
  inc/IConfigNode.hpp
  inc/yconf/Helper.hpp
  inc/yconf/util.hpp
  src/util.cpp

  # Jsp encore
  src/main.cpp
  src/Core/Configs/Configurations.cpp
  src/Core/Configs/Module.cpp
  src/Core/Module/Module.cpp
  src/Core/Listeners/ListenersControl.cpp
  src/Ihm/CmdLine.cpp
)

target_include_directories(zia PUBLIC
  # HttpParser
  inc/Core/Http

  # Network
  inc/Network/

  # Jsp encore
  inc/Core/Http/api
  inc/
  inc/Core/
  inc/Core/Listeners/
  inc/Ihm/
  inc/Core/Configs
)

target_link_libraries(zia PRIVATE ${CONAN_LIBS})
target_link_libraries(zia PRIVATE ${CMAKE_DL_LIBS})
