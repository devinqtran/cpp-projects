# Notice we named the target 'cs236_project' instead of 'main' to avoid global collisions
# Include Token.h in your directory, but only list .cpp files in add_executable
add_executable(cs236_project main.cpp Token.h)

# If you create more .cpp files later (like Token.cpp or Scanner.cpp), add them here:
# add_executable(cs236_project main.cpp Token.cpp Scanner.cpp)