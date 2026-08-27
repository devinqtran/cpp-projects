cmake_minimum_required(VERSION 3.15)
project(Lab3)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab3 main.cpp Tuple.h Scheme.h Database.h Interpreter.h Relation.h)