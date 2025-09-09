#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: slidingWindowMinimum
// URL: Not provided
// Difficulty: Unknown
// Tags:
// Strategy:

struct MapHash {
    std::size_t operator()(const std::map<int, int> &m) const {
        std::size_t seed = 0;
        std::hash<int> hasher;
        for (const auto &[key, value] : m) {
            // Combine the hash of key and value
            std::size_t pair_hash = hasher(key);
            pair_hash ^= hasher(value) + 0x9e3779b9 + (pair_hash << 6) + (pair_hash >> 2);
            // Combine into overall hash
            seed ^= pair_hash + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    int x, a, b, c;
    cin >> x >> a >> b >> c;

    vector<int> arr(n);
    arr[0] = x;

    // we are to calculate the minimum of each window of k elements, from left to right, and then take all their xors
    map<int, int> freq; // stores counts
    set<int> keys;      // stores current keys in sorted order
    int l = 0;
    int xr = 0;

    for (int r = 0; r < n; r++) {
        if (r > 0)
            arr[r] = (a * arr[r - 1] + b) % c;
        freq[arr[r]]++;
        keys.insert(arr[r]); // maintain the set of keys
        if (r - l + 1 == k) {
            xr ^= *keys.begin(); // smallest key in window
            // remove the left element from the window
            freq[arr[l]]--;
            if (!freq[arr[l]]) {
                keys.erase(arr[l]); // remove from set if count is zero
                freq.erase(arr[l]);
            }
            l++;
        }
    }
    cout << xr << endl;
    return 0;
}