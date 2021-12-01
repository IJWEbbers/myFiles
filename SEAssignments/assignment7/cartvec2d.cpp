#include "cartvec2d.hpp"

std::ostream& operator<<(std::ostream &os, const CartVec2D &rhs)
{
    os << "[" << rhs.getX() << ", " << rhs.getY() << "]";
    return os;
}

CartVec2D operator+(const CartVec2D &lhs, const CartVec2D &rhs)
{
    CartVec2D result;
    result += lhs;
    result += rhs;
    return result;
}

CartVec2D operator-(const CartVec2D &lhs, const CartVec2D &rhs)
{
    CartVec2D result;
    result -= lhs;
    result -= rhs;
    return result;
}


CartVec2D &CartVec2D::operator+=(const CartVec2D &rhs)
{
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
}

CartVec2D &CartVec2D::operator-=(const CartVec2D &rhs)
{
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    return *this;
}
