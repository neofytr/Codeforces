#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: prodOneModN
// URL: https://codeforces.com/problemset/problem/1514/C
// Difficulty: medium
// Tags: 
// Strategy: 

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> f;

    for (int r = 1; r < n; r++)
        if (gcd(r, n) == 1)
            f.push_back(r);

    int res = 1;
    for (int g : f)
        res = res * g % n;

    if (res == 1) {
        cout << f.size() << endl;
        for (int g : f)
            cout << g << " ";
        cout << endl;
    } else {
        cout << f.size() - 1 << endl;
        for (int g : f)
            if (g != res)
                cout << g << " ";
        cout << endl;
    }
    return 0;
}