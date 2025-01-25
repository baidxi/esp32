#include <cstring>
#include <algorithm>

#include <spi.hpp>

spi_slave::spi_slave(spi_master *master, const spi_device_interface_config_t *config):
_handle(nullptr),
_master(master)
{
    ::memcpy(&_config, config, sizeof(_config));
}

spi_slave::~spi_slave()
{
    if (_handle)
        _master->disconnect(_handle);
    
    _handle = nullptr;
}

int spi_slave::init()
{
    if (_master) {
        return _master->connect(this, &_handle);
    }

    return -ESP_ERR_NOT_FOUND;
}

int spi_slave::read(char *buf, size_t bufsize)
{
    return 0;
}

int spi_slave::write(const char *data, size_t len)
{
    return 0;
}

static const spi_bus_config_t bus_config = {

};

spi_master::spi_master(int host_id):
_host_id(host_id),
_dma_chan(0)
{

}

spi_master::spi_master(int host_id, const spi_bus_config_t *config):
_host_id(host_id),
_dma_chan(0)
{
    ::memcpy(&_config, config, sizeof(_config));
}

spi_master::spi_master(int host_id, const spi_bus_config_t *config, int dma_chan):
_host_id(host_id),
_dma_chan(dma_chan)
{
    ::memcpy(&_config, config, sizeof(_config));
}

int spi_master::init()
{
    esp_err_t err = spi_bus_initialize((spi_host_device_t)_host_id,_config.data0_io_num ? &_config : &bus_config, _dma_chan ? _dma_chan : SPI_DMA_DISABLED);
    if (err != ESP_OK)
        return err;

    if (_dma_chan) {
        _dma_mem = spi_bus_dma_memory_alloc((spi_host_device_t)_host_id, SPI_MAX_DMA_LEN, 0);

        if (!_dma_mem) {
            return -ESP_ERR_NO_MEM;  
        }
    }

    return 0;
}

int spi_master::connect(spi_slave *slave, spi_device_handle_t *_handle)
{
    spi_device_handle_t handle = nullptr;
    esp_err_t err;

    err = spi_bus_add_device((spi_host_device_t)_host_id, slave->acquire_config(), &handle);
    if (err != ESP_OK) {
        return err;
    }

    _devices.push_back(handle);

    *_handle = handle;

    return err;
}

int spi_master::disconnect(spi_device_handle_t handle)
{
    (void)std::remove_if(_devices.begin(), _devices.end(), [handle](spi_device_handle_t _handle){
        return handle == _handle;
    });

    return spi_bus_remove_device(handle);
}

int spi_master::write(const char *data, size_t len)
{
    return 0;
}

int spi_master::read(char *buf, size_t bufsize)
{
    return 0;
}