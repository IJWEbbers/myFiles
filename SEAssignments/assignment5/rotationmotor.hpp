#ifndef ROTATIONMOTOR_H
#define ROTATIONMOTOR_H
#include <iostream>
#include <string>
using namespace std;
class RotationMotor{
   int RPM = 0;
   int static const maxRPM = 500;
   int static const minRPM = -500;
   int const amount = 100;
   bool on = false;
   bool SD = false;
public:
   void start(){
      if(on == false){
         on = true;
         cout << "motor started" << endl;
      }
      else{
         cerr << "motor already turned on!" << endl;
      }
   }
   void shutdown(){
      if(on == true){
         RPM = 0;
         SD = true;
         cout << "motor shutdown" << endl;
      }
      else{
         cerr << "motor not turned on!" << endl;
      }
   }
   void restart(){
      if(on == true){
         RPM = 0;
         cout << "motor restart" << endl;
      }
      else{
         cerr << "motor not turned on!" << endl;
      }
   }
   void incRPM(){
      if(on == true){
         if(RPM + amount <= maxRPM){
            RPM = RPM + amount;
         }
         else{
            RPM = maxRPM;
         }
         cout << "motor turns at " << RPM << "RPM" << endl;

      }
      else{
         cerr << "motor not turned on!" << endl;
      }
   }
   void decRPM(){
      if(on == true){
         if(RPM - amount >= minRPM){
            RPM = RPM - amount;
         }
         else{
            RPM = minRPM;
         }
         cout << "motor turns at " << RPM << "RPM" << endl;
      }
      else{
         cerr << "motor not turned on!" << endl;
      }
   }
   void getRPM()const{
       if(on == true){
          cout << "motor turns at " << RPM << "RPM" << endl;
       }
       else{
         cerr << "motor not turned on!" << endl;
       }
   }
   bool getSD()const{return SD;}
};

#endif // ROTATIONMOTOR_H
