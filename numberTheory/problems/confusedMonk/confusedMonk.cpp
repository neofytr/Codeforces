#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: confusedMonk
// URL: Not provided
// Difficulty: https://www.hackerearth.com/practice/math/number-theory/basic-number-theory-1/practice-problems/algorithm/the-confused-monk/
// Tags:
// Strategy:

#define MOD (1000000000 + 7)

int gcd(int a, int b) {
    if (!b)
        return a;
    return gcd(b, a % b);
}

int exp(int a, int b) {
    if (!b)
        return 1;

    int r = exp(a, b / 2);
    if (b & 1)
        return ((r * r) % MOD * a) % MOD;
    return (r * r) % MOD;
}

int32_t main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    int g = 0;
    for (const int val : arr)
        g = gcd(g, val);

    int f = 1;
    for (const int val : arr)
        f = (f * val) % MOD;

    cout << exp(f, g) << endl;
    return 0;
}