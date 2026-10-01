#include <iostream>
#include "BMsearchs.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    string text = " an iterator adaptor which behaves exactly like the underlying iterator";
    string pattern = "tor";

    int firstIndex = findFirst(text, pattern);
    cout << "Первое вхождение (индекс): " << firstIndex << endl;
    return 0;
}
