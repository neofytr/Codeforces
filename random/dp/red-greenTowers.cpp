#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)
#define MOD (int)(1e9 + 7)

// Let f(n) = "If (n * (n + 1)) / 2 <= r + g, then a tower of height n can be formed" for some natural n is the
// induction hypothesis

// Base Case:
// Since r + g >= 1, We have at-least one block of either r or g.
// Whatsoever color may it be, a single
// block of that color can be used to build a tower of height 1. Since (1 * (1 + 1) / 2 <= r + g, and
// we can build a tower of height 1, f(1) is true

// Inductive Step
// Suppose that f(n) is true for some n >= 1
// Let ((n + 1) * (n + 2)) / 2 <= r + g
// In a tower of height n + 1, the base layer would be of n + 1 blocks of the same color, and above it
// will be a tower of height n
// Now, at-least one of r and g is >= n + 1, otherwise, if both r and g <= n, then
// ((n + 1) * (n + 2)) / 2 <= 2 * n is impossible for any n >= 1
// WLOG, assume that r >= n + 1. Then, we build the base layer with red blocks
// Now, we are left with (r + g - (n + 1)) blocks to build a tower of height n
// Since ((n + 1) * (n + 2)) / 2 <= r + g implies that (n * (n + 1)) / 2 <= (r + g - (n + 1)), and since
// f(n) is true, we can build a tower of height n using the remaining blocks
// Thus, we have f(k + 1)

// Thus, using the axiom of Induction, it can be concluded that f(n) is true for all integral n >= 1

int32_t main() {
    int r, g;
    cin >> r >> g;

    int left = 0;
    int right = MAX + 1;
    while (right != left + 1)
        if (const int mid = left + (right - left) / 2; (mid * (mid + 1)) / 2 <= r + g)
            left = mid;
        else
            right = mid;

    vector<int> one(r + 1, 0), two(r + 1, 0);
    one[0] = 1;
    for (int h = 1; h <= left; h++) {
        ranges::fill(two, 0);
        for (int c = 0; c <= r; c++) {
            if (const int f = (h * (h + 1)) / 2 - c; f <= g && f >= h)
                two[c] = (two[c] + one[c]) % MOD;
            if (c >= h)
                two[c] = (two[c] + one[c - h]) % MOD;
        }
        swap(one, two);
    }

    int res = 0;
    for (int c = 0; c <= r; c++) {
        if (const int f = (left * (left + 1)) / 2 - c; f <= g)
            res = (res + one[c]) % MOD;
    }

    cout << res << endl;
    return 0;
}