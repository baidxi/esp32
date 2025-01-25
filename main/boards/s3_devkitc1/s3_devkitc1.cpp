#include <board.hpp>
#include "config.hpp"

class s3_devkitc1: public board
{
public:
    s3_devkitc1();
    ~s3_devkitc1();
    int init() override;
};

s3_devkitc1::s3_devkitc1()
{
    spi_bus_config_t config = {};

    if (SPI0_ENABLED) {

    }

    if (SPI1_ENABLED) {

    }

    if (SPI2_ENABLED) {

    }

    if (SPI3_ENABLED) {
        config.mosi_io_num = SPI3_MOSI;
        config.miso_io_num = SPI3_MISO;
        config.max_transfer_sz = SPI_MAX_DMA_LEN;
        config.sclk_io_num = SPI3_CLK;
        _spi_master[SPI3_HOST] = new spi_master(SPI3_HOST, &config, SPI_DMA_CH_AUTO);
    }

    _display = new display();
}

s3_devkitc1::~s3_devkitc1()
{
    for (spi_master *master: _spi_master) {
        if (master)
            delete master;
    }
}

int s3_devkitc1::init()
{
    return 0;
}

DECLEAR_BOARD(s3_devkitc1)