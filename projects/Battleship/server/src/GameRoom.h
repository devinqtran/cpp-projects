// GameRoom.h
// Defines matchmaking and routing logic

#pragma once
#include <memory>
#include <string>

// Forward declaration
class GameSession;

class GameRoom : public std::enable_shared_from_this<GameRoom> {
public:
    void add_player(std::shared_ptr<GameSession> player);
    void handle_message(const std::string& message, std::shared_ptr<GameSession> sender);

private:
    void broadcast(const std::string& message);

    std::shared_ptr<GameSession> player1_; // create a shared ptr to a GameSession named player1_
    std::shared_ptr<GameSession> player2_; // create a shared ptr to a GameSession named player2_
};