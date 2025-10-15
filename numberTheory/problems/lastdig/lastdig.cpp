#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: lastdig
// URL: https://www.spoj.com/problems/LASTDIG/
// Difficulty: easy
// Tags: 
// Strategy: 

#define MOD 10
int pw(int base, int exp) {
    int res = 1;
    base = base % MOD;
    while(exp) {
        if (exp & 1)
            res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int a, b;
        cin >> a >> b;
        cout << pw(a, b) << endl;
    }    
    return 0;
}