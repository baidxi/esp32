#include <iostream>
#include <application.hpp>
#include <board.hpp>

application::application()
{

}

application::~application()
{

}

void application::start()
{
    auto& board = board::get_instance();

    board.init();
}