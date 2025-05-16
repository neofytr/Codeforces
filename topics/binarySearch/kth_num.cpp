#include <bits/stdc++.h>
using namespace std;

long long count(long long x, vector<pair<long long, long long>> &segments)
{
    // returns the number of elements in the final sorted array that are less than or equal to x
    long long ans = 0;
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
            ans += (right - left + 1);
        }

        ans += (x - left + 1);
    }

    return ans;
}

int main()
{
    long long n, k;
    cin >> n >> k;

    long long minimum = LONG_LONG_MAX;
    long long maximum = LONG_LONG_MIN;

    vector<pair<long long, long long>> segments(n);
    for (auto &segment : segments)
    {
        cin >> segment.first >> segment.second;

        long long temp = max(segment.first, segment.second);
        maximum = max(temp, maximum);

        temp = min(segment.first, segment.second);
        minimum = min(temp, minimum);
    }

    // we are to find the element at the kth index in the final array
    // that is, we are to find the element x in the final array whose count(x) = k + 1
    // such an element is guaranteed to exist (given in the problem statement)

    // that is, we have to find the minimum element x such that count(x) >= k + 1
    // let f(x) = 0 if count(x) <= k
    //          = 1 if count(x) >= k + 1
    // f is monotonically increasing

    long long left = minimum - 1;
    long long right = maximum + 1;

    // we maintain the invariant that
    // f(left) = 0
    // f(right) = 1

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