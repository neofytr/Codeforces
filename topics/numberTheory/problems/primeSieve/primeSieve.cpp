#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: primeSieve
// URL: https://open.kattis.com/problems/primesieve
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;

    vector<bool> prime(n + 1, true);
    int cnt = 0;
    for (int r = 2; r <= n; r++)
        if (prime[r]) {
            cnt++;
            for (int j = r * r; j <= n; j += r)
                prime[j] = false;
        }

    cout << cnt << endl;
    while(q--) {
        int x;
        cin >> x;

        if (x == 1)
            cout << 0 << endl;
        else 
            cout << prime[x] << endl;
    }    
    return 0;
}