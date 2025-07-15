// https://cses.fi/problemset/task/1085

#include <bits/stdc++.h>
using namespace std;

bool canMake(long long target, int k, vector<long long> &arr)
{
    int count = 1;
    long long curr = 0;
    for (int index = 0; index < arr.size(); index++)
    {
        if (arr[index] > target)
        {
            return false;
        }

        if (arr[index] + curr <= target)
        {
            curr += arr[index];
        }
        else
        {
            curr = arr[index];
            count++;
        }
    }

    return count <= k;
}

int main()
{
    int n, k;
    cin >> n >> k;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    long long left = 0;
    long long right = accumulate(arr.begin(), arr.end(), 0LL);

    while (right != left + 1)
    {
        long long mid = left + (right - left) / 2;
        if (canMake(mid, k, arr))
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