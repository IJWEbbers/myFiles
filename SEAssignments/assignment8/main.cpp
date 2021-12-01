#include <fstream>
#include <iostream>

#include "dofxyrz.hpp"
#include "dofxyrz.cpp"

int main()
{
    const double DELTA_t_sec{0.1};
    const double MAX_t_sec{10.0};
    double velocity{0.2}; // m/sec
    double angular_velocity{0.25 * PI}; // rad/sec
    double t_sec = 0.0;
    const std::string fileName{"myCSV.csv"};
    DOFxyRz roomba;

    std::ofstream csvFile;
    //Clear the file by creating it again. Append option for appending data
    std::ofstream newFile(fileName, std::ios_base::app);
    csvFile.open(fileName);
    csvFile << "delta_t,x,y,\n";


    while (t_sec <= MAX_t_sec)
    {
        std::cout << "t = " << t_sec << " " << roomba << std::endl;

        // Calculate rotation every simulation step
        roomba = roomba + (angular_velocity * DELTA_t_sec);
        // Calculate translation every simulation step
        CartVec2D delta_heading(roomba.heading() * velocity * DELTA_t_sec);
        std::cout << "deltaHead" << delta_heading << std::endl;
        roomba += delta_heading;
        t_sec += DELTA_t_sec;

        csvFile << t_sec << ","
                << roomba.getX() << ","
                << roomba.getY() << ",\n";
    }
    csvFile.close();

    return 0;
}
