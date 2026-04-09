#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1000000000 + 7)

// Problem: exponentiation
// URL: https://cses.fi/problemset/task/1095
// Difficulty: easy
// Tags: 
// Strategy: 

int pow(int base, int exp) {
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
    
    int n, a, b;
    cin >> n;
    while(n--) {
        cin >> a >> b;
        cout << pow(a, b) << endl;
    }    
    return 0;
}