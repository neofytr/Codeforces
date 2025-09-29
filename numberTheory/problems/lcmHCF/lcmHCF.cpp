#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: lcmHCF
// URL: https://vjudge.net/problem/HackerRank-si-lcm-and-hcf
// Difficulty: easy
// Tags: 
// Strategy: 

int hcf(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / hcf(a, b);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    while(t--) {
        int a, b;
        cin >> a >> b;

        cout << lcm(a, b) << " " << hcf(a, b) << "\n";
    }
    return 0;
}