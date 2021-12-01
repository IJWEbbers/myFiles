#include <iostream>
#include "commandprocessor.hpp"
#include "rotationmotor.hpp"

int main()
{
    RotationMotor motor1;
    CommandProcessor cmdp;

    cmdp.addCommand("start", std::bind(&RotationMotor::start, &motor1));
    cmdp.addCommand("shutdown", std::bind(&RotationMotor::shutdown, &motor1));
    cmdp.addCommand("restart", std::bind(&RotationMotor::restart, &motor1));
    cmdp.addCommand("incRPM", std::bind(&RotationMotor::incRPM, &motor1));
    cmdp.addCommand("decRPM", std::bind(&RotationMotor::decRPM, &motor1));
    cmdp.addCommand("getRPM", std::bind(&RotationMotor::getRPM, &motor1));

    std::cout << "Please select a command in the list below:" << std::endl
              << "* start"      << std::endl
              << "* shutdown"   << std::endl
              << "* restart"    << std::endl
              << "* incRPM"    << std::endl
              << "* decRPM"     << std::endl
              << "* getRPM"     << std::endl;

    do
    {
        std::string testInput;
        std::cin >> testInput;
        cmdp.executeCommand(testInput);
        std::cout << "Please select a command" << std::endl;
    }while(1);
}
