#pragma once
#include <vector>

using namespace std;

// Функция создания случайной матрицы
vector<vector<int>> createRandomMatrix(int n);

//алгоритм Дейкстры для перестановок
bool NextPermutation(vector<int>& p);

void executeRound(int n, int roundIndex);
