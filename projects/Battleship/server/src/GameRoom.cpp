#include "GameRoom.h"
#include "GameSession.h"

// GameRoom function to add a player, receives a player's shared_ptr to GameSession 
void GameRoom::add_player(std::shared_ptr<GameSession> player) {
    if (!player1_) {
        player1_ = player;
        player1_->set_room(shared_from_this());
    } else if (!player2_) {
        player2_ = player;
        player2_->set_room(shared_from_this());
        
        // Both players are here, start the game
        broadcast("Game matched! The game begins now.\n");
    }
}

// Function to check who is sending the message and deciding where to send it to
void GameRoom::route_message(const std::string& message, std::shared_ptr<GameSession> sender) {
    if (sender == player1_ && player2_) {
        player2_->deliver("Opponent: " + message);
    } else if (sender == player2_ && player1_) {
        player1_->deliver("Opponent: " + message);
    }
}

// Broadcast function for delivering the messages
void GameRoom::broadcast(const std::string& message) {
    if (player1_) player1_->deliver(message);
    if (player2_) player2_->deliver(message);
}