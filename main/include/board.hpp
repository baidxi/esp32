#pragma once

#include <display.hpp>
#include <spi.hpp>

class board;

board *board_create();
class board {
protected:
    spi_master *_spi_master[SPI_HOST_MAX] = {};
    display *_display;
public:
    board() = default;
    ~board() = default;
    virtual int init() = 0;
    static board &get_instance() {
        static board *_instance = nullptr;

        if (_instance == nullptr)
            _instance = board_create();

        return *_instance;
    }

    display *get_display() {
        return _display;
    }
};

#define DECLEAR_BOARD(BOARD_NAME) board *board_create()   \
{   \
    return new BOARD_NAME();    \
}