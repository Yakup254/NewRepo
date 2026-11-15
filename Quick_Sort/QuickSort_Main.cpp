#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include <iomanip>

using namespace std;

bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

void hoareSort3(vector<int>& A, int l, int r) {
    if (l >= r) return;

    int i = l;
    int j = r;
    int x = A[(l + r) / 2];

    while (i <= j) {
        while (A[i] < x) {
            i++;
        }
        while (A[j] > x) {
            j--;
        }
        if (i <= j) {
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;
        }
    }

    hoareSort3(A, l, j);
    hoareSort3(A, i, r);
}

void quickSort(vector<int>& arr) {
    if (!arr.empty()) {
        hoareSort3(arr, 0, static_cast<int>(arr.size()) - 1);
    }
}

void generateAndSaveArray(int size, int minVal, int maxVal, const char* filename) {
    vector<int> arr(size);
    mt19937 gen(1317);
    uniform_int_distribution<int> dis(minVal, maxVal);

    ofstream fout(filename);
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
        fout << arr[i];
        if (i < size - 1) fout << " ";
    }
    fout.close();
}

vector<int> loadArrayFromFile(const char* filename, int size) {
    vector<int> arr(size);
    ifstream fin(filename);
    if (!fin.is_open()) {
        return vector<int>();
    }
    for (int i = 0; i < size; ++i) {
        fin >> arr[i];
    }
    fin.close();
    return arr;
}

double measureAverageTime(const vector<int>& originalArr) {
    double totalDuration = 0;
    for (int run = 0; run < 3; ++run) {
        vector<int> tempArr = originalArr;
        auto start = chrono::high_resolution_clock::now();
        quickSort(tempArr);
        auto end = chrono::high_resolution_clock::now();

        if (!isSorted(tempArr)) {
            cout << "error! array not sorted" << endl;
        }
        chrono::duration<double, milli> duration = end - start;
        totalDuration += duration.count();
    }
    return totalDuration / 3.0;
}

int main() {
    setlocale(LC_ALL, "Rus");

    int sizes[3] = { 10000, 100000, 1000000 };
    int minVals[3] = { -10, -1000, -100000 };
    int maxVals[3] = { 10, 1000, 100000 };

    const char* filenames[3][3] = {
        {"array_10000_10.txt", "array_10000_1000.txt", "array_10000_100000.txt"},
        {"array_100000_10.txt", "array_100000_1000.txt", "array_100000_100000.txt"},
        {"array_1000000_10.txt", "array_1000000_1000.txt", "array_1000000_100000.txt"}
    };

    int mode;
    cout << "input 0 or 1:  0--generate  1--use from file ";
    cin >> mode;

    if (mode == 0) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                generateAndSaveArray(sizes[i], minVals[j], maxVals[j], filenames[i][j]);
            }
        }
    }
    else 
        cout << "\nРазмер\tДиапазон\tQuickSort (мс)" << endl;
        cout << "- - -- --- - - -- -- - - - -- -- - - - - - " << endl;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                vector<int> currentArray = loadArrayFromFile(filenames[i][j], sizes[i]);

                double tQuick = measureAverageTime(currentArray);
                cout << sizes[i] << "\t[" << minVals[j] << ";" << maxVals[j] << "]\t" << tQuick << endl;
            }
        }
    

    return 0;
}
