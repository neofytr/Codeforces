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
    long long minimum = LONG_LONG_MAX;
    for (auto &segment : segments)
    {
        cin >> segment.first >> segment.second;
        long long temp = max(segment.first, segment.second);
        maximum = max(maximum, temp);

        temp = min(segment.first, segment.second);
        minimum = min(minimum, temp);
    }

    long long left = minimum - 1;
    long long right = maximum + 1;

    // we want the smallest x such that count(x) >= k + 1
    while (right != left + 1)
    {
        long long mid = left + (right - left) / 2;
        if (count(mid, segments) >= k + 1)
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