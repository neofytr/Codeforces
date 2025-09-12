#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: arpa
// URL: https://codeforces.com/problemset/problem/742/A
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    if (!n) {
        cout << 1;
        return 0;
    }
    if (n % 4 == 1)
        cout << 8;
    else if (n % 4 == 2)
        cout << 4;
    else if (n % 4 == 3)
        cout << 2;
    else
        cout << 6;
    cout << endl;

    return 0;
}