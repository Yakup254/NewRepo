#pragma once

#include <vector>

using namespace std;

vector<vector<int>> createRandomMatrix(int n, int minVal, int maxVal);

void printRoute(const vector<int>& path);

void evaluatePaths(const vector<vector<int>>& matrix, int n, int start, int current,
    int visitedCount, int currentCost, vector<bool>& visited,
    vector<int>& currentPath, int& minCost, vector<int>& bestPath,
    int& maxCost, vector<int>& worstPath);

void executeRound(int n, int roundIndex);
