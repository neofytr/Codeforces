// https://codeforces.com/contest/702/problem/C

#include <bits/stdc++.h>
using namespace std;

bool canSolve(long long r, vector<long long> &city, vector<long long> &tower)
{
    for (int index = 0; index < city.size(); index++)
    {
        // for each city check if it can be reached in r by its nearest towers
        long long curr_city = city[index];
        // find the max index x in tower such that tower[x] <= curr_city
        int left = -1;
        int right = tower.size();

        while (right != left + 1)
        {
            int mid = left + (right - left) / 2;
            if (tower[mid] <= curr_city)
            {
                left = mid;
            }
            else
            {
                right = mid;
            }
        }

        if (left == -1)
        {
            // all > curr_city
            if (tower[right] - curr_city <= r)
            {
                continue;
            }
            else
            {
                return false;
            }
        }

        if (curr_city - tower[left] <= r)
        {
            continue;
        }
        else
        {
            if (right == tower.size())
            {
                return false;
            }
            else
            {
                if (tower[right] - curr_city <= r)
                {
                    continue;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    return true;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<long long> city(n);
    vector<long long> tower(m);

    for (long long &val : city)
    {
        cin >> val;
    }

    for (long long &val : tower)
    {
        cin >> val;
    }

    long long left = -1;
    long long right = 1e10;

    while (right != left + 1)
    {
        long long mid = left + (right - left) / 2;
        if (canSolve(mid, city, tower))
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }

    cout << right << endl;
    return EXIT_SUCCESS;
}
