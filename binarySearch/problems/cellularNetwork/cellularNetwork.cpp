#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

// Problem: cellularNetwork
// URL: https://codeforces.com/contest/702/problem/C
// Difficulty: hard
// Tags:
// Strategy:

#define int long long

bool works(int r, const vector<int> &cities, const vector<int> &towers) {
    for (int city : cities) {
        // find the closest tower using binary search
        auto it = lower_bound(towers.begin(), towers.end(), city);
        int dist = LLONG_MAX;

        if (it != towers.end())
            dist = min(dist, abs(city - *it));
        if (it != towers.begin())
            dist = min(dist, abs(city - *prev(it)));

        if (dist > r)
            return false;
    }
    return true;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> cities(n);
    for (int &val : cities)
        cin >> val; // in non-decreasing order

    vector<int> towers(m);
    for (int &val : towers)
        cin >> val; // in non-decreasing order

    // now we are sure that r = -1 won't work
    // also, we are fairly certain that r = 1e9 would work
    // also, if some distance r = x works, then distance r = x + 1 also works
    // so, there must be an r = y such that any r = x such that x < y won't work and any r = x where x >= y will work
    // since r = 0 doesn't work and r = 1e9 does

    int left = -1;
    int right = 2e9;

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (works(mid, cities, towers))
            right = mid;
        else
            left = mid;
    }

    cout << right << endl;

    return EXIT_SUCCESS;
}