#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX 10000

// Problem: primePath
// URL: https://open.kattis.com/problems/primepath
// Difficulty: hard
// Tags: 
// Strategy: 

vector<bool> sieve() {
    vector<bool> primes(MAX, true);
    primes[0] = primes[1] = false;
    for (int i = 2; i * i < MAX; i++) {
        if (primes[i]) {
            for (int j = i * i; j < MAX; j += i)
                primes[j] = false;
        }
    }
    return primes;
}

int bfs(int start, int target, const vector<bool> &primes) {
    if (start == target) return 0;

    vector<int> dist(MAX, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        string s = to_string(cur);

        for (int pos = 0; pos < 4; pos++) {
            char orig = s[pos];
            for (char d = '0'; d <= '9'; d++) {
                if (d == orig) continue;

                s[pos] = d;
                int nxt = stoi(s);

                if (nxt >= 1000 && primes[nxt] && dist[nxt] == -1) {
                    dist[nxt] = dist[cur] + 1;
                    if (nxt == target) return dist[nxt];
                    q.push(nxt);
                }
            }
            s[pos] = orig; // restore
        }
    }

    return -1; // impossible
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto primes = sieve();

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        int ans = bfs(a, b, primes);
        if (ans == -1)
            cout << "Impossible\n";
        else
            cout << ans << "\n";
    }
}