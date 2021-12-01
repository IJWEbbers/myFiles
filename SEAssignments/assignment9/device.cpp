 #include "device.hpp"

#include <iostream>

Device::Device(const std::string &id): ID_(id) {}

void Device::initialise()
{
    std::cout << "Device class: Initialise " << ID_ << std::endl;
}

void Device::reset()
{
    std::cout << "Device class: Reset " << ID_ << std::endl;
}

void Device::shutdown()
{
    std::cout << "Device class: Shutdown " << ID_ << std::endl;

}


