#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: cowsRoadsTwo
// URL: https://usaco.org/index.php?page=viewproblem2&cpid=715
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    freopen("maxcross.in", "r", stdin);
    freopen("maxcross.out", "w", stdout);
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k, b;
    cin >> n >> k >> b;

    int brk;
    vector<bool> signals(n + 1, true);
    while(b--) 
        cin >> brk, signals[brk] = false;

    int maxi = 0;

    // in any k length continuous segment, what is the maximum number of trues?
    int cnt = 0;

    for (int r = 1; r <= k; r++)
        if (signals[r])
            cnt++;
    maxi = max(maxi, cnt);
    int l = 1;
    for (int r = k + 1; r <= n; r++) {
        if (signals[r])
            cnt++;
        if (signals[l++])
            cnt--;
        maxi = max(maxi, cnt);
    }

    cout << k - maxi << endl;
    return 0;
}