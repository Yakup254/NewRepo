#include <iostream>
#include <string>
#include <vector>
#include "BMsearchs.h"

using namespace std;

vector<int> createCharMap(const string& pattern) {
    vector<int> shiftTable(256, -1);
    int patternSize = static_cast<int>(pattern.size());

    for (int i = 0; i < patternSize; i++) {
        unsigned char character = pattern[i];
        shiftTable[character] = i;
    }
    return shiftTable;
}

int findFirst(const string& text, const string& pattern) {
    int textSize = static_cast<int>(text.size());
    int patternSize = static_cast<int>(pattern.size());

    if (patternSize == 0 || textSize < patternSize) return -1;

    vector<int> shiftTable = createCharMap(pattern);
    int shift = 0;

    while (shift <= (textSize - patternSize)) {
        int j = patternSize - 1;
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }
        if (j < 0) return shift;

        unsigned char badChar = text[shift + j];
        int badCharShift = j - shiftTable[badChar];
        if (badCharShift < 1) {
            shift += 1;
        }
        else {
            shift += badCharShift;
        }
    }
    return -1;
}
void printResult(const string& label, const vector<int>& indices) {
    cout << label << ": [";
    for (size_t i = 0; i < indices.size(); i++) {
        cout << indices[i];
        if (i + 1 < indices.size()) cout << ", ";
    }
    cout << "]" << endl;
}

vector<int> findAll(const string& text, const string& pattern) {
    vector<int> results;
    int textSize = static_cast<int>(text.size());
    int patternSize = static_cast<int>(pattern.size());

    if (text.empty() || pattern.empty() || textSize < patternSize) return results;

    vector<int> shiftTable = createCharMap(pattern);
    int shift = 0;

    while (shift <= (textSize - patternSize)) {
        int j = patternSize - 1;
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }
        if (j < 0) {
            results.push_back(shift);
            shift += 1;
        }
        else {
            unsigned char badChar = text[shift + j];
            int badCharShift = j - shiftTable[badChar];

            if (badCharShift < 1) {
                shift += 1;
            }
            else {
                shift += badCharShift;
            }
        }
    }
    return results;
}
