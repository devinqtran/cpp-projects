#include "GameSession.h"
#include "GameRoom.h"
#include <iostream>

GameSession::GameSession(tcp::socket socket) : socket_(std::move(socket)) {}

void GameSession::start() {
    do_read();
}

void GameSession::set_room(std::shared_ptr<GameRoom> room) {
    room_ = room;
}

void GameSession::deliver(const std::string& msg) {
    // Check to see if writing is in progress before adding a new message
    bool write_in_progress = !write_msgs_.empty();

    // Add a new message to the back of the queue
    write_msgs_.push_back(msg);

    // process messages in the queue
    if (!write_in_progress) {
        do_write();
    }
}

void GameSession::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::string message(data_, length);
                
                if (auto room = room_.lock()) {
                    room->route_message(message, self);
                }
                
                do_read();
            } else {
                std::cerr << "Player disconnected: " << ec.message() << "\n";
            }
        });
}

void GameSession::do_write() {
    auto self(shared_from_this()); // shared_from_this() allows class to safely create shared_ptr to themselves
    
    // Write the message at the front of the queue
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_msgs_.front()),
        // lambda function that will run when player presses "Fire"
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            // if no error code...
            if (!ec) {
                // The message was sent successfully! Remove it from the queue.
                write_msgs_.pop_front();
                
                // If there are more messages waiting, fire off the next write
                if (!write_msgs_.empty()) {
                    do_write();
                }
            } else {
                std::cerr << "Write error: " << ec.message() << "\n";
                // If there's an error (e.g., player disconnected), the connection 
                // will drop naturally, so we don't call do_write() again.
            }
        });
}