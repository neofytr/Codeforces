#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: worms
// URL: https://codeforces.com/problemset/problem/474/B
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> pile(n);
    for (int &val : pile)
        cin >> val;

    int m;
    cin >> m;
    vector<int> juicy(m);
    int val;
    for (int index = 0; index < m; index++) {
        cin >> val;
        val--;
        juicy[index] = val;
    }

    vector<int> start(n);
    start[0] = 0;
    // start[r] = start[r - 1] + pile[r - 1];
    for (int i = 1; i < n; i++) {
        start[i] = start[i - 1] + pile[i - 1];
    }

    // we are to find the max index r such that juicy[k] >= start[r]
    // start is monotonic

    for (int k = 0; k < m; k++) {
        int elt = juicy[k];

        int left = -1;
        int right = n;

        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (elt >= start[mid])
                left = mid;
            else
                right = mid;
        }

        cout << left + 1 << endl;
    }

    return 0;
}