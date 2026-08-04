cmake_minimum_required(VERSION 3.10)

project(CppPortfolio VERSION 1.0 DESCRIPTION "C++ Portfolio Projects")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Output all compiled executables into a single 'bin' directory 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(CppProjects)

# 1. Bring in the FetchContent module
include(FetchContent)

# 2. Prevent CMake from building raylib's built-in examples to save compile time
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# 3. Download and configure raylib directly from GitHub
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        6.0
)
FetchContent_MakeAvailable(raylib)

# add_subdirectory(algorithms)
# add_subdirectory(data_structures)
add_subdirectory(practice)
# add_subdirectory(projects)
# add_subdirectory(school)
# add_subdirectory(utils)
add_subdirectory(projects/RaylibGame)
