#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: GCDEX
// URL: https://www.spoj.com/problems/GCDEX/
// Difficulty: hard
// Tags: 
// Strategy: 

#define MAX (1000000)

int phi[MAX + 1];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int r = 1; r <= MAX; r++)
        phi[r] = r;
    for (int r = 2; r <= MAX; r++)
        if (phi[r] == r)
            for (int j = r; j <= MAX; j += r)
                phi[j] -= phi[j] / r;

    vector<int> res(MAX + 1, 0);
    for (int r = 1; r <= MAX; r++)
        for (int j = r; j <= MAX; j += r)
            res[j] += r * phi[j / r];

    vector<int> prefix(MAX + 1, 0);
    for (int r = 1; r <= MAX; r++)
        prefix[r] = prefix[r - 1] + res[r];
    
    int n;
    while (cin >> n, n) 
        cout << prefix[n] - (n * (n + 1)) / 2 << endl;
    return 0;
}