#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, m;
    cin >> n >> m;

    int nsaved = 0;
    vector<int> inf(m);
    priority_queue<int> pq;
    for (int r = 0; r < m; r++)
        cin >> inf[r];

    sort(inf.begin(), inf.end());
    for (int r = 0; r < m - 1; r++)
        pq.push(inf[r + 1] - inf[r] - 1);

    int d = 0;
    pq.push(n - inf[m - 1] + inf[0] - 1);

    while (!pq.empty()) {
        int v = pq.top();
        pq.pop();
        v -= 2 * d;
        if (v <= 2) {
            d++;
            if (v >= 1)
                nsaved++;
            continue;
        }
        nsaved += (v - 1), d += 2;
    }

    cout << n - nsaved << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}