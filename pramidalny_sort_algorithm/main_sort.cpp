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

void sift2(vector<int>& a, int n, int i) {
    int j = 2 * i + 1;
    int x = a[i];   
    bool f = true;  

    while (j < n && f) 
    {
        if (j + 1 < n) 
        {
            if (a[j + 1] > a[j]) 
            {
                j = j + 1;
            }
        }
        if (a[j] > x) {
            a[i] = a[j];    
            i = j;
            j = 2 * i + 1;     
        }
        else {
            f = false;         
        }
    }
    a[i] = x; 
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i) {
        sift2(arr, n, i);
    }

    for (int i = n - 1; i >= 1; --i) {
        int temp = arr[0];
        arr[0] = arr[i]; 
        arr[i] = temp;  
        sift2(arr, i, 0); 
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
        heapSort(tempArr);
        auto end = chrono::high_resolution_clock::now();

        if (!isSorted(tempArr)) {
            cout << "error! arrays no sorted" << endl;
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
        cout << "\nРазмер\tДиапазон\tHeap Sort (мс)" << endl;
        cout << "- - -- --- - - -- -- - - - -- -- - - - - - " << endl;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                vector<int> currentArray = loadArrayFromFile(filenames[i][j], sizes[i]);

                double tHeap = measureAverageTime(currentArray);
                cout << sizes[i] << "\t[" << minVals[j] << ";" << maxVals[j] << "]\t" << tHeap << endl;
            }
        
    }
    return 0;
}
