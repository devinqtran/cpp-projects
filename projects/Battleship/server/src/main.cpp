#include <iostream>
#include <boost/asio.hpp>
#include "BattleshipServer.h"

int main()
{
    try
    {
        boost::asio::io_context io_context;
        BattleshipServer server(io_context, 8080);

        std::cout << "Battleship server running on port 8080...\n";
        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}