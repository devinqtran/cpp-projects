/*
    PLACE <row> <col> <orientation>   → sent by client during setup
    ATTACK <row> <col>                → sent by client on their turn
    RESULT <row> <col> <HIT|MISS> <SUNK|> → server response
    YOURTURN                          → server tells a client it's their turn
    GAMEOVER <WIN|LOSE>               → server ends the game
*/

#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <optional>

// ═════════════════════════════════════════════════════════════════════════════
//  Battleship Network Protocol  (v1)
//
//  Transport:  TCP, line-delimited text.
//              Every message is a single line ending with '\n'.
//              Fields are separated by a single space.
//
//  Flow:
//    1. Client connects  →  Server sends WELCOME
//    2. Server sends     →  WAITING  (no opponent yet)
//       or               →  YOURTURN / OPPONENTTURN once paired
//    3. During PLACEMENT  →  Client sends PLACE for each ship (5 total)
//                            Server replies PLACE_OK or PLACE_ERR
//                            After all ships placed, server sends GAME_START
//    4. During play       →  Active player sends ATTACK <row> <col>
//                            Server sends RESULT to both players
//                            Server then sends YOURTURN / OPPONENTTURN
//    5. Game ends         →  Server sends GAMEOVER <WIN|LOSE> to each player
//
//  Row/col are 0-based integers (0–9).
//  Orientation: H = horizontal, V = vertical.
// ═════════════════════════════════════════════════════════════════════════════

namespace Protocol {

// ── Message type tags ─────────────────────────────────────────────────────────

// Server → Client
constexpr const char* WELCOME         = "WELCOME";      // "WELCOME" — connection accepted
constexpr const char* WAITING         = "WAITING";      // "WAITING" — no opponent yet
constexpr const char* GAME_START      = "GAME_START";   // "GAME_START" — both players placed ships
constexpr const char* PLACE_OK        = "PLACE_OK";     // "PLACE_OK <size> <row> <col> <H|V>"
constexpr const char* PLACE_ERR       = "PLACE_ERR";    // "PLACE_ERR <reason>"
constexpr const char* RESULT          = "RESULT";       // "RESULT <row> <col> <HIT|MISS> [SUNK <shipname>]"
constexpr const char* YOURTURN        = "YOURTURN";     // "YOURTURN"
constexpr const char* OPPONENTTURN    = "OPPONENTTURN"; // "OPPONENTTURN"
constexpr const char* GAMEOVER        = "GAMEOVER";     // "GAMEOVER <WIN|LOSE>"
constexpr const char* ERROR_MSG       = "ERROR";        // "ERROR <description>"

// Client → Server
constexpr const char* PLACE           = "PLACE";        // "PLACE <size> <row> <col> <H|V>"
constexpr const char* ATTACK          = "ATTACK";       // "ATTACK <row> <col>"

// ── Orientation encoding ──────────────────────────────────────────────────────

inline char orientationToChar(bool isHorizontal) {
    return isHorizontal ? 'H' : 'V';
}

inline bool charToHorizontal(char c) {
    return c == 'H';
}

// ── Result type for parsing ───────────────────────────────────────────────────

enum class AttackResult { HIT, MISS };

// Returned by parseResult(); sunkShipName is non-empty when a ship was sunk.
struct ResultPayload {
    int row;
    int col;
    AttackResult outcome;
    std::string sunkShipName; // empty if ship was not sunk this hit
};

// ── Message builders (Client → Server) ───────────────────────────────────────

// "PLACE <size> <row> <col> <H|V>\n"
inline std::string makePlaceMsg(int size, int row, int col, bool horizontal) {
    std::ostringstream oss;
    oss << PLACE << " " << size << " " << row << " " << col
        << " " << orientationToChar(horizontal) << "\n";
    return oss.str();
}

// "ATTACK <row> <col>\n"
inline std::string makeAttackMsg(int row, int col) {
    std::ostringstream oss;
    oss << ATTACK << " " << row << " " << col << "\n";
    return oss.str();
}

// ── Message builders (Server → Client) ───────────────────────────────────────

// "RESULT <row> <col> <HIT|MISS>\n"
// "RESULT <row> <col> HIT SUNK <shipname>\n"
inline std::string makeResultMsg(int row, int col, bool isHit,
                                  const std::string& sunkShipName = "") {
    std::ostringstream oss;
    oss << RESULT << " " << row << " " << col << " "
        << (isHit ? "HIT" : "MISS");
    if (isHit && !sunkShipName.empty()) {
        oss << " SUNK " << sunkShipName;
    }
    oss << "\n";
    return oss.str();
}

// "PLACE_OK <size> <row> <col> <H|V>\n"
inline std::string makePlaceOkMsg(int size, int row, int col, bool horizontal) {
    std::ostringstream oss;
    oss << PLACE_OK << " " << size << " " << row << " " << col
        << " " << orientationToChar(horizontal) << "\n";
    return oss.str();
}

// "PLACE_ERR <reason>\n"
inline std::string makePlaceErrMsg(const std::string& reason) {
    return std::string(PLACE_ERR) + " " + reason + "\n";
}

// "GAMEOVER <WIN|LOSE>\n"
inline std::string makeGameOverMsg(bool won) {
    return std::string(GAMEOVER) + " " + (won ? "WIN" : "LOSE") + "\n";
}

// Simple one-word messages
inline std::string makeWelcomeMsg()       { return std::string(WELCOME)       + "\n"; }
inline std::string makeWaitingMsg()       { return std::string(WAITING)       + "\n"; }
inline std::string makeGameStartMsg()     { return std::string(GAME_START)    + "\n"; }
inline std::string makeYourTurnMsg()      { return std::string(YOURTURN)      + "\n"; }
inline std::string makeOpponentTurnMsg()  { return std::string(OPPONENTTURN)  + "\n"; }

// ── Parsers ───────────────────────────────────────────────────────────────────

// Split a line into space-separated tokens (strips the trailing '\n' if present)
inline std::vector<std::string> tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string tok;
    while (iss >> tok) {
        tokens.push_back(tok);
    }
    return tokens;
}

// Parse "ATTACK <row> <col>" → {row, col}
// Returns false if malformed.
inline bool parseAttack(const std::vector<std::string>& tokens, int& row, int& col) {
    if (tokens.size() < 3 || tokens[0] != ATTACK) return false;
    try {
        row = std::stoi(tokens[1]);
        col = std::stoi(tokens[2]);
    } catch (...) { return false; }
    return row >= 0 && row < 10 && col >= 0 && col < 10;
}

// Parse "PLACE <size> <row> <col> <H|V>" → fields
// Returns false if malformed.
inline bool parsePlace(const std::vector<std::string>& tokens,
                        int& size, int& row, int& col, bool& horizontal) {
    if (tokens.size() < 5 || tokens[0] != PLACE) return false;
    try {
        size = std::stoi(tokens[1]);
        row  = std::stoi(tokens[2]);
        col  = std::stoi(tokens[3]);
    } catch (...) { return false; }
    if (tokens[4].empty()) return false;
    horizontal = charToHorizontal(tokens[4][0]);
    return size >= 2 && size <= 5
        && row >= 0 && row < 10
        && col >= 0 && col < 10;
}

// Parse "RESULT <row> <col> <HIT|MISS> [SUNK <shipname>]"
inline std::optional<ResultPayload> parseResult(const std::vector<std::string>& tokens) {
    if (tokens.size() < 4 || tokens[0] != RESULT) return std::nullopt;
    ResultPayload p;
    try {
        p.row = std::stoi(tokens[1]);
        p.col = std::stoi(tokens[2]);
    } catch (...) { return std::nullopt; }
    if (tokens[3] == "HIT")       p.outcome = AttackResult::HIT;
    else if (tokens[3] == "MISS") p.outcome = AttackResult::MISS;
    else return std::nullopt;

    // Optional "SUNK <shipname>" trailer
    if (tokens.size() >= 6 && tokens[4] == "SUNK") {
        p.sunkShipName = tokens[5];
    }
    return p;
}

// ── Validation helpers ────────────────────────────────────────────────────────

inline bool isValidCoord(int row, int col) {
    return row >= 0 && row < 10 && col >= 0 && col < 10;
}

inline bool isValidShipSize(int size) {
    return size == 2 || size == 3 || size == 4 || size == 5;
}

// Ship name lookup (mirrors the logic in Board.cpp so both sides agree)
inline std::string shipName(int size) {
    switch (size) {
        case 5: return "Carrier";
        case 4: return "Battleship";
        case 3: return "Cruiser";
        case 2: return "Destroyer";
        default: return "Unknown";
    }
}

} // namespace Protocol