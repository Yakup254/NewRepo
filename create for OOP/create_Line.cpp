#include <iostream>
#include <cmath>

#include "Line.h"

using namespace std;

const double EPS = 1e-9;

Line::Line()
{
    setCoefficients(1, 0, 0);
}

Line::Line(double a_val, double b_val, double c_val)
{
    setCoefficients(a_val, b_val, c_val);
}

Line::Line(const Line& other)
{
    a_ = other.a_;
    b_ = other.b_;
    c_ = other.c_;
}

Line::~Line()
{
}

void Line::setCoefficients(double a_val, double b_val, double c_val)
{
    if (fabs(a_val) < EPS && fabs(b_val) < EPS)
    {
        cout << " ќшибка: коэффициенты 'a' и 'b' не могут быть равны 0 одновременно!\n";
        a_ = 1.0;
        b_ = 0.0;
        c_ = 0.0;
    }
    else
    {
        a_ = a_val;
        b_ = b_val;
        c_ = c_val;
    }
}

void Line::printLine() const
{
    cout << a_ << "x";

    if (b_ >= 0) {
        cout << " + " << b_ << "y";
    }
    else {
        cout << " - " << fabs(b_) << "y";
    }

    if (c_ >= 0) {
        cout << " + " << c_;
    }
    else {
        cout << " - " << fabs(c_);
    }
    cout << " = 0" << endl;
}

void Line::readLine()
{
    double a_in, b_in, c_in;
    cout << "¬ведите коэффициенты a, b, c через пробел: ";
    cin >> a_in >> b_in >> c_in;
    setCoefficients(a_in, b_in, c_in);
}

double Line::getA() const { return a_; }
double Line::getB() const { return b_; }
double Line::getC() const { return c_; }

void Line::setA(double val) { setCoefficients(val, b_, c_); }
void Line::setB(double val) { setCoefficients(a_, val, c_); }
void Line::setC(double val) { c_ = val; }

bool Line::passesOrigin() const
{
    return fabs(c_) < EPS;
}

bool Line::isParallelToOx() const
{
    return (fabs(a_) < EPS && fabs(b_) > EPS);
}

bool Line::getIntercepts(double& xIntercept, double& yIntercept) const
{
    if (fabs(a_) < EPS || fabs(b_) < EPS)
    {
        return false;
    }
    xIntercept = -c_ / a_;
    yIntercept = -c_ / b_;

    if (fabs(xIntercept) < EPS) xIntercept = 0;
    if (fabs(yIntercept) < EPS) yIntercept = 0;
    return true;
}

bool Line::getSlope(double& slope) const
{
    if (fabs(b_) < EPS)
    {
        return false;
    }
    slope = -a_ / b_;
    if (fabs(slope) < EPS) slope = 0;
    return true;
}

bool Line::operator==(const Line& other) const
{
    bool cond1 = fabs(a_ * other.b_ - other.a_ * b_) < EPS;
    bool cond2 = fabs(a_ * other.c_ - other.a_ * c_) < EPS;
    bool cond3 = fabs(b_ * other.c_ - other.b_ * c_) < EPS;
    return cond1 && cond2 && cond3;
}

bool Line::isParallel(const Line& other) const
{
    bool parallelCheck = fabs(a_ * other.b_ - other.a_ * b_) < EPS;
    bool notIdentical = !(*this == other);
    return parallelCheck && notIdentical;
}

bool Line::containsPoint(double x0, double y0) const
{
    return fabs(a_ * x0 + b_ * y0 + c_) < EPS;
}

double Line::distanceToPoint(double x0, double y0) const
{
    return fabs(a_ * x0 + b_ * y0 + c_) / sqrt(a_ * a_ + b_ * b_);
}

bool Line::intersect(const Line& other, double& intersectX, double& intersectY) const
{
    double D = a_ * other.b_ - other.a_ * b_;
    if (fabs(D) < EPS)
    {
        return false;
    }
    intersectX = (b_ * other.c_ - other.b_ * other.c_) / D;
    intersectY = (c_ * other.a_ - other.c_ * a_) / D;
    return true;
}

double Line::distanceToParallelLine(const Line& other) const
{
    if (!isParallel(other))
    {
        return -1;
    }

    double x0, y0;
    if (fabs(b_) > EPS)
    {
        x0 = 0;
        y0 = -c_ / b_;
    }
    else
    {
        y0 = 0;
        x0 = -c_ / a_;
    }
    return other.distanceToPoint(x0, y0);
}
