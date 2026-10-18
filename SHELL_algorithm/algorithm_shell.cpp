#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

// Проверка массива
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

void shellSortOriginal(vector<int>& arr) {
    int n = arr.size();
    vector<int> gaps;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        gaps.push_back(gap);
    }
    int t = gaps.size() - 1;

    for (int i = 0; i <= t; ++i) {
        int s = gaps[i];
        for (int b = 0; b < s; ++b) {
            for (int j = b + s; j < n; j += s) {
                int x = arr[j];
                int k = j - s;
                while (k >= 0 && arr[k] > x) {
                    arr[k + s] = arr[k];
                    k = k - s;
                }
                arr[k + s] = x;
            }
        }
    }
}

// Генерация случайных чисел
vector<int> generateAndSaveArray(int size, int minVal, int maxVal, const char* filename) {
    vector<int> arr(size);
    mt19937 gen(1337);
    uniform_int_distribution<int> dis(minVal, maxVal);
    ofstream fout(filename);
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
        fout << arr[i];
        if (i != size - 1) {
            fout << " ";
        }
    }
    fout.close();
    return arr;
}

double measureAverageTime(const vector<int>& originalArr, void (*sortFunc)(vector<int>&)) {
    double totalDuration = 0;
    for (int run = 0; run < 3; ++run) {
        vector<int> tempArr = originalArr;
        auto start = chrono::high_resolution_clock::now();
        sortFunc(tempArr);
        auto end = chrono::high_resolution_clock::now();
        if (!isSorted(tempArr)) cout << "Ошибка сортировки!" << endl;
        chrono::duration<double, milli> duration = end - start;
        totalDuration += duration.count();
    }
    return totalDuration / 3.0;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int sizes[3] = { 10000, 100000, 1000000 };
    int minVals[3] = { -10, -1000, -100000 };
    int maxVals[3] = { 10, 1000, 100000 };
    const char* filenames[3][3] = {
        {"array_10000_10.txt", "array_10000_1000.txt", "array_10000_100000.txt"},
        {"array_100000_10.txt", "array_100000_1000.txt", "array_100000_100000.txt"},
        {"array_1000000_10.txt", "array_1000000_1000.txt", "array_1000000_100000.txt"}
    };

    cout << "Размер\tДиапазон\tшелла (мс)" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            vector<int> currentArray = generateAndSaveArray(sizes[i], minVals[j], maxVals[j], filenames[i][j]);
            double tOriginal = measureAverageTime(currentArray, shellSortOriginal);
            cout << sizes[i] << "\t[" << minVals[j] << ";" << maxVals[j] << "]\t" << tOriginal << endl;
        }
    }
    return 0;
}
