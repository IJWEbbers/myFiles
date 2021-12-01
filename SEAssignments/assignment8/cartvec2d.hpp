#ifndef CARTVEC2D_HPP
#define CARTVEC2D_HPP

#include <ostream>

class CartVec2D
{
public:
    friend std::ostream& operator<<(std::ostream &os, const CartVec2D &rhs);
    friend CartVec2D operator+(const CartVec2D &lhs, const CartVec2D &rhs);
    friend CartVec2D operator-(const CartVec2D &lhs, const CartVec2D &rhs);

public:
    CartVec2D(double x, double y): x_(x), y_(y){}
    CartVec2D(): CartVec2D(0.0, 0.0) {}
    CartVec2D(const CartVec2D &other): x_(other.getX()), y_(other.getY()) {}
    ~CartVec2D() = default;

    CartVec2D &operator+=(const CartVec2D &rhs);
    CartVec2D &operator-=(const CartVec2D &rhs);

    double length() const;

    void setX(const double x) {x_=x;}
    double getX() const {return x_;}

    void setY(const double y) {y_=y;}
    double getY() const {return y_;}

private:
    double x_, y_;

};

#endif // CARTVEC2D_HPP
