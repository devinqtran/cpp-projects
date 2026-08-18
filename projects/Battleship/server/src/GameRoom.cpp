#include "GameRoom.h"
#include "GameSession.h"
#include "Protocol.h"
#include <iostream>

// GameRoom function to add a player, receives a player's shared_ptr to GameSession 
void GameRoom::add_player(std::shared_ptr<GameSession> player) {
    if (!player1_) {
        player1_ = player;
        player1_->set_room(shared_from_this());
        player1_->deliver("WAITING\n"); // Tell player 1 to wait
    } else if (!player2_) {
        player2_ = player;
        player2_->set_room(shared_from_this());
        
        // Both players are here! Tell them they matched.
        broadcast("MATCHED\n");
        
        // Give Player 1 the first turn
        player1_->deliver("YOURTURN\n");
    }
}

// Function to check who is sending the message and deciding where to send it to
void GameRoom::handle_message(const std::string& raw_data, std::shared_ptr<GameSession> sender) {
    // 1. Parse the incoming string into a C++ struct
    Protocol::Message msg = Protocol::parse(raw_data);
    
    // 2. Figure out who the opponent is
    auto opponent = (sender == player1_) ? player2_ : player1_;

    // 3. Decide what to do based on the command
    switch (msg.type) {
        case Protocol::CommandType::PLACE:
            std::cout << "[ROOM] Player placed a ship at row " << msg.row << ", col " << msg.col << "\n";
            // TODO: Pass this to ServerGame to store the board state
            break;

        case Protocol::CommandType::ATTACK:
            std::cout << "[ROOM] Player attacked row " << msg.row << ", col " << msg.col << "\n";
            
            // TODO: Ask ServerGame if it's a hit or miss. 
            // For right now, let's just pretend everything is a MISS.
            if (opponent) {
                // Build the result message
                std::string result_msg = Protocol::buildResult(msg.row, msg.col, "MISS");
                
                // Send the result to BOTH players so their screens update
                sender->deliver(result_msg);
                opponent->deliver(result_msg);
                
                // Tell the opponent it's now their turn
                opponent->deliver("YOURTURN\n");
            }
            break;

        default:
            std::cout << "[ROOM] Received unknown or unhandled command.\n";
            break;
    }
}

// Broadcast function for delivering the messages
void GameRoom::broadcast(const std::string& message) {
    if (player1_) player1_->deliver(message);
    if (player2_) player2_->deliver(message);
}