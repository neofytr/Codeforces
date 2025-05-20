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

    unordered_map<long long, int> freq;
    long long left = 0, count = 0;

    for (long long right = 0; right < n; ++right)
    {
        freq[arr[right]]++;

        while ((long long)freq.size() > k)
        {
            freq[arr[left]]--;
            if (freq[arr[left]] == 0)
            {
                freq.erase(arr[left]);
            }
            left++;
        }

        count += right - left + 1;
    }

    cout << count << endl;
    return 0;
}
