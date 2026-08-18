#include <iostream>
#include <memory>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
class GameRoom;

// Handles an individual game connection
class GameSession : public std::enable_shared_from_this<GameSession>
{
public:
    GameSession(tcp::socket socket) : socket_(std::move(socket)) {}

    void start()
    {
        do_read();
    }

    void set_room(std::shared_ptr<GameRoom> room)
    {
        room_ = room;
    }

    // Method called by GameRoom to send a message to the specific player
    void deliver(const std::string &msg)
    {
        // Note: For a production server, you need a queue here to prevent
        // overlapping async_writes. For simplicity, we write directly.
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(msg),
                                 [this, self](boost::system::error_code ec, std::size_t /*length*/)
                                 {
                                     if (ec)
                                     {
                                         // Handle disconnect
                                     }
                                 });
    }

private:
    void do_read()
    {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                [this, self](boost::system::error_code ec, std::size_t length)
                                {
                                    if (!ec)
                                    {
                                        std::string message(data_, length);

                                        // Route the message to the GameRoom instead of echoing
                                        if (auto room = room_.lock())
                                        {
                                            room->route_message(message, self);
                                        }

                                        do_read(); // Keep reading
                                    }
                                });
    }

    tcp::socket socket_;
    std::weak_ptr<GameRoom> room_; // Weak pointer prevents memory leak
    enum
    {
        max_length = 1024
    };
    char data_[max_length];
};

// Listens for and accepts new players (greeter)
class BattleshipServer
{
public:
    BattleshipServer(boost::asio::io_context &io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    {
        do_accept();
    }

private:
    void do_accept()
    {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                    auto new_session = std::make_shared<GameSession>(std::move(socket));

                    if (!waiting_player_)
                    {
                        // Nobody is waiting. This player becomes the waiting player.
                        waiting_player_ = new_session;
                        waiting_player_->deliver("Waiting for an opponent to connect...\n");
                        waiting_player_->start();
                    }
                    else
                    {
                        // Someone is waiting! Create a room and pair them up.
                        auto room = std::make_shared<GameRoom>();
                        room->add_player(waiting_player_);
                        room->add_player(new_session);

                        // Keep the room alive in memory
                        active_rooms_.push_back(room);

                        new_session->start();

                        // Clear the waiting slot for the next person
                        waiting_player_ = nullptr;
                    }
                }
                do_accept();
            });
    }

    tcp::acceptor acceptor_;
    std::shared_ptr<GameSession> waiting_player_;
    std::vector<std::shared_ptr<GameRoom>> active_rooms_;
};

// GameRoom class for (matchmaking)
class GameRoom : public std::enable_shared_from_this<GameRoom>
{
public:
    void add_player(std::shared_ptr<GameSession> player)
    {
        if (!player1_)
        {
            player1_ = player;
            player1_->set_room(shared_from_this());
        }
        else if (!player2_)
        {
            player2_ = player;
            player2_->set_room(shared_from_this());

            // Both players are here, start the game
            broadcast("Game matched! The game begins now.\n");
        }
    }

    void route_message(const std::string &message, std::shared_ptr<GameSession> sender)
    {
        // If Player 1 sent the message, deliver it to Player 2
        if (sender == player1_ && player2_)
        {
            player2_->deliver("Opponent: " + message);
        }
        // If Player 2 sent the message, deliver it to Player 1
        else if (sender == player2_ && player1_)
        {
            player1_->deliver("Opponent: " + message);
        }
    }

private:
    void broadcast(const std::string &message)
    {
        if (player1_)
            player1_->deliver(message);
        if (player2_)
            player2_->deliver(message);
    }

    std::shared_ptr<GameSession> player1_;
    std::shared_ptr<GameSession> player2_;
};

int main()
{
    try
    {
        boost::asio::io_context io_context;

        // Start listening on port 8080
        BattleshipServer server(io_context, 8080);
        std::cout << "Battleship server running on port 8080...\n";

        // This blocks and runs the event loop until the server shuts down
        io_context.run(); // looks for player connections, data arrival and triggers call backs
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}