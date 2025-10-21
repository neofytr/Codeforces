#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n, z;
    cin >> n >> z;

    int val;
    priority_queue<int> pq;
    for (int r = 1; r <= n; r++)
        cin >> val, pq.push(val);

    int at = 0;
    while(!pq.empty()) {
        int x = pq.top();
        pq.pop();

        z -= x, at++;
        if (z <= 0) {
            cout << at << endl;
            return;
        }

        if (x / 2 > 0)
            pq.push(x / 2);
    }

    cout << "Evacuate\n";
    return;
}

int32_t main() {
    int t;
    cin >> t;

    while(t--) {
        solve();
    }
    return 0;
}
