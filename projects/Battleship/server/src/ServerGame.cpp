// ServerGame.cpp
// File for collision checking, bounds checking, and hit detection

#include "ServerGame.h"

ServerGame::ServerGame() {}

bool ServerGame::place_ship(int player_id, int row, int col, char orientation) {
    PlayerState& player = players_[player_id];
    
    // Check if they already placed all ships
    if (player.ships_placed >= MAX_SHIPS) return false;
    
    int length = SHIP_LENGTHS[player.ships_placed];

    // 1. Bounds checking (does it go off the edge of the board?)
    if (orientation == 'H' && col + length > BOARD_SIZE) return false;
    if (orientation == 'V' && row + length > BOARD_SIZE) return false;
    if (row < 0 || col < 0) return false;

    // 2. Collision checking (does it overlap an existing ship?)
    for (int i = 0; i < length; ++i) {
        int r = row + (orientation == 'V' ? i : 0);
        int c = col + (orientation == 'H' ? i : 0);
        if (player.board[r][c] != CellState::EMPTY) return false;
    }

    // 3. Actually place the ship
    for (int i = 0; i < length; ++i) {
        int r = row + (orientation == 'V' ? i : 0);
        int c = col + (orientation == 'H' ? i : 0);
        player.board[r][c] = CellState::SHIP;
    }

    player.ships_placed++;
    player.ship_cells_remaining += length; // Add to total health
    return true;
}

std::string ServerGame::process_attack(int attacker_id, int row, int col) {
    int defender_id = (attacker_id == 0) ? 1 : 0;
    PlayerState& defender = players_[defender_id];

    // Out of bounds counts as a miss
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return "MISS";
    }

    CellState& target = defender.board[row][col];

    if (target == CellState::SHIP) {
        target = CellState::HIT;
        defender.ship_cells_remaining--;
        
        // If that was the last piece of the last ship, the attacker wins!
        if (defender.ship_cells_remaining <= 0) {
            return "WIN";
        }
        return "HIT";
    } 
    else if (target == CellState::EMPTY) {
        target = CellState::MISS;
        return "MISS";
    }

    // If they shoot somewhere they already shot, it just returns what it was
    return (target == CellState::HIT) ? "HIT" : "MISS";
}

// Boolean to check if both players have placed their ships so game can start
bool ServerGame::is_ready(int player_id) const {
    return players_[player_id].ships_placed == MAX_SHIPS;
}