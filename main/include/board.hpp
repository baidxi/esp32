#pragma once

#include <spi.hpp>

#include <esp_lcd_types.h>

class board;

board *board_create();
class board {
protected:
    spi_master *_spi_master[SPI_HOST_MAX] = {};
    esp_lcd_panel_handle_t _lcd_panel;
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
};

#define DECLEAR_BOARD(BOARD_NAME) board *board_create()   \
{   \
    return new BOARD_NAME();    \
}