#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: doraC++
// URL: https://codeforces.com/contest/2007/problem/C
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n, a, b;
        cin >> n >> a >> b;

        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;

        int g = gcd(a, b);

        vector<int> res(n);
        for (int i = 0; i < n; ++i) res[i] = arr[i] % g;
        sort(res.begin(), res.end());

        int max_gap = 0;
        for (int i = 0; i + 1 < n; ++i) {
            max_gap = max(max_gap, res[i+1] - res[i]);
        }
        max_gap = max(max_gap, (int)(res[0] + g - res[n-1]));

        int answer = g - max_gap;
        cout << answer << '\n';
    }    
    return 0;
}
