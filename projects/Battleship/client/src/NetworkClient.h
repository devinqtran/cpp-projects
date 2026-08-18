#pragma once

// --- THE WINDOWS/RAYLIB FIX ---
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOGDI               
    #define NOUSER              
    
    // Only define NOMINMAX if the compiler hasn't already done it
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
#endif
// ------------------------------

#include <boost/asio.hpp>
#include <string>
#include <queue>
#include <deque>
#include <thread>
#include <mutex>
#include "Protocol.h" // Shared dictionary

using boost::asio::ip::tcp;

class NetworkClient
{
public:
    NetworkClient();
    ~NetworkClient();

    // Connects to the server. Returns true if successful.
    bool connect(const std::string &host, const std::string &port);

    // Safely shuts down the background thread
    void disconnect();

    // Puts a message in the outgoing queue (called by Raylib thread)
    void send(const std::string &message);

    // Checks if the background thread has put any new messages in the mailbox
    bool has_message();

    // Retrieves the oldest message from the mailbox
    Protocol::Message pop_message();

private:
    void do_read();
    void do_write();

    boost::asio::io_context io_context_;
    tcp::socket socket_;
    std::thread network_thread_;

    // Reading buffer
    enum
    {
        max_length = 1024
    };
    char data_[max_length];
    std::string read_buffer_;

    // Writing queue
    std::deque<std::string> write_msgs_;

    // The Mailbox (Inbox) - Shared between Raylib and Boost.Asio
    std::queue<Protocol::Message> inbox_;
    std::mutex inbox_mutex_; // Locks the mailbox so both threads don't crash it
};