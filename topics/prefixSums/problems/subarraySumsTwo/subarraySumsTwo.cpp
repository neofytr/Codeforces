#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: subarraySumsTwo
// URL: https://cses.fi/problemset/task/1661
// Difficulty: medium
// Tags:
// Strategy:

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // we are to count the number of subarrays with target sum x
    unordered_map<int, int, custom_hash> freq; // freq[r] denotes the number of subarrays starting from 0 until the current iteration have their sum = r
    freq[0] = 1;
    int count = 0;
    int sum = 0;
    // for each index we count the number of subarrays (starting at zero) whose sum is target
    // each such subarray forms s good segment with the current index
    for (int index = 0; index < n; index++) {
        // pref[a + 1] - x = pref[b]
        sum += arr[index]; // since we only need sums until the current iteration to do our job, no need to build the whole prefix array before
        int target = sum - x;
        count += freq[target];
        freq[sum]++;
    }
    cout << count << endl;
    return 0;
}