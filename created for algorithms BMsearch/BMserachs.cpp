#include "BMsearchs.h"

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

int findFirst(const string& S, const string& P)
{
    int n = S.size();
    int m = P.size();

    if (S.empty() || P.empty() || n < m)
    {
        return -1;
    }

    vector<int> T = makeTAB(P);

    int i = m - 1;
    int j = m - 1;

    while (i < n)
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
        }
        else
        {
            return i + 1 - m;
        }
    }
    return -1;
}

vector<int> findAll(const string& S, const string& P)
{
    vector<int> results;
    int n = S.size();
    int m = P.size();

    if (S.empty() || P.empty() || n < m)
    {
        return results;
    }

    vector<int> T = makeTAB(P);

    int i = m - 1;
    int j = m - 1;

    while (i < n)
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
        }
        else
        {
            results.push_back(i + 1 - m);

            char textChar = S[i];
            i = i + T[textChar];
        }
    }
    return results;
}

vector<int> findAllInRange(const string& S, const string& P, size_t start, size_t end)
{
    vector<int> results;
    int m = P.size();

    if (start > end || end >= S.size() || m == 0)
    {
        return results;
    }

    vector<int> T = makeTAB(P);

    int i = start + m - 1;
    int limit = end;
    int j = m - 1;

    while (i <= limit)
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
        }
        else
        {
            results.push_back(i + 1 - m);

            char textChar = S[i];
            i = i + T[textChar];
        }
    }
    return results;
}
