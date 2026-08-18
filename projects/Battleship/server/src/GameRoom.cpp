#include "GameRoom.h"
#include "GameSession.h"
#include "Protocol.h"
#include <iostream>

// GameRoom function to add a player, receives a player's shared_ptr to GameSession
void GameRoom::add_player(std::shared_ptr<GameSession> player)
{
    if (!player1_)
    {
        player1_ = player;
        player1_->set_room(shared_from_this());
        player1_->deliver("WAITING\n"); // Tell player 1 to wait
    }
    else if (!player2_)
    {
        player2_ = player;
        player2_->set_room(shared_from_this());

        // Both players are here! Tell them they matched.
        broadcast("MATCHED\n");
    }
}

// Function to check who is sending the message and deciding where to send it to
void GameRoom::handle_message(const std::string &raw_data, std::shared_ptr<GameSession> sender)
{
    Protocol::Message msg = Protocol::parse(raw_data);
    auto opponent = (sender == player1_) ? player2_ : player1_; // opponent either player1/player2 based on the sender of the message

    // Identify which integer ID this player is
    int player_id = (sender == player1_) ? 0 : 1;

    // Switch statement to execute the right message based on the command type
    switch (msg.type)
    {
    case Protocol::CommandType::PLACE:
    {
        bool success = game_.place_ship(player_id, msg.row, msg.col, msg.orientation);

        if (success)
        {
            std::cout << "[ROOM] Player " << player_id << " placed a ship.\n";

            // If both players have finished placing all 5 ships, start the game!
            if (game_.is_ready(0) && game_.is_ready(1))
            {
                std::cout << "[ROOM] Both players ready. Game starting.\n";
                broadcast("MATCHED\n");
                player1_->deliver("YOURTURN\n"); // Player 1 goes first
            }
        }
        break;
    }

    case Protocol::CommandType::ATTACK:
    {
        // Ask the ServerGame logic what happened
        std::string status = game_.process_attack(player_id, msg.row, msg.col);

        // Tell BOTH players the result of the shot
        std::string result_msg = Protocol::buildResult(msg.row, msg.col, status);
        broadcast(result_msg);

        // Handle game over or next turn
        if (status == "WIN")
        {
            sender->deliver(Protocol::buildGameOver("WIN"));
            if (opponent)
                opponent->deliver(Protocol::buildGameOver("LOSE"));
        }
        else if (opponent)
        {
            opponent->deliver("YOURTURN\n");
        }
        break;
    }

    default:
        break;
    }
}

// Broadcast function for delivering the messages
void GameRoom::broadcast(const std::string &message)
{
    if (player1_)
        player1_->deliver(message);
    if (player2_)
        player2_->deliver(message);
}