#include <bits/stdc++.h>
using namespace std;

#define int long long

// problem: divideandequalize
// url: https://codeforces.com/problemset/problem/1881/d
// difficulty: medium
// tags:
// strategy:

bool solve(const vector<int> &arr, const vector<int> &leastprime) {
    const int n = arr.size();
    unordered_map<int, int> mp;

    for (int x : arr) {
        while (x != 1) {
            int p = leastprime[x];
            mp[p]++;
            x /= p;
        }
    }

    for (auto &[p, cnt] : mp)
        if (cnt % n != 0)
            return false;

    return true;
}

#define max 1000000

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    vector<int> leastprime(max + 1, -1);
    for (int r = 2; r <= max; r++)
        for (int j = r; j <= max; j += r)
            if (leastprime[j] == -1)
                leastprime[j] = r;

    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;
        cout << (solve(arr, leastprime) ? "yes" : "no");
        cout << "\n";
    }

    return 0;
}