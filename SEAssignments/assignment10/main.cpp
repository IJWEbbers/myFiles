#include <iostream>
#include <vector>
#include <string>
#include "device.hpp"
#include "rotationmotor.hpp"


int main()
{
    RotationMotor *MotorOne = new RotationMotor("one");
    RotationMotor *MotorTwo = new RotationMotor("two");

    RotationMotor *MotorNull1 = nullptr;
    RotationMotor *MotorNull2 = nullptr;
    RotationMotor *MotorNull3 = nullptr;

    std::vector<Device *> devices;

    devices.push_back(MotorOne);
    devices.push_back(MotorTwo);
    devices.push_back(MotorNull1);
    devices.push_back(MotorNull2);
    devices.push_back(MotorNull3);
    for(auto &e: devices)
    {
        std::cout << e->getID() << std::endl;
        e->reset();
    }

    return 0;
}
