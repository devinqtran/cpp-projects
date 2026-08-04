# Create the executable from your source code
add_executable(RaylibGame main.cpp)

# Link the raylib library to your game
target_link_libraries(RaylibGame PRIVATE raylib)

# Copy the graphics folder to exactly where the executable gets built
add_custom_command(TARGET RaylibGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics"
    "$<TARGET_FILE_DIR:RaylibGame>/graphics"
)