#include <bits/stdc++.h>
using namespace std;

struct Casino {
    long long l, r, real;
};

void solve() {
    int n;
    long long k;
    cin >> n >> k;

    vector<Casino> casinos(n);
    for (int i = 0; i < n; ++i) {
        cin >> casinos[i].l >> casinos[i].r >> casinos[i].real;
    }

    sort(casinos.begin(), casinos.end(), [](const Casino &a, const Casino &b) { return a.l < b.l; });

    queue<long long> q;
    q.push(k);

    long long maxCoins = k;

    vector<bool> visited(n, false);
    int ptr = 0;

    while (!q.empty()) {
        long long coins = q.front();
        q.pop();
        maxCoins = max(maxCoins, coins);

        while (ptr < n && casinos[ptr].l <= coins) {
            if (!visited[ptr] && coins <= casinos[ptr].r) {
                visited[ptr] = true;
                q.push(casinos[ptr].real);
            }
            ++ptr;
        }

        for (int i = 0; i < n; ++i) {
            if (!visited[i] && casinos[i].l <= coins && coins <= casinos[i].r) {
                visited[i] = true;
                q.push(casinos[i].real);
            }
        }
    }

    cout << maxCoins << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
