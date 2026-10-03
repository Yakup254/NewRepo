#include <iostream>
#include <string>
#include <vector>
#include "BMsearchs.h"

using namespace std;

void printResult(const string& label, const vector<int>& indixes)
{
	cout << label << ": [";
	for (size_t i = 0; i < indixes.size(); i++)
	{
		cout << indixes[i];
		if (i + 1 < indixes.size())
		{
			cout << ", ";
		}
	}
	cout << "]" << endl;
}

int main()
{
	setlocale(LC_ALL, "Rus");

	string text = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
	string pattern = "tor";

	int firstIndex = findFirst(text, pattern);
	cout << "Первое вхождение (индекс): " << firstIndex << "\n" << endl;

	vector<int> allIndices = findAll(text, pattern);
	printResult("Поиск во всём тексте (findAll)", allIndices);

	vector<int> range1 = findAllInRange(text, pattern, 0, 91);
	printResult("Поиск в диапазоне findAll(0, 91)", range1);

	vector<int> range2 = findAllInRange(text, pattern, 17, 91);
	printResult("Поиск в диапазоне findAll(17, 91)", range2);

	vector<int> range3 = findAllInRange(text, pattern, 28, 36);
	printResult("Поиск в диапазоне findAll(28, 36)", range3);

	return 0;
}
