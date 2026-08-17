cmake_minimum_required(VERSION 3.15)
project(Battleship)

# Create the executable from your source code
# (Be sure to update these to match your actual .cpp files!)
add_executable(Battleship 
    main.cpp
    Game.cpp
    Globals.cpp
    Board.cpp
    Ship.cpp
    Player.cpp
)

# Link the raylib library to your game
target_link_libraries(Battleship PRIVATE raylib)

# Copy the graphics folder to exactly where the executable gets built
add_custom_command(TARGET Battleship POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics"
    "$<TARGET_FILE_DIR:Battleship>/graphics"
)

# Copy the sounds folder to exactly where the executable gets built
add_custom_command(TARGET Battleship POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/sounds"
    "$<TARGET_FILE_DIR:Battleship>/sounds"
)
