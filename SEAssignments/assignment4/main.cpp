#include <iostream>
#include "dataframe.hpp"

using namespace std;

int main()
{
    std::array<std::uint8_t, 255> externalDataframe = {0};
    externalDataframe[0] = 19;
    externalDataframe[1] = 3;
    externalDataframe[2] = 15;
    externalDataframe[3] = 3;
    externalDataframe[4] = 15;
    externalDataframe[5] = 200;

    std::array<std::uint8_t, 255> someData = {0};
    someData[0] = 5;
    someData[1] = 15;
    someData[2] = 3;
    someData[3] = 15;

   Dataframe dataframeObject;

   printf("empty dataframe\n");
   dataframeObject.showAll();

   dataframeObject.setDataframe(externalDataframe);
   printf("setDataframe\n");
   dataframeObject.show();

   if(dataframeObject.checksumIsCorrect())
   {
       printf("checksum is correct\n");
   }
   else
   {
       printf("checksum is not correct\n");
   }

   dataframeObject.clear();
   printf("clear dataframe\n");
   dataframeObject.showAll();

   dataframeObject.setData(someData, 4);
   printf("set data\n");
   dataframeObject.show();

   if(dataframeObject.checksumIsCorrect())
   {
       printf("checksum is correct\n");
   }
   else
   {
       printf("checksum is not correct\n");
   }

   return 0;
}
