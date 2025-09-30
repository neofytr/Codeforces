#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: lcmProb
// URL: https://codeforces.com/problemset/problem/1389/A
// Difficulty: medium
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int l, r;
        cin >> l >> r;

        if (2 * l > r)
            cout << -1 << " " << -1 << endl;
        else 
            cout << l << " " << 2 * l << endl;
    }    
    return 0;
}