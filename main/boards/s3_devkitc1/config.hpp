#pragma once

#include <driver/gpio.h>

#define SPI1_ENABLED    0
#define SPI2_ENABLED    0
#define SPI3_ENABLED    1

#define SPI3_CLK       GPIO_NUM_12 
#define SPI3_MOSI      GPIO_NUM_13
#define SPI3_MISO      GPIO_NUM_11
#define SPI3_CS0       GPIO_NUM_10