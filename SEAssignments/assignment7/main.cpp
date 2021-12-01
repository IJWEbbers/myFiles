#include <iostream>

#include "dofxyrz.hpp"


int main()
{
    DOFxyRz myDofOne(6,4);
    myDofOne.setRz(25.3);
    DOFxyRz myDofTwo(64,34);
    myDofTwo.setRz(64.7);
    std::cout << "Initial values:" << std::endl
              << "myDofOne: " << myDofOne << std::endl
              << "myDofTwo: " << myDofTwo << std::endl;

    myDofOne += myDofTwo;
    std::cout << "Used the += [myDofOne += myDofTwo]:" << std::endl
              << "myDofOne: " << myDofOne << std::endl
              << "myDofTwo: " << myDofTwo << std::endl << std::endl;

    myDofOne -= myDofTwo;
    std::cout << "Used the -= [myDofOne -= myDofTwo]:" << std::endl
              << "myDofOne: " << myDofOne << std::endl
              << "myDofTwo: " << myDofTwo << std::endl << std::endl;

    std::cout << "Added inline [myDofOne + myDofTwo]:" << std::endl
              << "myDofOne: " << myDofOne + myDofTwo << std::endl << std::endl;

    std::cout << "Substract inline [myDofOne - myDofTwo]:" << std::endl
              << "myDofOne: " << myDofOne - myDofTwo << std::endl << std::endl;

    std::cout << "Added the angle inline [myDof... + angle 26.34]:" << std::endl
              << "myDofOne: " << myDofOne + 26.34  << std::endl
              << "myDofTwo: " << myDofTwo + 26.34 << std::endl << std::endl;

    std::cout << "Substracted the angle inline [myDof... - angle 26.34]:"
              << std::endl
              << "myDofOne: " << myDofOne - 26.34  << std::endl
              << "myDofTwo: " << myDofTwo - 26.34 << std::endl << std::endl;

    std::cout << "Made the angle biger than PIE [myDof... - angle 360]:"
              << std::endl
              << "myDofOne: " << myDofOne + 360  << std::endl
              << "myDofTwo: " << myDofTwo + 360 << std::endl << std::endl;

    std::cout << "Made the angle smaller than -PIE [myDof... - angle 360]:"
              << std::endl
              << "myDofOne: " << myDofOne - 360  << std::endl
              << "myDofTwo: " << myDofTwo - 360 << std::endl << std::endl;

    myDofOne.setRz(186);
    myDofTwo.setRz(217);
    myDofOne += myDofOne.heading();
    myDofTwo += myDofTwo.heading();
    std::cout << "Added the heading calculation dof1=186, DOF2=217:"
              << std::endl
              << "myDofOne: " << myDofOne << std::endl
              << "myDofTwo: " << myDofTwo << std::endl << std::endl;
    return 0;
}
