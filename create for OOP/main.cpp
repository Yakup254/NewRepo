#include <iostream>

#include "Line.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");

    cout << " 1 и 2. Создание и ввод 1-й прямой \n";
    Line line1;
    line1.readLine();
    cout << "Уравнение 1-й прямой: ";
    line1.printLine();

    cout << "\n-- Свойства 1-й прямой \n";

    cout << "4. Проходит через начало координат?: ";
    if (line1.passesOrigin()) cout << "ДА"; else cout << "НЕТ";
    cout << endl;

    cout << "5. Параллельна оси Ox?: ";
    if (line1.isParallelToOx()) cout << "ДА"; else cout << "НЕТ";
    cout << endl;

    double xIntercept, yIntercept;
    if (line1.getIntercepts(xIntercept, yIntercept)) {
        cout << "6. Отрезки на осях координат: x = " << xIntercept << ", y = " << yIntercept << endl;
    }
    else {
        cout << "6. Прямая параллельна одной из осей, поэтому не пересекает обе.\n";
    }

    double slope;
    if (line1.getSlope(slope)) {
        cout << "7. Угловой коэффициент (k): " << slope << endl;
    }
    else {
        cout << "7. Прямая вертикальная, угловой коэффициент не определен.\n";
    }

    double pointX, pointY;
    cout << "\nВведите координату x для точки: "; cin >> pointX;
    cout << "Введите координату y для точки: "; cin >> pointY;

    if (line1.containsPoint(pointX, pointY)) {
        cout << "ДА";
    }
    else {
        cout << "НЕТ";
    }
    cout << endl;
    cout << "11. Расстояние от точки до 1-й прямой: " << line1.distanceToPoint(pointX, pointY) << endl;

    cout << "\n Создание и ввод 2-й прямой \n";
    Line line2;
    line2.readLine();
    cout << "Уравнение 2-й прямой: ";
    line2.printLine();

    cout << "\n- - Отношения между двумя прямыми - -\n";

    cout << "8. Прямые совпадают?: ";
    if (line1 == line2) {
        cout << "ДА";
    }
    else {
        cout << "НЕТ";
    }
    cout << endl;

    cout << "9. Прямые параллельны?: ";
    if (line1.isParallel(line2)) {
        cout << "ДА";
    }
    else {
        cout << "НЕТ";
    }
    cout << endl;

    double intersectX, intersectY;
    if (line1.intersect(line2, intersectX, intersectY)) {
        cout << "12. Точка пересечения: (" << intersectX << ", " << intersectY << ")\n";
    }
    else {
        cout << "12. Прямые параллельны или совпадают, единственной точки пересечения нет.\n";
    }

    if (line1.isParallel(line2)) {
        cout << "13. Расстояние между параллельными прямыми: " << line1.distanceToParallelLine(line2) << endl;
    }
    else {
        cout << "13. Прямые не параллельны, расстояние вычислить нельзя.\n";
    }

    return 0;
}
