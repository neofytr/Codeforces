#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: excitingBets
// URL: https://codeforces.com/problemset/problem/1543/A
// Difficulty: medium
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int a, b;
        cin >> a >> b;

        int A = max(a, b);
        int B = min(a, b);

        if (A == B)
            cout << "0 0\n";
        else {
            int l = A - B;
            int r = B % l;

            cout << l << " " << min(r, l - r) << endl;
        }
    }    
    return 0;
}