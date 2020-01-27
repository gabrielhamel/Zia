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
  Sources/src/Core/Http/HttpResponse.cpp

  # Network
  Sources/src/Network/BoostNetworkClient.cpp
  Sources/src/Network/BoostNetworkServer.cpp
  Sources/src/Network/NetworkManager.cpp
  Sources/src/Network/Request.cpp

  # Modules
  Sources/include/Core/Module/ModuleApi.hpp
  Sources/include/Core/Module/Module.hpp

  # Jsp encore
  Sources/src/main.cpp
  Sources/src/Core/Configs/Configurations.cpp
  Sources/src/Core/Configs/Module.cpp
  Sources/src/Core/Module/Module.cpp
  Sources/src/Core/Listeners/ListenersControl.cpp
  Sources/src/Ihm/CmdLine.cpp
)

target_include_directories(zia PUBLIC
  # HttpParser
  Sources/include/Core/Http

  # Network
  Sources/include/Network/

  # Jsp encore
  Sources/include/Core/Http/api
  Sources/include/
  Sources/include/Core/
  Sources/include/Core/Listeners/
  Sources/include/Ihm/
  Sources/include/Core/Configs
)

add_library(yaml-config STATIC
  libs/yaml-config/src/ConfigNode.cpp
  libs/yaml-config/include/yconf/ConfigNode.hpp
  libs/yaml-config/include/IConfigNode.hpp
  libs/yaml-config/include/yconf/Helper.hpp
  libs/yaml-config/include/yconf/util.hpp
  libs/yaml-config/src/util.cpp
)

target_include_directories(yaml-config PUBLIC
  libs/yaml-config/include
)

target_link_libraries(yaml-config PUBLIC ${CONAN_LIBS})
target_link_libraries(zia PRIVATE ${CONAN_LIBS})
target_link_libraries(zia PRIVATE ${CMAKE_DL_LIBS})
target_link_libraries(zia PRIVATE yaml-config)
