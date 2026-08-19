// ServerGame.h
// Class for representing the pure game rules

#pragma once
#include <vector>
#include <string>

class ServerGame {
public:
    ServerGame();

    // Places a ship. Automatically determines length based on how many 
    // ships the player has already placed. Returns true if valid.
    bool place_ship(int player_id, int row, int col, char orientation);

    // Executes an attack. Returns "HIT", "MISS", or "WIN"
    std::string process_attack(int attacker_id, int row, int col);

    // Checks if a player has placed all 5 ships
    bool is_ready(int player_id) const;

    void reset();

private:
    static const int BOARD_SIZE = 10;
    static const int MAX_SHIPS = 5;
    
    // Standard Battleship lengths: Carrier, Battleship, Destroyer, Submarine, Patrol Boat
    const int SHIP_LENGTHS[MAX_SHIPS] = {5, 4, 3, 3, 2};

    enum class CellState { EMPTY, SHIP, HIT, MISS };

    struct PlayerState {
        std::vector<std::vector<CellState>> board;
        int ships_placed = 0;
        int ship_cells_remaining = 0; // Tracks total health. When 0, they lose.

        // Initialize a 10x10 grid of EMPTY cells
        PlayerState() : board(BOARD_SIZE, std::vector<CellState>(BOARD_SIZE, CellState::EMPTY)) {}
    };

    // Index 0 is Player 1, Index 1 is Player 2
    PlayerState players_[2]; 
};