#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

#define int long long

// Problem: factoryMachines
// URL: https://cses.fi/problemset/task/1620
// Difficulty: easy
// Tags:
// Strategy:

bool canMake(int x, int t, vector<int> &time) {
    // can we make the t products in atmost x time
    int count = 0;
    for (int val : time) {
        count += (x / val);
        if (count >= t)
            return true;
    }

    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    cin >> n >> t;
    vector<int> time(n);
    int maxi = LLONG_MIN;
    for (int &val : time) {
        cin >> val;
        maxi = max(maxi, val);
    }

    // a factory has n machines which can make products
    // we have to make a total of t products
    // for machine r, it takes time[r] seconds to make a single product
    // the machines can work simultaneously and we can freely decide their schedule
    // what is the shortest time needed to make t products

    // if we can make t products in atmost k time, we can make them in atmost k + 1 time too
    int left = 0;             // this time is impossible
    int right = (maxi)*t + 1; // this won't overflow since it can at most 10^18 + 1

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (canMake(mid, t, time))
            right = mid;
        else
            left = mid;
    }

    cout << right << endl;
    return 0;
}