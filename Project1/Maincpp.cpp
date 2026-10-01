#include <iostream>

#include "SalesmanSolver.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");

    int sizes[] = { 4, 6, 8, 10 };
    int totalSizes = sizeof(sizes) / sizeof(sizes[0]);
    int repeats = 4;

    cout << " ЭКСПЕРИМЕНТ (Диапазон стоимостей: 10 - 100)" << endl;

    for (int i = 0; i < totalSizes; i++) {
        cout << "\nРазмерность матрицы: " << sizes[i] << " x " << sizes[i] << endl;
        for (int n = 1; n <= repeats; n++) {
            executeRound(sizes[i], n);
        }
    }

    return 0;
}
