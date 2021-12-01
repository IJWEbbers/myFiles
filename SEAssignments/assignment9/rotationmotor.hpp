#ifndef ROTATIONMOTOR_H
#define ROTATIONMOTOR_H

#include <string>
#include <iostream>
#include <map>
#include <functional>

#include "device.hpp"

class RotationMotor : public Device
{
public:
    RotationMotor(const std::string &deviceID): Device(deviceID), currentSpeed_(0) {  }
    virtual ~RotationMotor() override;

    virtual void initialise() override;
    virtual void shutdown() override;
    virtual void reset() override;

    void setRPM(const double speed) {
        std::cout << "Set motor speed to " << speed << " RPM." << std::endl;
        currentSpeed_ = speed;
    }
    double getRPM() const { return currentSpeed_; }

private:
    bool motorStarted_;
    double currentSpeed_;
};

class CommandProcessor
{
public:
    using comandfunction = std::function<void()>;

    CommandProcessor() {}
    void addCommand(const std::string &command,
                    CommandProcessor::comandfunction cf);
    void executeCommand(const std::string &command);

private:
    std::map<std::string, CommandProcessor::comandfunction> commands_;

};
#endif // ROTATIONMOTOR_H
