// GameSession.h
// File for managing the physical TCP socket for a single player

#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>

class GameRoom; // Forward declaration

using boost::asio::ip::tcp;

class GameSession : public std::enable_shared_from_this<GameSession> {
public:
    GameSession(tcp::socket socket);

    void start();
    void set_room(std::shared_ptr<GameRoom> room);
    void deliver(const std::string& msg);

private:
    void do_read();

    tcp::socket socket_;
    std::weak_ptr<GameRoom> room_; // Weak ptr prevents memory leaks
    enum { max_length = 1024 };
    char data_[max_length];
};