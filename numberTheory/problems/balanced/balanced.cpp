#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: balanced
// URL: https://codeforces.com/problemset/problem/1925/B
// Difficulty: medium
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n, x;
        cin >> x >> n;

        int maxi = LLONG_MIN;
        for (int r = 1; r * r <= x; r++) {
            if (!(x % r)) {
                int d1 = r;
                int d2 = x / r;

                if (d2 >= n)
                    maxi = max(maxi, d1);
                if (d1 >= n)
                    maxi = max(maxi, d2);
            }
        }
        cout << maxi << endl;
    }    
    return 0;
}