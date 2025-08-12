#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: coloringGame
// URL: https://codeforces.com/problemset/problem/2112/C
// Difficulty: medium
// Tags:
// Strategy:

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int index = 1; index <= n; index++) {
        cin >> arr[index];
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int target = arr[n] - arr[i] - arr[j];
            auto itr = upper_bound(arr.begin() + j + 1, arr.end(), target);
            if (itr == arr.end())
                continue;
            int firstIndex = itr - arr.begin();
            itr = lower_bound(arr.begin() + firstIndex, arr.end(), arr[i] + arr[j]);
            int secondIndex = itr - arr.begin();
            cnt += (secondIndex - firstIndex);
        }
    }

    cout << cnt << endl;
    return;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}