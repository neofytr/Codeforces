#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: etf
// URL: https://www.spoj.com/problems/ETF/
// Difficulty: easy
// Tags: 
// Strategy: 

#define MAX 1000000

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;

    vector<int> phi(MAX + 1);
    for (int r = 1; r <= MAX; r++)
        phi[r] = r;

    for (int r = 2; r <= MAX; r++)
        if (phi[r] == r) // prime
            for (int j = r; j <= MAX; j += r)
                phi[j] -= phi[j] / r;

    while(t--) {
        int n;
        cin >> n;
        cout << phi[n] << endl;
    }    
    return 0;
}