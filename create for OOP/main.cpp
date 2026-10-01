#include <iostream>
#include "Line.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");

    Line line1;
    cout << "Введите коэффициенты a, b, c через пробел: ";
    line1.input();

    cout << "Уравнение 1-й прямой: ";
    line1.output();

    cout << "\n 2. Свойства 1-й прямой \n";

    cout << "Проходит через начало координат?: ";
    if (line1.passesOrigin()) {
        cout << "ДА\n";
    }
    else {
        cout << "НЕТ\n";
    }

    cout << "Параллельна оси Ox?: ";
    if (line1.isParallelToOx()) {
        cout << "ДА\n";
    }
    else {
        cout << "НЕТ\n";
    }

    double xIntercept, yIntercept;
    if (line1.getIntercepts(xIntercept, yIntercept)) {
        cout << "Отрезки на осях координат: x = " << xIntercept << ", y = " << yIntercept << "\n";
    }
    else {
        cout << "Пмямая параллельна одной из осей.\n";
    }

    double slope;
    if (line1.getSlope(slope)) {
        cout << "Угловой коэффициент (k): " << slope << "\n";
    }
    else {
        cout << "Прямая вертикальная, k не определен.\n";
    }

    cout << "\n 3. Проверка точки \n";
    double pointX, pointY;
    cout << "Введите координату X для точки: "; cin >> pointX;
    cout << "Введите координату Y для точки: "; cin >> pointY;

    cout << "Точка принадлежит 1-й прямой?: ";
    if (line1.containsPoint(pointX, pointY)) {
        cout << "ДА\n";
    }
    else {
        cout << "НЕТ\n";
    }

    cout << "Расстояние от точки до 1-й прямой: " << line1.distanceToPoint(pointX, pointY) << "\n";

    cout << "\n 4. Создание и ввод 2-й прямой \n";
    Line line2;
    cout << "Введите коэффициенты a, b, c через пробел: ";
    line2.input();

    cout << "Уравнение 2-й прямой: ";
    line2.output();

    cout << "\n 5. Отношения между прямыми \n";

    cout << "Прямые совпадают?: ";
    if (line1 == line2) {
        cout << "ДА\n";
    }
    else {
        cout << "НЕТ\n";
    }

    cout << "Прямые параллельны?: ";
    if (line1.isParallel(line2)) {
        cout << "ДА\n";
    }
    else {
        cout << "НЕТ\n";
    }

    double intersectX, intersectY;
    if (line1.intersect(line2, intersectX, intersectY)) {
        cout << "Точка пересечения: (" << intersectX << "; " << intersectY << ")\n";
    }
    else {
        cout << "Прямые параллельны или совпадают.\n";
    }

    if (line1.isParallel(line2)) {
        cout << "Расстояние между параллельными прямыми: " << line1.distanceToParallelLine(line2) << "\n";
    }

    return 0;
}
