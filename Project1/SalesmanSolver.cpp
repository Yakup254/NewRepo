#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>

#include "SalesmanSolver.h"

using namespace std;

const int INF = 1e9;

vector<vector<int>> createRandomMatrix(int n, int minVal, int maxVal) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(minVal, maxVal);

    vector<vector<int>> matrix(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            }
            else {
                matrix[i][j] = dis(gen);
            }
        }
    }
    return matrix;
}

void printRoute(const vector<int>& path) {
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << "-";
    }
}