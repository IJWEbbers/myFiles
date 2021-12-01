#ifndef DOFXYRZ_HPP
#define DOFXYRZ_HPP

#include <ostream>
#include "cartvec2d.hpp"

const double PI{3.1415926535897932385};

class DOFxyRz : public CartVec2D
{
public:
    friend std::ostream& operator<<(std::ostream &os, const DOFxyRz &dof);
    friend DOFxyRz operator+(const DOFxyRz &dof, const double Rz);
    friend DOFxyRz operator-(const DOFxyRz &dof, const double Rz);

    friend DOFxyRz operator+(const CartVec2D &rhs, const DOFxyRz &lhs);
    friend DOFxyRz operator-(const CartVec2D &rhs, const DOFxyRz &lhs);

    //Added after issues with the DOF_roomba (ex08):
    friend CartVec2D operator*(const DOFxyRz &lhs, const double &rhs);
    friend CartVec2D operator*(const CartVec2D &lhs, const double &rhs);

public:
    DOFxyRz(const int x, const int y) : CV2D_(x, y) {}
    DOFxyRz() : DOFxyRz(0,0) {}
    virtual ~DOFxyRz() = default;

    void setRz(const double Rz) { Rz_ = Rz; }
    double getRz() const { return Rz_; }

    CartVec2D heading() const;

    DOFxyRz &operator+=(const CartVec2D &rhs);
    DOFxyRz &operator-=(const CartVec2D &rhs);

    //Added after issues with the DOF_roomba (ex08):
    DOFxyRz &operator+=(const double &Rz);
    DOFxyRz &operator-=(const double &Rz);

private:
    CartVec2D CV2D_;
    double Rz_;
};

#endif // DOFXYRZ_HPP
