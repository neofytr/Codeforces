#include <bits/stdc++.h>
using namespace std;

#define int long long

// problem: encryptingmessages
// url: https://codeforces.com/contest/177/problem/d2
// difficulty: hard
// tags:
// strategy:

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, c;
    cin >> n >> m >> c;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<int> keys(m);
    for (int &val : keys)
        cin >> val;

    vector<int> prefix(m + 1, 0);
    for (int r = 1; r <= m; r++)
        prefix[r] = (prefix[r - 1] + keys[r - 1]) % c;

    vector<int> diff(n + 1, 0);
    for (int r = 0; r < (n - m + 1); r++) {
        diff[r] += 1;
        diff[m + r] -= 1;
    }

    for (int r = 1; r <= n; r++)
        diff[r] += diff[r - 1];

    for (int r = 0; r < n; r++) {
        int right = min(r, m - 1);
        int left = right - diff[r] + 1;

        int add_value = (prefix[right + 1] - prefix[left] + c) % c;
        arr[r] = (arr[r] + add_value) % c;
    }

    for (int val : arr)
        cout << val << ' ';
    cout << '\n';
    return 0;
}
