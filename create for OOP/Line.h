#pragma once

class Line {
public:
    // Конструкторы
    Line() = default;
    Line(const double a_val, const double b_val, const double c_val);

    // Ввод и вывод
    void input();
    void output() const;

    // Геттеры и сеттеры
    double getA() const;
    double getB() const;
    double getC() const;

    void setA(const double val);
    void setB(const double val);
    void setC(const double val);

    // Геометрические методы
    bool passesOrigin() const;
    bool isParallelToOx() const;
    bool getIntercepts(double& xIntercept, double& yIntercept) const;
    bool getSlope(double& slope) const;

    bool operator==(const Line& other) const;
    bool isParallel(const Line& other) const;
    bool containsPoint(const double x0, const double y0) const;
    double distanceToPoint(const double x0, const double y0) const;
    bool intersect(const Line& other, double& intersectX, double& intersectY) const;
    double distanceToParallelLine(const Line& other) const;

private:
    double a_ = 1.0;
    double b_ = 0.0;
    double c_ = 0.0;
};
