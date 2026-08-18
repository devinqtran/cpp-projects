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
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(msg),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            if (ec) {
                std::cerr << "Write error: " << ec.message() << "\n";
            }
        });
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
            }
        });
}