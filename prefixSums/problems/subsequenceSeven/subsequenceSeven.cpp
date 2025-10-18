#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: subsequenceSeven
// URL: https://usaco.org/index.php?page=viewproblem2&cpid=595
// Difficulty: hard
// Tags: 
// Strategy: 

int32_t main() {
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    vector<int> cows(n);
    for (int &val : cows)
        cin >> val;

    vector<int> prefix(n + 1, 0);
    for (int r = 1; r <= n; r++)
        prefix[r] += prefix[r - 1] + cows[r - 1];

    // for any 0 <= l <= r < n such that sum[l, r] % 7 = 0
    //, sum[l, r] % 7 = 0 iff (prefix[r + 1] - prefix[l]) % 7 iff prefix[r + 1] % 7 = prefix[l] % 7

    vector<int> c(n + 1, 0);
    for (int r = 1; r <= n; r++)
        c[r] = prefix[r] % 7;

    // Let 0 <= r < n
    // For any 0 <= l <= r, sum[l, r] % 7 = 0 is possible iff c[r + 1] = c[l]
    // So the number of subarrays ending at r that have sum divisible by 7 are precisely
    // the number of values in the range {c[0], c[1], ..., c[r]} such that c[x] = c[r + 1] for 0 <= x <= r

    // So, the maximum possible length subarray ending at r that has its sum divisible
    // by 7 is the subarray arr[l, r] where 0 <= l <= r such that c[l] is the first occurrence
    // of c[r + 1] in the range {c[0], ..., c[r]}

    // int cnt = 0;

    // at the beginning of each iteration, mp[k] is the number of values in the range [c[0], c[r]]
    // that have their values equal to k
    // unordered_map<int, int> mp;
    // mp[c[0]] = 1; // to maintain the invariant initially
 
    // for (int r = 0; r < n; r++) {
    //     int target = c[r + 1];
    //     cnt += mp[target];
 
    //     mp[target]++; // to maintain the invariant for the next iteration
    // }

    // cout << cnt << endl;

    // at the beginning of iteration r = a, mp[k] is the 
    // index of first occurence of k in the range {c[0], ..., c[a]}
    vector<int> mp(7, -1);
    int maxi = 0;

    // maintaining the invariant initially
    mp[c[0]] = 0;
    for (int r = 0; r < n; r++) {
        int target = c[r + 1];
        if (mp[target] != -1) 
            maxi = max(maxi, r - mp[target] + 1);
        else 
            mp[target] = r + 1; // since it's c[r + 1], we set the indexes according
            // to the range {c[0], ..., c[r + 1]}
    }

    cout << maxi << endl;
    return 0;
}