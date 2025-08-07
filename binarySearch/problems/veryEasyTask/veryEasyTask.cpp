#include <bits/stdc++.h>
using namespace std;

// Problem: veryEasyTask
// URL: https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/C
// Difficulty: easy
// Tags:
// Strategy:

#include <bits/stdc++.h>
using namespace std;

#define int long long

bool check(int t, int x, int y, int n) {
    if (t < min(x, y))
        return false;

    t -= min(x, y);
    int copies = 1 + t / x + t / y;
    return copies >= n;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x, y;
    cin >> n >> x >> y;

    int left = 0;
    int right = min(x, y) + (n - 1) * max(x, y); // safe upper bound

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (check(mid, x, y, n)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << left << endl;

    return 0;
}
