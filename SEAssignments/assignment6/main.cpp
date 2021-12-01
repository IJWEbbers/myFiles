#include "cartvec2d.hpp"
#include <iostream>


int main()
{
    CartVec2D cv1{-2.0, 1.0};
    CartVec2D cv2{-4.0, 2.0};
    std::cout << "Initial values:" << std::endl
              << "cv1: " << cv1 << std::endl
              << "cv2: " << cv2 << std::endl << std::endl;

    cv1 += cv2;
    std::cout << "added cv2 into cv1 [cv1 += cv2]" << std::endl
              << "cv1: " << cv1 << std::endl
              << "cv2: " << cv2 << std::endl << std::endl;

    cv2 -= cv1;
    std::cout << "substracted cv1 from cv2 [cv2 -= cv1]" << std::endl
              << "cv1: " << cv1 << std::endl
              << "cv2: " << cv2 << std::endl << std::endl;

    std::cout << "added cv2 inline into cv1" << std::endl
              << "cv1: " << cv1 + cv2 << std::endl
              << "cv2: " << cv2 << std::endl << std::endl;

    std::cout << "substracted cv1 from cv2" << std::endl
              << "cv1: " << cv1 << std::endl
              << "cv2: " << cv2 - cv1 << std::endl << std::endl;
}
