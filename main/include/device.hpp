#pragma once
#include <cstdint>

class device {

public:
    device() = default;
    virtual ~device() = default;
    virtual int init() = 0;
    virtual int read(char *buf, size_t bufsize) = 0;
    virtual int write(const char *data, size_t len) = 0;
};