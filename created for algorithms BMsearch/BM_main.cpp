#include <iostream>
#include <vector>
#include "BMsearchs.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    string text = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
    string pattern = "tor";

    int firstIndex = findFirst(text, pattern);
    cout << "Первое вхождение (индекс): " << firstIndex << "\n" << endl;

    vector<int> allIndices = findAll(text, pattern);
    printResult("Поиск во всём тексте (findAll)", allIndices);
    return 0;
}
