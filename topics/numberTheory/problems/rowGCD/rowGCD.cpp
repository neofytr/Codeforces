#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: rowGCD
// URL: https://codeforces.com/problemset/problem/1458/A
// Difficulty: hard
// Tags:
// Strategy:

int gcd(const int a, const int b) {
    if (!b)
        return a;
    return gcd(b, a % b);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> A(n), B(m);
    for (int &val : A)
        cin >> val;
    for (int &val : B)
        cin >> val;

    if (n == 1) {
        for (int j = 0; j < m; j++)
            cout << A[0] + B[j] << " ";
        cout << endl;
        return 0;
    }
    if (n == 2) {
        for (int j = 0; j < m; j++)
            cout << gcd(A[0] + B[j], A[1] + B[j]) << " ";
        cout << endl;
        return 0;
    }

    int miniOne = 0;
    for (int r = 1; r < n - 1; r++)
        miniOne = gcd(miniOne, gcd(abs(A[r] - A[0]), abs(A[r + 1] - A[0])));

    for (int j = 0; j < m; j++) {
        const int g = gcd(miniOne, gcd(abs(A[0] + B[j]), abs(A[1] - A[0])));
        cout << g << " ";
    }
    cout << endl;
    return 0;
}