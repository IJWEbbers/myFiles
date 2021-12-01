#include <iostream>
#include <string>
#include "rotationmotor.h"
RotationMotor motor;
string input;
int amount;

int main()
{
   cout << "Command line" << endl;
   while(motor.getSD() != true){
      cin >> input;
      if(input =="start"){
         motor.start();
      }
      if(input == "shutdown"){
         motor.shutdown();
      }
      if(input == "restart"){
         motor.restart();
      }
      if(input == "incRPM"){
         motor.incRPM();
      }
      if(input == "decRPM"){
         motor.decRPM();
      }
      if(input == "getRPM"){
         motor.getRPM();
      }
   }

   return 0;
}
