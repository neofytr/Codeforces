// https://codeforces.com/contest/702/problem/C

#include <bits/stdc++.h>
using namespace std;

bool canCover(long long r, vector<long long> &city, vector<long long> &tower)
{
    for (long long curr_city : city)
    {
        // binary search to find tower closest to curr_city
        long long left = -1, right = tower.size();
        while (right != left + 1)
        {
            long long mid = left + (right - left) / 2;
            if (tower[mid] <= curr_city)
                left = mid;
            else
                right = mid;
        }

        // candidates: tower[left] (<= curr_city) and tower[right] (>= curr_city)
        long long min_dist = LLONG_MAX;

        if (left >= 0)
            min_dist = min(min_dist, curr_city - tower[left]);

        if (right < tower.size())
            min_dist = min(min_dist, tower[right] - curr_city);

        if (min_dist > r)
            return false;
    }

    return true;
}

int main()
{
    long long n, m;
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

    // city and tower array are in non-decreasing order
    // if all cities can be covered with r range, they can also be covered with r + 1 range; for any r >= 0

    if (city[0] == city[n - 1] && binary_search(tower.begin(), tower.end(), city[0]))
    {
        // this is the only case in which 0 range is sufficient
        cout << 0 << endl;
        return EXIT_SUCCESS;
    }

    long long left = 0; // cannot be covered with zero range (until and unless all cities and all towers are in the same place, which is not the case(we handled it already))
    long long right = 5 * 1e18;

    while (right != left + 1)
    {
        long long mid = left + (right - left) / 2;
        if (canCover(mid, city, tower))
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