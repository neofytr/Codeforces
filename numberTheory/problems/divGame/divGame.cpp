#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: divGame
// URL: https://atcoder.jp/contests/abc169/tasks/abc169_d
// Difficulty: easy
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    int res = 0;
    for (int p = 2; p * p <= n; p++)
        if (!(n % p)) {
            int cnt = 0;
            while(!(n % p))
                cnt++, n /= p;
            res += (-1 + (int)sqrt(1 + 8 * cnt)) / 2;
        }    
    if (n > 1) res += 1;
    cout << res << endl;
    return 0;
}