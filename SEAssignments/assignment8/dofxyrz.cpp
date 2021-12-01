#include "dofxyrz.hpp"

#include <cmath>

#include <iostream>


std::ostream& operator<<(std::ostream &os, const DOFxyRz &dof)
{
    //os << "[X:" << dof.getX() << ", Y:" << dof.getY() << ", Rz:" << dof.getRz() << "]";
    os << "[" << dof.CV2D_ <<", Rz:" << dof.getRz() << "]";
    return os;
}

DOFxyRz operator+(const DOFxyRz &dof, const double Rz)
{
    DOFxyRz result;
    result = dof;
    result.Rz_ += Rz;
    while(((result.Rz_ * PI) / 180) >= PI)
    {
        --result.Rz_;
    }
    return result;
}

DOFxyRz operator-(const DOFxyRz &dof, const double Rz)
{
    DOFxyRz result;
    result = dof;
    result.Rz_ -= Rz;
    while(((result.Rz_ * PI) / 180) <= -PI)
    {
        ++result.Rz_;
    }
    return result;
}

DOFxyRz operator+(const CartVec2D &rhs, const DOFxyRz &lhs)
{
    DOFxyRz result;
    result += rhs;
    result += lhs;
    return result;
}

DOFxyRz operator-(const CartVec2D &rhs, const DOFxyRz &lhs)
{
    DOFxyRz result;
    result -= rhs;
    result -= lhs;
    return result;
}

CartVec2D operator*(const DOFxyRz &lhs, const double &rhs)
{
    CartVec2D result;
    result.setX(lhs.getX() * rhs);
    result.setY(lhs.getY() * rhs);
    return result;
}

CartVec2D operator*(const CartVec2D &lhs, const double &rhs)
{
    CartVec2D result;
    result.setX(lhs.getX() * rhs);
    result.setY(lhs.getY() * rhs);
    return result;
}

DOFxyRz &DOFxyRz::operator+=(const CartVec2D &rhs)
{
    double newX = getX();
    newX += rhs.getX();
    setX(newX);
    double newY = getY();
    newY += rhs.getY();
    setY(newY);
    return *this;
}

DOFxyRz &DOFxyRz::operator-=(const CartVec2D &rhs)
{
    double newX = getX();
    newX -= rhs.getX();
    setX(newX);
    double newY = getY();
    newY -= rhs.getY();
    setY(newY);
    return *this;
}

DOFxyRz &DOFxyRz::operator+=(const double &Rz)
{
    double newRz = Rz_;
    newRz += Rz;
    return *this;
}

DOFxyRz &DOFxyRz::operator-=(const double &Rz)
{
    double newRz = Rz_;
    newRz -= Rz;
    return *this;
}

CartVec2D DOFxyRz::heading() const
{
    CartVec2D heading;
    heading.setX(cos(Rz_));
    heading.setY(sin(Rz_));
    std::cout << "RzCOS: " << cos(Rz_) << ", RzSIN: " << sin(Rz_) << ", length: " << "heading" << heading << std::endl;
    return heading;
}
