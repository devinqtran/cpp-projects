cmake_minimum_required(VERSION 3.15)
project(BattleshipServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Source files ──────────────────────────────────────────────────────────────
add_executable(BattleshipServer
    src/main.cpp
    src/GameSession.cpp
    src/GameRoom.cpp
    src/BattleshipServer.cpp
    src/ServerGame.cpp
)

# ── Include paths ─────────────────────────────────────────────────────────────
target_include_directories(BattleshipServer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ── Shared protocol header ────────────────────────────────────────────────────
if(TARGET battleship_protocol)
    target_link_libraries(BattleshipServer PRIVATE battleship_protocol)
else()
    target_include_directories(BattleshipServer PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../shared
    )
endif()

# ── Boost.Asio ────────────────────────────────────────────────────────────────
# Prefer the modern CONFIG mode to suppress CMP0167 warnings
find_package(Boost CONFIG REQUIRED COMPONENTS system)
target_link_libraries(BattleshipServer PRIVATE Boost::system)

# On Linux/macOS, Asio also needs pthreads
find_package(Threads REQUIRED)
target_link_libraries(BattleshipServer PRIVATE Threads::Threads)

# ── Windows Sockets (Required for Boost.Asio on Windows) ──────────────────────
if(WIN32)
    target_link_libraries(BattleshipServer PRIVATE ws2_32 mswsock)
endif()