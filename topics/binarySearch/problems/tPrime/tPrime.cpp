#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <system_error>
#include <vector>
using namespace std;

#define int long long

// Problem: tPrime
// URL: https://codeforces.com/problemset/problem/230/B
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // we call a positive integer T-prime iff it has exactly three distinct positive divisors
    for (int val : arr) {
        if (val == 1) {
            cout << "NO\n";
            continue;
        }

        // now val has two divisors, 1 and itself and both are distinct (since val != 1)
        // if it has exactly one more divisor, we are done
        int left = 2;
        int right = val - 1;

        // if it has exactly one divisor in this range, we are done
        // but, if it has a divisor r, then it also has a divisor val / r
        // for them to be the same r * r = val
        // i.e, val is a perfect square

        // if val isn't a perfect square, it will have an even number of divisors, so it can't be a T-prime
        // if val is a perfect square, such that val = r * r, its a T-prime only when r is a prime number

        int sqroot = sqrt(val);
        if (sqroot * sqroot != val) {
            cout << "NO\n";
            continue;
        }

        // now sqroot needs to be a prime
        int x = sqroot;
        bool cond = false;
        for (int i = 2; i <= sqrt(x); i++) {
            int q = x / i;
            if (i * q == x) {
                cond = true;
                break;
            }
        }

        if (cond) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }

    return 0;
}