#include <iostream>
#include <cmath>
#include "Line.h"
using namespace std;

const double EPS = 1e-9;

Line::Line() { setCoefficients(1  ,  0,   0); }
Line::Line(double a_val, double b_val, double c_val) { setCoefficients(a_val, b_val, c_val); }

void Line::setCoefficients(double a_val, double b_val, double c_val) {
    if (fabs(a_val) < EPS && fabs(b_val) < EPS) {
        a_ = 1; b_ = 0; c_ = 0;
    }
    else {
        a_ = a_val; b_ = b_val; c_ = c_val;
    }
}
void Line::printLine() const { cout << a_ << "x + " << b_ << "y + " << c_ << " = 0" << endl; }
void Line::readLine() {
    double a_in, b_in, c_in;
    cin >> a_in >> b_in >> c_in;
    setCoefficients(a_in, b_in, c_in);
}
double Line::getA() const { return a_; }
double Line::getB() const { return b_; }
double Line::getC() const { return c_; }
