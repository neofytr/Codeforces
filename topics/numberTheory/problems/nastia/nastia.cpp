#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: nastia
// URL: https://codeforces.com/problemset/problem/1521/B
// Difficulty: medium
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> arr(n);
        int mini = LLONG_MAX;
        int idx = -1;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            if (arr[i] < mini) {
                mini = arr[i];
                idx = i;
            }
        }

        vector<tuple<int,int,int,int>> ops;
        for (int i = 0; i < n; i++) {
            if (i == idx) continue;
            // make arr[i] = mini + abs(i - idx)
            ops.push_back({idx+1, i+1, mini, mini + abs(i - idx)});
        }

        cout << ops.size() << "\n";
        for (auto &[x, y, a, b] : ops) {
            cout << x << " " << y << " " << a << " " << b << "\n";
        }
    }
    return 0;
}