#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: playlist
// URL: https://cses.fi/problemset/task/1141
// Difficulty: medium
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

    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    // mp[k] is the last index of k in the array during the current iteration
    unordered_map<int, int, custom_hash> mp;
    int maxi = LLONG_MIN;
    int l = 1; // the segment is [l, r]; we maintain the invariant that this segment is the largest unique segment ending at r
    for (int r = 1; r <= n; r++) {
        if (mp[arr[r]] >= l) // we add the element arr[r] into our segment; if there is an element like it
                             // in the segment previously, the maximum length unique segment ending at r will be [mp[arr[r]] + 1, r]
            l = mp[arr[r]] + 1;
        maxi = max(maxi, r - l + 1);
        mp[arr[r]] = r;
    }
    cout << maxi << endl;
    return 0;
}