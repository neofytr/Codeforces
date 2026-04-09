#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: yetAnother
// URL: https://codeforces.com/problemset/problem/1511/C
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> colorsToMinIndex(50 + 1, LLONG_MAX); // there are at max 50 colors

    int n, q;
    cin >> n >> q;

    int a;
    for (int r = 1; r <= n; r++) {
        cin >> a;
        colorsToMinIndex[a] = min(colorsToMinIndex[a], r);
    }

    int t;
    while (q--) {
        cin >> t;
        int mini = colorsToMinIndex[t];
        cout << mini << " ";
        for (int c = 1; c <= 50; c++) {
            if (c == t)
                colorsToMinIndex[c] = 1;
            else if (colorsToMinIndex[c] < mini)
                colorsToMinIndex[c]++;
        }
    }
    cout << endl;
    return 0;
}