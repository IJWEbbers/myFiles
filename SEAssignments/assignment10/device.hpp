#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <string>

class Device
{
public:
    Device(const std::string &id);
    virtual ~Device() = default;

    const std::string &getID() const {return ID_; }
    ///The abstract functions:
    virtual void initialise() = 0;
    virtual void reset() = 0;
    virtual void shutdown() = 0;

private:
    const std::string ID_;
};

#endif // DEVICE_HPP
