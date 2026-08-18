// GameSession.h
// File for managing the physical TCP socket for a single player

#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <deque>

class GameRoom; // Forward declaration

using boost::asio::ip::tcp;

class GameSession : public std::enable_shared_from_this<GameSession> {
public:
    GameSession(tcp::socket socket);

    void start();
    void set_room(std::shared_ptr<GameRoom> room);

    // public method called by GameRoom for delivering messages
    void deliver(const std::string& msg);

private:
    void do_read();

    // private method to process messages in the queue
    void do_write();

    tcp::socket socket_;
    std::weak_ptr<GameRoom> room_; // Weak ptr prevents memory leaks
    enum { max_length = 1024 };
    char data_[max_length];

    // Message queue to solve data race issue
    std::deque<std::string> write_msgs_;

    // std::string buffer for holding the incoming chunks of text from TCP stream
    std::string read_buffer_;
};