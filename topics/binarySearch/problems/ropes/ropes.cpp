#include <bits/stdc++.h>
#include <iomanip>
#include <vector>
using namespace std;

// Problem: ropes
// URL: https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/B
// Difficulty: easy
// Tags:
// Strategy:

#define int long long

bool canCut(double x, int k, vector<double> &arr) {
    int count = 0;
    for (double &val : arr) {
        count += (int)(val / x);
        if (count >= k)
            return true;
    }

    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    double maxi = -1;
    vector<double> arr(n);
    for (double &val : arr) {
        cin >> val;
        maxi = fmax(maxi, val);
    }

    // there are n ropes; we need to cut k pieces of the same length from them
    // find the maximum length of pieces we can get

    // if we cannot cut k pieces of length r, we cannot cut k pieces of length x for any x >= r

    double left = 0;         // we can always cut k pieces of length zero
    double right = maxi + 1; // to cut k pieces with this is obv impossible

    for (int iter = 0; iter < 100; iter++) {
        double mid = left + (right - left) / 2;
        if (canCut(mid, k, arr))
            left = mid;
        else
            right = mid;
    }

    cout << setprecision(12) << right << endl;
    return 0;
}