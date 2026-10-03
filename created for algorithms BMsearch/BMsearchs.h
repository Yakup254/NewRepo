#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

int findFirst(const string& S, const string& P);
vector<int> findAll(const string& S, const string& P);
vector<int> findAllInRange(const string& S, const string& P, size_t start, size_t end);
