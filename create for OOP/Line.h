#pragma once
#include <vector>
using namespace std;

class Line {
public:
    Line();
    Line(double a_val, double b_val, double c_val);
    void setCoefficients(double a_val, double b_val, double c_val);
    void printLine() const;
    void readLine();

    double getA() const;
    double getB() const;
    double getC() const;

    void setA(double val);
    void setB(double val);
    void setC(double val);

    bool passesOrigin() const;
    bool isParallelToOx() const;
    bool getIntercepts(double& xIntercept, double& yIntercept) const;
    bool getSlope(double& slope) const;


private:
    double a_ = 1;
    double b_ = 0;
    double c_ = 0;
};
