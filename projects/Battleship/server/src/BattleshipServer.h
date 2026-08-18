// BattleshipServer.h
// Main listener that will accept incoming connections and route them to waiting rooms

#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <vector>

// Forward declarations
class GameSession;
class GameRoom;

using boost::asio::ip::tcp;

class BattleshipServer {
public:
    BattleshipServer(boost::asio::io_context& io_context, short port);

private:
    void do_accept();

    tcp::acceptor acceptor_;
    std::shared_ptr<GameSession> waiting_player_;
    std::vector<std::shared_ptr<GameRoom>> active_rooms_;
};