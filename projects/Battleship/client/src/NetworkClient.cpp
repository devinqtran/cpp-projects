#include "NetworkClient.h"
#include <iostream>

NetworkClient::NetworkClient() : socket_(io_context_) {}

NetworkClient::~NetworkClient() {
    disconnect();
}

bool NetworkClient::connect(const std::string& host, const std::string& port) {
    try {
        tcp::resolver resolver(io_context_);
        auto endpoints = resolver.resolve(host, port);
        
        // This is a blocking connect. It will pause the game for a split second 
        // while it tries to reach the server.
        boost::asio::connect(socket_, endpoints);

        // Start the background reading loop
        do_read();

        // Launch io_context.run() on a brand new background thread!
        network_thread_ = std::thread([this]() {
            io_context_.run();
        });

        return true;
    } catch (std::exception& e) {
        std::cerr << "Network Client Exception: " << e.what() << "\n";
        return false;
    }
}

void NetworkClient::disconnect() {
    // Gracefully stop the network engine
    boost::asio::post(io_context_, [this]() { socket_.close(); });
    io_context_.stop();
    
    // Wait for the background thread to finish and merge back
    if (network_thread_.joinable()) {
        network_thread_.join();
    }
}

void NetworkClient::send(const std::string& message) {
    // VERY IMPORTANT: Raylib is calling this from the main thread, but 
    // the socket belongs to the background thread. We use boost::asio::post 
    // to safely hand the message over to the background thread's to-do list.
    boost::asio::post(io_context_,
        [this, message]() {
            bool write_in_progress = !write_msgs_.empty();
            write_msgs_.push_back(message);
            if (!write_in_progress) {
                do_write();
            }
        });
}

void NetworkClient::do_write() {
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_msgs_.front()),
        [this](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                write_msgs_.pop_front();
                if (!write_msgs_.empty()) {
                    do_write();
                }
            } else {
                socket_.close();
            }
        });
}

void NetworkClient::do_read() {
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                read_buffer_.append(data_, length);

                size_t pos;
                while ((pos = read_buffer_.find('\n')) != std::string::npos) {
                    std::string line = read_buffer_.substr(0, pos);
                    read_buffer_.erase(0, pos + 1);

                    // Parse the text into our C++ struct
                    Protocol::Message msg = Protocol::parse(line);

                    // LOCK THE MAILBOX: Stop Raylib from reading while we put mail in
                    {
                        std::lock_guard<std::mutex> lock(inbox_mutex_);
                        inbox_.push(msg);
                    } // Mailbox automatically unlocks here
                }
                do_read();
            } else {
                socket_.close();
            }
        });
}

bool NetworkClient::has_message() {
    std::lock_guard<std::mutex> lock(inbox_mutex_);
    return !inbox_.empty();
}

Protocol::Message NetworkClient::pop_message() {
    std::lock_guard<std::mutex> lock(inbox_mutex_);
    Protocol::Message msg = inbox_.front();
    inbox_.pop();
    return msg;
}