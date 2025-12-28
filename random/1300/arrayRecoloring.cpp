#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    vector<int> leftDP(k + 1), rightDP(k + 1);
    leftDP[1] = arr[1], leftDP[0] = 0;
    rightDP[1] = arr[n], rightDP[0] = 0;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) solve();
}
