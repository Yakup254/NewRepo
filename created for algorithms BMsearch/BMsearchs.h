#pragma once

#include <string>
#include <vector>

using namespace std;

vector<int> createCharMap(const string& pattern);
int findFirst(const string& text, const string& pattern);

void printResult(const string& label, const vector<int>& indices);
vector<int> findAll(const string& text, const string& pattern);

