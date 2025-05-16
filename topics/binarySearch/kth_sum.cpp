#include <bits/stdc++.h>
using namespace std;

// this function returns the number of pairs (a, b) such that a + b <= x
long long count(long long x, vector<long long> &arrOne, vector<long long> &arrTwo)
{
    long long ans = 0;

    for (long long i = 0; i < arrOne.size(); ++i)
    {
        if (arrOne[i] >= x)
            break;

        long long max_target = x - arrOne[i];

        // binary search to find how many elements in arrTwo <= max_target
        long long left = -1;
        long long right = arrTwo.size();

        while (right != left + 1)
        {
            long long mid = left + (right - left) / 2;
            if (arrTwo[mid] <= max_target)
            {
                left = mid;
            }
            else
            {
                right = mid;
            }
        }

        if (left != -1)
        {
            ans += (left + 1);
        }
    }

    return ans;
}

int main()
{
    long long n, k;
    cin >> n >> k;

    vector<long long> arrOne(n);
    vector<long long> arrTwo(n);

    for (long long &val : arrOne)
        cin >> val;

    for (long long &val : arrTwo)
        cin >> val;

    sort(arrOne.begin(), arrOne.end());
    sort(arrTwo.begin(), arrTwo.end());

    long long minOne = arrOne[0];
    long long maxOne = arrOne[n - 1];
    long long minTwo = arrTwo[0];
    long long maxTwo = arrTwo[n - 1];

    // binary search to find first candidate where count(x) >= k
    long long left = minOne + minTwo - 1;
    long long right = maxOne + maxTwo + 1;

    while (right != left + 1)
    {
        long long mid = left + (right - left) / 2;
        if (count(mid, arrOne, arrTwo) >= k)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }

    long long low = right; // minimum x such that count(x) >= k

    // now find the maximum x such that count(x) >= k
    left = minOne + minTwo - 1;
    right = maxOne + maxTwo + 1;

    while (right != left + 1)
    {
        long long mid = left + (right - left) / 2;
        if (count(mid, arrOne, arrTwo) >= k)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }

    long long high = left;

    // now check every value from low to high to find the first x such that count(x) >= k and x exists as a+b
    for (long long x = low; x <= high; ++x)
    {
        long long cnt = 0;
        for (long long i = 0; i < n; ++i)
        {
            long long target = x - arrOne[i];
            if (target < 0)
                continue;

            // check if target exists in arrTwo using binary search
            if (binary_search(arrTwo.begin(), arrTwo.end(), target))
            {
                cnt++;
                if (cnt >= 1)
                    break;
            }
        }

        // if at least one valid pair (a + b == x) is found
        if (cnt > 0 && count(x, arrOne, arrTwo) >= k)
        {
            cout << x << '\n';
            return 0;
        }
    }

    return 0;
}
