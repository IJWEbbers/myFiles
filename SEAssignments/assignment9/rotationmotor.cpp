#include "rotationmotor.hpp"

RotationMotor::~RotationMotor()
{
    std::cerr << "Quiting motor " << Device::getID() << std::endl;
    setRPM(0.0);
}

void RotationMotor::initialise()
{
    std::cout << "Chosen command: \"start\"." << std::endl;
    Device::initialise();
    if(!motorStarted_)
    {
        motorStarted_ = true;
        currentSpeed_ = 0;
        std::cout << "The motor is started."
                  << std::endl << "The current RPM: " << getRPM()
                  << std::endl << std::endl;
    }
    else
        std::cerr << "Motor is already started!" << std::endl << std::endl;
}

void RotationMotor::shutdown()
{
    std::cout << "Chosen command: \"shutdown\"." << std::endl;
    Device::shutdown();
    if(motorStarted_)
    {
        motorStarted_ = false;
        currentSpeed_ = 0;

        std::cout << "The motor is stopped."
                  << std::endl << "\t\t\tThe current RPM: " << getRPM()
                  << std::endl << std::endl;
    }
    else
    {
        std::cerr << "You should start the motor before shutdown"
                  << std::endl << std::endl;
    }
}

void RotationMotor::reset()
{
    std::cout << "Chosen command: \"reset\"." << std::endl;
    Device::reset();
    if(motorStarted_)
    {
        currentSpeed_ = 0;
        std::cout << "The motor is restarted."
                  << std::endl << "\t\t\tCurrent RPM:" << getRPM()
                  << std::endl << std::endl;
    }
    else
    {
        std::cerr << "You should start the motor before restart"
                  << std::endl << std::endl;
    }

}

void CommandProcessor::addCommand(const std::string &command,
                                  CommandProcessor::comandfunction cf)
{
    CommandProcessor::commands_.insert({command, cf});
}

void CommandProcessor::executeCommand(const std::string &command)
{
    auto p = commands_.find(command);
    if(p != end(commands_))
    {
        auto commandfunc = (*p).second;
        commandfunc();
    }
    else
    {
        std::cout << "Command '" << command << "'not found!" << std::endl;
    }
}
