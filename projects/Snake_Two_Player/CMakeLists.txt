add_executable(Snake_Two_Player main.cpp)

target_link_libraries(Snake_Two_Player PRIVATE raylib)

add_custom_command(TARGET Snake_Two_Player POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics"
    "$<TARGET_FILE_DIR:Snake_Two_Player>/graphics"
)

add_custom_command(TARGET Snake_Two_Player POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/sounds"
    "$<TARGET_FILE_DIR:Snake_Two_Player>/sounds"
)