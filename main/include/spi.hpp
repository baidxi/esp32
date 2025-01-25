#pragma once

#include <memory>
#include <vector>

#include <driver/spi_master.h>
#include <driver/spi_slave.h>

#include <device.hpp>

class spi_master;
class spi_slave:public device {
private:
    spi_device_handle_t _handle;
    spi_device_interface_config_t _config = {};
    spi_master *_master;
public:
    explicit spi_slave(spi_master *master, const spi_device_interface_config_t *config);
    ~spi_slave();
    int init() override;
    const spi_device_interface_config_t *acquire_config() {
        return &_config;
    }

    int read(char *buf, size_t bufsize) override;
    int write(const char *data, size_t len) override;
};

class spi_master:public device {
private:
    int _host_id;
    spi_bus_config_t _config = {};
    int _dma_chan;
    void *_dma_mem;
    std::vector<spi_device_handle_t> _devices;
public:
    explicit spi_master(int host_id);
    ~spi_master() {
        if (_host_id >= 0)
            spi_bus_free((spi_host_device_t)_host_id);
    };
    spi_master(int host_id, const spi_bus_config_t *config);
    spi_master(int host_id, const spi_bus_config_t *config, int dma_chan);
    int init() override;
    int connect(spi_slave *slave, spi_device_handle_t *_handle);
    int disconnect(spi_device_handle_t handle);
    int read(char *buf, size_t bufsize) override;
    int write(const char *data, size_t len) override;
};