#pragma once

#include <driver/i2c_master.h>
#include <driver/i2c_slave.h>

#include <device.hpp>

class i2c_master;

class i2c_slave:public device {
private:
    i2c_master *_master;
    i2c_slave_config_t _config = {};
    i2c_slave_dev_handle_t _handle;
public:
    explicit i2c_slave(i2c_master *master, const i2c_slave_config_t *config);
    ~i2c_slave();
    int init() override;
};

class i2c_master: public device {

};