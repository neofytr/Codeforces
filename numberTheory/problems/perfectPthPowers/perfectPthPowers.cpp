#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: perfectPthPowers
// URL: https://open.kattis.com/problems/perfectpowers
// Difficulty: hard
// Tags: 
// Strategy: 

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x;
    while(cin >> x, x) {
         int orig = x;
        x = abs(x);

        int g = 0;
        for (int r = 2; r * r <= x; r++) {
            int cnt = 0;
            while (x % r == 0) {
                cnt++;
                x /= r;
            }
            if (cnt) g = gcd(g, cnt);
        }
        if (x > 1) g = gcd(g, 1);

        // if number is negative, answer must be odd
        if (orig < 0) {
            while (!(g & 1)) g /= 2;
        }

        cout << g << "\n";
    }    
    return 0;
}