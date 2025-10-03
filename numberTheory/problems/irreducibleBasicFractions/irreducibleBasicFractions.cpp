#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: irreducibleBasicFractions
// URL: https://onlinejudge.org/index.php?option=onlinejudge
// Difficulty: easy
// Tags: 
// Strategy: 

int phi(int n) {
    int res = n;
    for (int r = 2; r * r <= n; r++) 
        if (!(n % r)) {
            while(!(n % r))
                n /= r;
            res -= res / r;
        }
    if (n > 1) res -= res / n;
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while(cin >> n, n) {
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }

        cout << phi(n) << endl;
    }
    return 0;
}