#include "BMsearch.h"

vector<int> makeTAB(const string& P)
{
	int m = P.size();
	vector<int> T(256, m);

	for (int i = 0; i < m - 1; i++)
	{
		char character = P[i];
		T[character] = m - 1 - i;
	}
	return T;
}

vector<int> findAllInRange(const string& S, const string& P, size_t start, size_t end)
{
	vector<int> results;
	int n = S.size();
	int m = P.size();

	if (start > end || end >= S.size() || m == 0)
	{
		return results;
	}

	vector<int> T = makeTAB(P);

	int i = start + m - 1;
	int j = m - 1;

	while (i <= end)
	{
		int k = i;
		j = m - 1;

		while (j >= 0)
		{
			if (S[k] == P[j])
			{
				j--;
				k--;
			}
			else
			{
				break;
			}
		}

		if (j >= 0)
		{
			char textChar = S[i];
			i = i + T[textChar];
			j = m - 1;
		}
		else
		{
			results.push_back(i + 1 - m);

			char textChar = S[i];
			int shift = T[textChar];

			if (shift > 1) {
				i = i + shift;
			}
			else {
				i = i + 1;
			}
			j = m - 1;
		}
	}
	return results;
}

vector<int> findAll(const string& S, const string& P)
{
	if (S.empty() || P.empty())
	{
		return vector<int>();
	}
	return findAllInRange(S, P, 0, S.size() - 1);
}

int findFirst(const string& S, const string& P)
{
	vector<int> results = findAll(S, P);

	if (results.empty()) {
		return -1;
	}
	else {
		return results[0];
	}
}
