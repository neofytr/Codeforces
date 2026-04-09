#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: bestie
// URL: https://codeforces.com/problemset/problem/1732/A
// Difficulty: medium
// Tags: 
// Strategy: 

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int solve(vector<int> &arr) {
    int n = (int)arr.size() - 1;

    int g = 0;
    for (int r = 1; r <= n; r++)
        g = gcd(g, arr[r]);

    if (g == 1)
        return 0;

    if (gcd(g, n) == 1)
        return 1;

    if (gcd(g, n - 1) == 1)
        return 2;
    return 3; 
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        vector<int> arr(n + 1);
        for (int r = 1; r <= n; r++)
            cin >> arr[r];

        cout << solve(arr) << endl;
    }    
    return 0;
}