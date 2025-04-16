#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    string str;
    cin >> str;

    long long count = 0; // Stores the total number of valid subarrays
    long long sum = 0;   // Running prefix sum of the digits
    long long val;

    // Key insight:
    // We want to count subarrays where sum of elements == number of elements
    // That is, for subarray [l, r], we want:
    //     prefix[r] - prefix[l - 1] == r - l + 1
    // Rearranged:
    //     prefix[r] - r == prefix[l - 1] - (l - 1)
    // So we can count how many times (prefix[i] - i) has occurred using a hash map

    unordered_map<long long, long long> map;
    map[0] = 1; // Base case: empty prefix with (sum - index) = 0 occurs once

    for (int index = 1; index <= n; index++)
    {
        // Convert character to digit
        val = str[index - 1] - '0';

        // Update prefix sum
        sum += val;

        // Calculate the key (prefix sum - index)
        long long key = sum - index;

        // If this key has been seen before, those subarrays ending here are valid
        // They satisfy sum of subarray == length of subarray
        if (map.count(key))
        {
            count += map[key];
        }

        // Record the current key for future subarrays
        map[key]++;
    }

    cout << count << endl;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
