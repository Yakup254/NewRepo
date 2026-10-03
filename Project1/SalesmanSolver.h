#pragma once
#include <vector>

using namespace std;

//вывода пути на экран
void printRoute(const vector<int>& path);

/// Функция создания случайной матрицы
vector<vector<int>> createRandomMatrix(int n);

//алгоритм Дейкстры для перестановок
bool NextPermutation(vector<int>& p);

// Запуск одного раунда эксперимента для матрицы размерности n
void executeRound(int n, int roundIndex);
