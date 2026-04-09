#include <bits/stdc++.h>
using namespace std;

struct CustomHash
{
    size_t operator()(long long x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        x += FIXED_RANDOM;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
};

int main()
{
    int n;
    cin >> n;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    int left = 0;
    int right = 0;
    int max_count = INT_MIN;

    unordered_map<long long, int, CustomHash> freq;

    while (left < n)
    {
        while (right < n && !freq[arr[right]])
        {
            freq[arr[right++]]++;
        }

        max_count = max(max_count, right - left);

        freq[arr[left++]]--;
    }

    cout << max_count << endl;
    return EXIT_SUCCESS;
}