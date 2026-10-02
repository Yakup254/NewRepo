#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>

#include "SalesmanSolver.h"

using namespace std;

const int INF = 1e9;

vector<vector<int>> createRandomMatrix(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(10, 100);

    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) matrix[i][j] = 0;
            else matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

bool NextPermutation(vector<int>& p) {
    int n = p.size();

    // Максимальное i
    int i = n - 2;
    while (i >= 0 && p[i] >= p[i + 1]) {
        i--;
    }
    if (i < 0) return false;

    // Находим максимальное j
    int j = n - 1;
    while (p[i] >= p[j]) {
        j--;
    }

    // swap
    int temp = p[i];
    p[i] = p[j];
    p[j] = temp;

    int left = i + 1;
    int right = n - 1;
    while (left < right) {
        int t = p[left];
        p[left] = p[right];
        p[right] = t;
        left++;
        right--;
    }

    return true; 
}

void executeRound(int n, int roundIndex) {
    auto matrix = createRandomMatrix(n);

    vector<int> cities;
    for (int i = 1; i < n; i++) {
        cities.push_back(i); 
    }

    int minCost = INF;
    int maxCost = -1;

    auto startExact = chrono::high_resolution_clock::now();

    while (true) {
        int currentCost = 0;
        int prevCity = 0;

        for (size_t i = 0; i < cities.size(); i++) {
            int city = cities[i];
            currentCost += matrix[prevCity][city];
            prevCity = city;
        }
        currentCost += matrix[prevCity][0];

        if (currentCost < minCost) minCost = currentCost;
        if (currentCost > maxCost) maxCost = currentCost;

        bool hasNext = NextPermutation(cities);

        if (hasNext == false) {
            break;
        }
    }

    auto endExact = chrono::high_resolution_clock::now();
    double timeExact = chrono::duration<double, milli>(endExact - startExact).count();

    vector<bool> visited(n, false);
    int greedyCost = 0;
    int currentCity = 0;
    visited[0] = true;

    auto startGreedy = chrono::high_resolution_clock::now();

    for (int step = 0; step < n - 1; step++) {
        int nextCity = -1;
        int shortest = INF;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && matrix[currentCity][i] < shortest) {
                shortest = matrix[currentCity][i];
                nextCity = i;
            }
        }
        greedyCost += shortest;
        currentCity = nextCity;
        visited[currentCity] = true;
    }
    greedyCost += matrix[currentCity][0];

    auto endGreedy = chrono::high_resolution_clock::now();
    double timeGreedy = chrono::duration<double, milli>(endGreedy - startGreedy).count();

    double quality = 100.0;
    if (maxCost != minCost) {
        quality = (double)(maxCost - greedyCost) / (maxCost - minCost) * 100.0;
    }

    cout << "  > Итерация " << roundIndex
        << " > Точный метод \n Лучший: " << minCost
        << ", Худший: " << maxCost
        << ", Время: " << fixed << setprecision(4) << timeExact << " мс\n";

    cout << "    Жадный метод Стоимость: " << greedyCost
        << ", Время: " << fixed << setprecision(4) << timeGreedy << " мс\n";

    cout << "    Качество Э: " << fixed << setprecision(1) << quality << "%" << endl;
    cout << "-- --- - -- - -- - -- - -- -- ---  --" << endl;
}
