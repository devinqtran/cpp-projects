cmake_minimum_required(VERSION 3.15)
project(Parser)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Parser main.cpp Parser.h)