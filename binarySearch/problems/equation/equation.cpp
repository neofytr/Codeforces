#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

#define int long long

// Problem: equation
// URL: https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/E
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double c;
    cin >> c;

    // we are to find an x such that x^2 + root(x) = c
    // such an x must be >= 0 since c is a real number
    // also x != 0 since c >= 1
    // let f(x) = x^2 + root(x) for x >= 0
    // f is a strictly increasing function
    // we find a point y such that f(r) >= c for all r >= y and f(r) < c for all r < y

    double left = 0;     // not possible
    double right = 1e12; // possible

    for (int i = 0; i < 100; i++) {
        double mid = left + (right - left) / 2;
        if (mid * mid + sqrt(mid) >= c)
            right = mid;
        else
            left = mid;
    }

    cout << setprecision(16) << right << endl;

    return 0;
}