#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    string s;
    cin >> s;

    const int n = (int)s.length();
    vector<int> str(n + 1);
    for (int r = 1; r <= n; r++)
        str[r] = s[r - 1] - 'a';

    priority_queue<pair<int, pair<int, int>>> pq;
    pq.push({0, {1, 2}});
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}