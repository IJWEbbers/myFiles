#include <iostream>
#include <array>
#include "rotationmotor.h"

int main()
{

    std::cout << "Example with the \"&\" (call by reference)" << std::endl;
    std::array<int, 3> ar1{2, -2, 3};
    for(auto& el: ar1)
    {
        std::cout << el << " ";
        el *= 10;
    }
    std::cout << std::endl;

    ar1[10] = 10 * ar1[1];

    for(const auto el: ar1)
    {
        std::cout << el << " ";
    }

    std::cout << std::endl << std::endl;

    std::cout << "Example without the \"&\" (call by reference)" << std::endl;

    std::array<int, 3> ar2{2, -2, 3};

    for(auto el: ar2)
    {
        std::cout << el << " ";
        el *= 10;
    }
    std::cout << std::endl;

    ar2[0] = 10 * ar2[1];

    for(const auto el: ar2)
    {
        std::cout << el << " ";
    }

    std::cout << std::endl << std::endl << std::endl;

    //Rotation motor part
    int motornumber;
    std::array<RotationMotor, 4> motor{{{}, {}, {}, {}}};
    string input;
    int speed;

    cout << "Input your command" << endl;
    while(1){
       std::cin >> input;
       if(input =="start"){
          std::cout << "what motor is this command for?" << std::endl;
          std::cin >> motornumber;
          motor[motornumber].start();
       }
       if(input == "shutdown"){
           std::cout << "what motor is this command for?" << std::endl;
           std::cin >> motornumber;
           motor[motornumber].shutdown();
       }
       if(input == "restart"){
           std::cout << "what motor is this command for?" << std::endl;
           std::cin >> motornumber;
           motor[motornumber].restart();
       }
       if(input == "incRPM"){
           std::cout << "what motor is this command for?" << std::endl;
           std::cin >> motornumber;
           motor[motornumber].incRPM();
       }
       if(input == "decRPM"){
           std::cout << "what motor is this command for?" << std::endl;
           std::cin >> motornumber;
           motor[motornumber].decRPM();
       }
       if(input == "getRPM"){
           std::cout << "what motor is this command for?" << std::endl;
           std::cin >> motornumber;
           motor[motornumber].getRPM();
       }
       if(input == "setRPM"){
           std::cout << "what RPM do the motors need to go?" << std::endl;
           std::cin >> speed;
           for(auto& m: motor)
           {
               m.setRPM(speed);
           }
       }
    }




    return 0;
}

/*
 -  What is the output of the code code block if we remove & in the second line?
    Why?
       > Anwser: In the second loop all the values will be 10 times less.
                  The reason for this is that the '&' stands for call by reference.
                  When you call the array by reference it is possible to change it's
                  values

 - Why should you use const in the second for loop?
       > Anwser: When you make it const it's not possible to change it.
                  In the second for loop we don't need to change so it's better
                  to make it a const

 - The second range-based for-loop does not contain an &.
   What will happen now for el?
       > Anwser: 'el' will copy 'ar' into the array.

 - We can also use ar.at(1) instead of ar[1]. What is the difference?
       > Anwser:


  */
