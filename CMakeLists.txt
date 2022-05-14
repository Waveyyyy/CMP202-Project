cmake_minimum_required(VERSION 3.16)
project(CMP202Project)

set(CMAKE_CXX_STANDARD 20)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "/opt/sfml-build")
set(SFML_LIBRARY_DIR "/opt/sfml-build/lib")

link_directories(${SFML_LIBRARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

find_package(SFML COMPONENTS network system REQUIRED)
include_directories(${PROJECT_SOURCE_DIR} ${SFML_INCLUDE_DIRS})

add_executable(CMP202Project
        src/main.cpp
        src/utils.cpp
        src/scanner.cpp
        src/tasks.hpp
        src/pools.cpp)
target_link_libraries(CMP202Project pthread sfml-network-s sfml-system-s)
