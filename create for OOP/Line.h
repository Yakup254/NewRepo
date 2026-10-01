#pragma once

class Line {
public:
    // Конструкторы
    Line() = default;
    Line(double a_val, double b_val, double c_val);

    // Ввод и вывод
    void input();
    void output() const;

    // Геттеры и сеттеры
    double getA() const;
    double getB() const;
    double getC() const;

    void setA(double val);
    void setB(double val);
    void setC(double val);

    // Геометрические методы
    bool passesOrigin() const;
    bool isParallelToOx() const;
    bool getIntercepts(double& xIntercept, double& yIntercept) const;
    bool getSlope(double& slope) const;

    bool operator==(const Line& other) const;
    bool isParallel(const Line& other) const;
    bool containsPoint(double x0, double y0) const;
    double distanceToPoint(double x0, double y0) const;
    bool intersect(const Line& other, double& intersectX, double& intersectY) const;
    double distanceToParallelLine(const Line& other) const;

private:
    double a_ = 1.0;
    double b_ = 0.0;
    double c_ = 0.0;
};
