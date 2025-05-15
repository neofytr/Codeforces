#include <bits/stdc++.h>
using namespace std;

long long count(long long x, vector<pair<long long, long long>> &segments)
{
    // this returns the count of the elements in the final multiset that are less than
    // or equal to x
    long long cnt = 0;
    for (auto segment : segments)
    {
        long long left = segment.first;
        long long right = segment.second;

        if (x < left)
        {
            continue;
        }

        if (x > right)
        {
            cnt += (right - left + 1);
            continue;
        }

        cnt += (x - left + 1);
    }

    return cnt;
}

int main()
{
    long long n, k;
    cin >> n >> k;

    vector<pair<long long, long long>> segments(n);
    long long maximum = -1;
    for (auto &segment : segments)
    {
        cin >> segment.first >> segment.second;
        long long temp = max(segment.first, segment.second);
        maximum = max(maximum, temp);
    }

    // we are to find the (k + 1)th element in the final multiset (its given that it exists)
    // so we find the maximum element with count(x) <= k + 1

    long long left = -1;
    long long right = maximum + 1;

    // we maintain f(right) > k and f(left) <= k + 1
    while (right != left + 1)
    {
        long long mid = left + (right - left) / 2;
        if (count(mid, segments) <= k + 1)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }

    cout << left << endl;

    return EXIT_SUCCESS;
}