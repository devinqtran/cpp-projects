# Create the executable from your source code
add_executable(RaylibGame 
    main.cpp
    Globals.cpp
    Snake.cpp
    Food.cpp
    Game.cpp
    )

# Link the raylib library to your game
target_link_libraries(RaylibGame PRIVATE raylib)

# Copy the graphics folder to exactly where the executable gets built
add_custom_command(TARGET RaylibGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics"
    "$<TARGET_FILE_DIR:RaylibGame>/graphics"
)

# Copy the sounds folder to exactly where the executable gets built
add_custom_command(TARGET RaylibGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/sounds"
    "$<TARGET_FILE_DIR:RaylibGame>/sounds"
)