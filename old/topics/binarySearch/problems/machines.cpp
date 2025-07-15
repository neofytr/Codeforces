// https://cses.fi/problemset/task/1620

#include <bits/stdc++.h>
using namespace std;

bool canMake(long long x, vector<long long> &time, long long t)
{
    long long count = 0;
    for (size_t index = 0; index < time.size(); index++)
    {
        count += x / time[index];
        if (count >= t)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    long long n, t;
    cin >> n >> t;

    vector<long long> time(n);
    long long max_time = -1;
    for (long long &val : time)
    {
        cin >> val;
        max_time = max(val, max_time);
    }

    sort(time.begin(), time.end());

    // we want to know the shortest time needed to make t products

    // if we can make t products in x time, we can make them in x + 1 time;  x >= 0
    // if we can't make t products in x time, we can't make them in x - 1 time; x >= 1

    long long left = 0;             // we can't make t products in 0 time
    long long right = max_time * t; // we can make t products if we make the max time machine run consecutively t times

    while (right != left + 1)
    {
        long long mid = left + (right - left) / 2;
        if (canMake(mid, time, t))
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