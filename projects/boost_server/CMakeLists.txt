# 1. Find Boost using the modern CONFIG mode (this suppresses the CMP0167 warning)
find_package(Boost CONFIG REQUIRED COMPONENTS system)

# 2. CREATE YOUR EXECUTABLE FIRST
# (Replace 'main.cpp' with whatever your actual source file is named)
add_executable(boost_server main.cpp)

# 3. NOW you can link Boost to your executable
# Using Boost::system automatically handles the include directories for you!
target_link_libraries(boost_server PRIVATE Boost::system)