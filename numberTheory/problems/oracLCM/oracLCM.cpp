#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: oracLCM
// URL: http://codeforces.com/contest/1349/problem/A
// Difficulty: hard
// Tags: 
// Strategy: 

#define MAX (2 * 1000000)

int power(int base, int exp) {
    int res = 1;
    while(exp) {
        if (exp & 1)
            res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> spf(MAX + 1, -1);
    for (int r = 2; r <= MAX; r++)
        for (int j = r; j <= MAX; j += r)
            if (spf[j] == -1)
                spf[j] = r;
    
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)    
        cin >> val;

    unordered_map<int, multiset<int>> prime;
    for (int val : arr) {
        int x = val;
        while (x != 1) {
            int p = spf[x];
            int pw = 0;
            while(!(x % p))
                pw++, x /= p;

            prime[p].insert(pw);
        }
    }

    int res = 1;
    for (auto &[p, s] : prime)
        if (s.size() == n)
            res *= power(p, *(++s.begin()));
        else if (s.size() == n - 1)
            res *= power(p, *s.begin());

    cout << res << endl;
    return 0;
}