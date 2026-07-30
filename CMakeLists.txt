cmake_minimum_required(VERSION 3.10)

project(CppPortfolio VERSION 1.0 DESCRIPTION "C++ Portfolio Projects")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Output all compiled executables into a single 'bin' directory 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# add_subdirectory(algorithms)
# add_subdirectory(data_structures)
add_subdirectory(practice)
# add_subdirectory(projects)
# add_subdirectory(school)
# add_subdirectory(utils)