#include <bits/stdc++.h>
using namespace std;

// Problem: veryEasyTask
// URL: https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/C
// Difficulty: easy
// Tags:
// Strategy:

#define int long long

bool check(int t, int a, int b, int n) {
    int copies = 0;

    // make the first copy so that we have atleast two copies at anytime to put simultaneously into the copier
    t -= a;
    copies++;

    copies += (t / a + t / b);
    return copies >= n;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x, y;
    cin >> n >> x >> y;

    int a = min(x, y);
    int b = max(x, y);

    // if they can copy in t seconds, then can in t + 1
    int left = 0;          // impossible
    int right = n / a + 1; // possible

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (check(mid, a, b, n)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    cout << right << endl;

    return 0;
}