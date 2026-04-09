#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, k;
    cin >> n >> k;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    long long count = 0;
    long long right = 0;
    long long left = 0;
    long long size = 0;

    unordered_map<long long, long long> freq;

    while (left < n)
    {
        // count good segments starting at left

        while (right < n && size + (!freq[arr[right]] ? 1 : 0) <= k)
        {
            if (!freq[arr[right]])
            {
                size++;
            }
            freq[arr[right++]]++;
        }

        count += (right - left);

        if (!(--freq[arr[left++]]))
        {
            size--;
        }
    }

    cout << count << endl;
    return 0;
}
