cmake_minimum_required(VERSION 3.0)

add_library(testMod SHARED module.cpp)

target_include_directories(testMod PRIVATE ../../Sources/include/Core/Module/) # TODO: cleaner way to provide this header

# CONAN STUFF (until the end of the file)

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES
                    boost/1.71.0@conan/stable
                BASIC_SETUP
                BUILD missing)

target_link_libraries(testMod ${CONAN_LIBS})

# Probably not the cleanest way to do it, but it works :shrug:
foreach(dir in ${CONAN_INCLUDE_DIRS})
    target_include_directories(testMod PUBLIC ${dir})
endforeach()

foreach(dir in ${CONAN_LIB_DIRS})
    target_link_directories(testMod PUBLIC ${dir})
endforeach()
