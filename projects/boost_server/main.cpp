#include <iostream>
#include <memory>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

// Handles an individual game connection
class GameSession : public std::enable_shared_from_this<GameSession> {
public:
    GameSession(tcp::socket socket) : socket_(std::move(socket)) {}

    void start() {
        do_read();
    }

private:
    void do_read() {
        // Keep the session alive while the async operation runs
        auto self(shared_from_this());
        
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
            [this, self](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    std::cout << "Received move: " << std::string(data_, length);
                    do_write(length); // Echo it back
                }
            });
    }

    void do_write(std::size_t length) {
        auto self(shared_from_this());
        
        boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
            [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    // Once data is sent, go back to waiting for the next turn
                    do_read(); 
                }
            });
    }

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
};

// Listens for and accepts new players
class BattleshipServer {
public:
    BattleshipServer(boost::asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        do_accept();
    }

private:
    void do_accept() {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    // A new player connected! Create a session for them
                    std::make_shared<GameSession>(std::move(socket))->start();
                }
                // Immediately go back to listening for the next connection
                do_accept(); 
            });
    }

    tcp::acceptor acceptor_;
};

int main() {
    try {
        boost::asio::io_context io_context;
        
        // Start listening on port 8080
        BattleshipServer server(io_context, 8080);
        std::cout << "Battleship server running on port 8080...\n";
        
        // This blocks and runs the event loop until the server shuts down
        io_context.run(); 
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}