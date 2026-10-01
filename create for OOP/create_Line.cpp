#include "Line.h"
#include <iostream>
#include <cmath>

using namespace std;

const double EPS = 1e-9;

Line::Line(double a_val, double b_val, double c_val) {
    a_ = a_val;
    b_ = b_val;
    c_ = c_val;
}

void Line::input() {
    cin >> a_ >> b_ >> c_;
}

void Line::output() const {
    cout << a_ << "x";

    if (b_ >= 0.0) {
        cout << " + " << b_ << "y";
    }
    else {
        cout << " - " << abs(b_) << "y";
    }

    if (c_ >= 0.0) {
        cout << " + " << c_;
    }
    else {
        cout << " - " << abs(c_);
    }

    cout << " = 0" << endl;
}

double Line::getA() const { return a_; }
double Line::getB() const { return b_; }
double Line::getC() const { return c_; }

void Line::setA(double val) { a_ = val; }
void Line::setB(double val) { b_ = val; }
void Line::setC(double val) { c_ = val; }

bool Line::passesOrigin() const {
    return abs(c_) < EPS;
}

bool Line::isParallelToOx() const {
    return (abs(a_) < EPS && abs(b_) > EPS);
}

bool Line::getIntercepts(double& xIntercept, double& yIntercept) const {
    if (abs(a_) < EPS || abs(b_) < EPS) {
        return false;
    }
    xIntercept = -c_ / a_;
    yIntercept = -c_ / b_;
    return true;
}

bool Line::getSlope(double& slope) const {
    if (abs(b_) < EPS) {
        return false;
    }
    slope = -a_ / b_;
    return true;
}

bool Line::operator==(const Line& other) const {
    bool cond1 = abs(a_ * other.b_ - other.a_ * b_) < EPS;
    bool cond2 = abs(a_ * other.c_ - other.a_ * c_) < EPS;
    bool cond3 = abs(b_ * other.c_ - other.b_ * c_) < EPS;
    return cond1 && cond2 && cond3;
}

bool Line::isParallel(const Line& other) const {
    bool parallelCheck = abs(a_ * other.b_ - other.a_ * b_) < EPS;
    bool notIdentical = !(*this == other);
    return parallelCheck && notIdentical;
}

bool Line::containsPoint(double x0, double y0) const {
    return abs(a_ * x0 + b_ * y0 + c_) < EPS;
}

double Line::distanceToPoint(double x0, double y0) const {
    return abs(a_ * x0 + b_ * y0 + c_) / hypot(a_, b_);
}

bool Line::intersect(const Line& other, double& intersectX, double& intersectY) const {
    double D = a_ * other.b_ - other.a_ * b_;
    if (abs(D) < EPS) {
        return false;
    }
    intersectX = (b_ * other.c_ - other.b_ * c_) / D;
    intersectY = (c_ * other.a_ - other.c_ * a_) / D;
    return true;
}

double Line::distanceToParallelLine(const Line& other) const {
    if (!isParallel(other)) {
        return -1.0;
    }
    double x0 = 0.0, y0 = 0.0;
    if (abs(b_) > EPS) {
        y0 = -c_ / b_;
    }
    else {
        x0 = -c_ / a_;
    }
    return other.distanceToPoint(x0, y0);
}
