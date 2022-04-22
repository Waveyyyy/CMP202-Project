cmake_minimum_required(VERSION 3.16)
project(CMP202Project)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5.1 COMPONENTS network system REQUIRED)
include_directories(${PROJECT_SOURCE_DIR} ${SFML_INCLUDE_DIRS})

add_executable(CMP202Project
        main.cpp 
        Scanner.cpp)
target_link_libraries(CMP202Project sfml-network sfml-system)
