#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    map<int, int> f;
    for (int r = 1; r <= n; r++)
        f[arr[r]]++;

    int sz = (int)f.size();
    vector<int> dp(sz + 1, 0);

    dp[0] = 0;
    dp[1] = (f.begin())->first * (f.begin())->second;
    return 0;
}