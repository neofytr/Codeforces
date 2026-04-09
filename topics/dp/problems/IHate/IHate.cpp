#include <bits/stdc++.h>
using namespace std;

#define MAX_X (int)(1e9 + 1)

#define int long long

// Problem: IHate
// URL: https://codeforces.com/problemset/problem/1526/B
// Difficulty: hard
// Tags:
// Strategy:

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, x;
    cin >> t;
    while (t--) {
        cin >> x;

        // we are given an integer x
        // can we make x by summing up some number of 11, 111, 1111, 11111, ... and so on
        // we can use any of them any number of times
        // we can make such an x iff x = 11a + 111b for some a, b >= 0 since all 1111, 11111, ... can be
        // expressed as a combination of 11 and 111

        // so x = 11(a + 10b) + b
        // thus for each 0 <= b < 11, we check can we find an a >= 0 such that x = 11(a + 10b) + b

        bool can = false;
        for (int b = 0; b < 11 && !false; b++) {
            int r = x - 111 * b;
            if (r >= 0 && !(r % 11))
                can = true;
        }
        cout << (can ? "YES\n" : "NO\n");
    }
}
