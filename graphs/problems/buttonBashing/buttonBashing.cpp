#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: buttonBashing
// URL: https://open.kattis.com/problems/buttonbashing
// Difficulty: medium
// Tags: 
// Strategy: 

#define MAX (3600)

void solve() {
    int n, t;
        cin >> n >> t;

        vector<int> dist(MAX + 1, LLONG_MAX);
        vector<int> buttons(n);
        for (int &val : buttons)
            cin >> val;

        int src = 0;
        queue<int> que;
        que.push(src);
        dist[src] = 0;

        int miniTime = LLONG_MAX;
        int miniDist;

        while(!que.empty()) {
            int x = que.front();
            que.pop();
            if (x == t) {
                cout << dist[x] << " " << 0 << endl;
                return;
            }

            if (x > t)
                if (x < miniTime)
                    miniTime = x, miniDist = dist[x];


            for (int but : buttons) {
                int nt = x + but;
                if (nt <= 0)
                    nt = 0;
                if (nt >= 3600)
                    nt = 3600;
                if (dist[nt] > dist[x] + 1)
                    dist[nt] = dist[x] + 1, que.push(nt);
            }
        }
        cout << miniDist << " " << miniTime - t << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }    
    return 0;
}