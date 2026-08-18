cmake_minimum_required(VERSION 3.15)
project(BattleshipClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Source files ──────────────────────────────────────────────────────────────
add_executable(BattleshipClient
    src/main.cpp
    src/Game.cpp
    src/Board.cpp
    src/Ship.cpp
    src/Player.cpp
    src/Globals.cpp
    src/NetworkClient.cpp
)

# ── Include paths ─────────────────────────────────────────────────────────────
target_include_directories(BattleshipClient PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ── Shared protocol header ────────────────────────────────────────────────────
# If building standalone (not from root), locate the shared/ directory manually
if(TARGET battleship_protocol)
    target_link_libraries(BattleshipClient PRIVATE battleship_protocol)
else()
    target_include_directories(BattleshipClient PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../shared
    )
endif()

# ── raylib ────────────────────────────────────────────────────────────────────
target_link_libraries(BattleshipClient PRIVATE raylib)

# ── Copy assets next to the executable ───────────────────────────────────────
add_custom_command(TARGET BattleshipClient POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/graphics"
        "$<TARGET_FILE_DIR:BattleshipClient>/graphics"
    COMMENT "Copying graphics assets"
)

add_custom_command(TARGET BattleshipClient POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/sounds"
        "$<TARGET_FILE_DIR:BattleshipClient>/sounds"
    COMMENT "Copying sound assets"
)

# ── Boost.Asio ────────────────────────────────────────────────────────────────
find_package(Boost CONFIG REQUIRED COMPONENTS system)
target_link_libraries(BattleshipClient PRIVATE Boost::system)

# On Linux/macOS, Asio also needs pthreads
find_package(Threads REQUIRED)
target_link_libraries(BattleshipClient PRIVATE Threads::Threads)

# ── Windows Sockets ───────────────────────────────────────────────────────────
if(WIN32)
    target_link_libraries(BattleshipClient PRIVATE ws2_32 mswsock)
endif()