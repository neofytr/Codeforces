#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: distinctValuesSubarrayTwo
// URL: https://cses.fi/problemset/task/2428
// Difficulty: hard
// Tags:
// Strategy:

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // A fast, high-quality mixer
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(int x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    int num = 0;
    int l = 0;
    unordered_map<int, int, custom_hash> mp;
    set<int> s;
    for (int r = 0; r < n; r++) {
        if (!mp[arr[r]])
            s.insert(arr[r]);
        mp[arr[r]]++;
        while (l <= r && s.size() > k) {
            const int elt = arr[l];
            if (!(--mp[elt]))
                s.erase(elt);
            l++;
        }
        if (r >= l)
            num += (r - l + 1); // num is the largest subarray ending at r with this property,
                                // and all the subarrays ending at r with the property are [i, r] for l <= i <= r
    }
    cout << num << endl;
    return 0;
}