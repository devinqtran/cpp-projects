#pragma once
#include <string>
#include <sstream>
#include <vector>

namespace Protocol
{

    // 1. All possible messages that can be sent over the network
    enum class CommandType
    {
        UNKNOWN,
        WAITING,   // Server -> Client: "You are in the lobby"
        MATCHED,   // Server -> Client: "Opponent found, game starting"
        PLACE,     // Client -> Server: "I placed a ship at Row, Col, Orientation"
        ATTACK,    // Client -> Server: "I am shooting at Row, Col"
        CONFIRM,   // Server -> Attacker: "Your shot was a HIT/MISS"
        ENEMY_HIT, // Server -> Defender: "The enemy shot you here"
        YOURTURN,  // Server -> Client: "It is your turn to attack"
        GAMEOVER   // Server -> Client: "The game is over, you WIN/LOSE"
    };

    // 2. A struct to hold the parsed data so C++ can easily read it
    struct Message
    {
        CommandType type = CommandType::UNKNOWN;
        int row = -1;
        int col = -1;
        char orientation = 'H';  // 'H' for Horizontal, 'V' for Vertical
        std::string status = ""; // Used for "HIT", "MISS", "SUNK", "WIN", "LOSE"
    };

    // ========================================================================
    // PARSER (Reads raw network strings and turns them into a Message struct)
    // ========================================================================
    inline Message parse(const std::string &raw_data)
    {
        Message msg;
        std::istringstream iss(raw_data);
        std::string command;

        // Grab the first word
        if (!(iss >> command))
            return msg;

        if (command == "WAITING")
        {
            msg.type = CommandType::WAITING;
        }
        else if (command == "MATCHED")
        {
            msg.type = CommandType::MATCHED;
        }
        else if (command == "PLACE")
        {
            msg.type = CommandType::PLACE;
            iss >> msg.row >> msg.col >> msg.orientation;
        }
        else if (command == "ATTACK")
        {
            msg.type = CommandType::ATTACK;
            iss >> msg.row >> msg.col;
        }
        else if (command == "CONFIRM")
        {
            msg.type = CommandType::CONFIRM;
            iss >> msg.row >> msg.col >> msg.status;
        }
        else if (command == "ENEMY_HIT")
        {
            msg.type = CommandType::ENEMY_HIT;
            iss >> msg.row >> msg.col >> msg.status;
        }
        else if (command == "YOURTURN")
        {
            msg.type = CommandType::YOURTURN;
        }
        else if (command == "GAMEOVER")
        {
            msg.type = CommandType::GAMEOVER;
            iss >> msg.status;
        }

        return msg;
    }

    // ========================================================================
    // BUILDERS (Turns C++ variables into raw network strings to send)
    // ========================================================================
    inline std::string buildPlace(int row, int col, char orientation)
    {
        return "PLACE " + std::to_string(row) + " " + std::to_string(col) + " " + orientation + "\n";
    }

    inline std::string buildAttack(int row, int col)
    {
        return "ATTACK " + std::to_string(row) + " " + std::to_string(col) + "\n";
    }

    inline std::string buildResult(int row, int col, const std::string &status)
    {
        return "RESULT " + std::to_string(row) + " " + std::to_string(col) + " " + status + "\n";
    }

    inline std::string buildGameOver(const std::string &status)
    {
        return "GAMEOVER " + status + "\n";
    }

} // namespace Protocol

/*
    Modify client code to use this protocol
    #include "../shared/Protocol.h"

    // Player clicked (3,4)
    std::string network_msg = Protocol::buildAttack(3, 4);
    network_client.send(network_msg); // Sends: "ATTACK 3 4\n"

*/