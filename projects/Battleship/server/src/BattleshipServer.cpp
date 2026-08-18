#include "BattleshipServer.h"
#include "GameSession.h"
#include "GameRoom.h"

BattleshipServer::BattleshipServer(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    do_accept();
}

void BattleshipServer::do_accept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                auto new_session = std::make_shared<GameSession>(std::move(socket));
                
                if (!waiting_player_) {
                    waiting_player_ = new_session;
                    waiting_player_->deliver("Waiting for an opponent to connect...\n");
                    waiting_player_->start();
                } else {
                    auto room = std::make_shared<GameRoom>();
                    room->add_player(waiting_player_);
                    room->add_player(new_session);
                    
                    active_rooms_.push_back(room);
                    
                    new_session->start();
                    waiting_player_ = nullptr; 
                }
            }
            do_accept(); 
        });
}