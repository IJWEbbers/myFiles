#include <iostream>
#include <sstream>
#include <vector>

#include "rotationmotor.hpp"

static bool loopMotors = true;
static std::vector<RotationMotor*> RotationMotors;

void getAction(const int number, const size_t selectedMotor);

int main()
{
    std::string myMotorName = "";
    int userInput = 0;
    size_t userMotorSelect = 0;
    size_t totalMotors = 1;

    std::cout << "Welcome to this motor control application."
              << std::endl << std::endl;

    std::cout << "Amount of motors?" << std::endl;
    while(loopMotors)
    {
        std::cin >> totalMotors;
        if(!std::cin.fail())
        {
            if(totalMotors)
            {
                break;
            }
            std::cout << "\n Please give a number that's bigger than '0'\n";

        }
        else {
            std::cout << "\n Please give a number" << "\n";
        }
        std::cin.clear();
        std::cin.ignore(10000,'\n');
    }
    for(size_t i = 0; i < totalMotors; i++)
    {
        std::cout << "Give a name for motor " << i + 1 << std::endl;
        std::cin >> myMotorName;
        RotationMotors.push_back(new RotationMotor(myMotorName));
    }





    while(loopMotors)
    {
        std::cout << "Select the motornumber:" << std::endl
                  << "\tnumbers 1 to " << totalMotors << " can be provided"
                  << std::endl << "\t > ";
        while(loopMotors)
        {
            std::cin >> userMotorSelect;
            if(!std::cin.fail())
            {
                if(userMotorSelect >= 1 && userMotorSelect <= totalMotors)
                {
                    break;
                }
                std::cout << "Please give a number between 1 and "
                          << totalMotors << "!\n\t > ";
            }
            else {
                std::cout << "This was not a number. Please enter a number\n"
                          << std::endl;
            }
            std::cin.clear();
            std::cin.ignore(10000,'\n');
        }
        std::cout << "\tMotor "
                  << RotationMotors[userMotorSelect - 1]->Device::getID()
                  << " selected!";

        std::cout << std::endl
                  << "Please select a command in the list below:" << std::endl
                  << "\t 1 = initialise"       << std::endl
                  << "\t 2 = reset"    << std::endl
                  << "\t 3 = shutdown"    << std::endl
                  << "\t 4 = setRPM"      << std::endl
                  << "\t 5 = getRPM"      << std::endl
                  << "\t 6 = stop application"      << std::endl;

        while(loopMotors)
        {
            std::cin >> userInput;
            if(!std::cin.fail())
            {
                getAction(userInput, userMotorSelect - 1);
                break;
            }
            else
            {
                std::cout << "This was not a number. Please enter a number\n\t > "
                          << std::endl;
            }
            std::cin.clear();
            std::cin.ignore(10000,'\n');
        }
    }
    for(size_t i = 0; i < totalMotors; i++)
    {
        RotationMotors[i]->~RotationMotor();
    }
    return 0;
}

void getAction(const int number, const size_t selectedMotor)
{
    switch(number)
    {
    case 1: //Initialise
        RotationMotors[selectedMotor]->initialise();
        break;
    case 2: //reset
        RotationMotors[selectedMotor]->reset();
        break;
    case 3: //shutdown
        RotationMotors[selectedMotor]->shutdown();
        break;
    case 4: //setRPM
        std::cout << "Please give a desired speed: ";
        while(1)
        {
            double userInput;
            std::cin >> userInput;
            if(!std::cin.fail())
            {
                RotationMotors[selectedMotor]->setRPM(userInput);
                break;
            }
            else
            {
                std::cout << "This was not a number. Please enter a number\n"
                          << std::endl;
            }
            std::cin.clear();
            std::cin.ignore(10000,'\n');
        }
        break;
    case 5: //getRPM
        std::cout << "Current RPM is: "
                  << RotationMotors[selectedMotor]->getRPM() << std::endl;
        break;
    case 6: //stop
        loopMotors=false;
        break;
    default:
        std::cout << "The given number is incorrect.";
        break;
    }
}
