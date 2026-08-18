cmake_minimum_required(VERSION 3.15)
project(Battleship)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
# Shared protocol header is visible to both targets
add_library(battleship_protocol INTERFACE)
target_include_directories(battleship_protocol INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/shared
)
 
# Build both programs
add_subdirectory(client)
add_subdirectory(server)