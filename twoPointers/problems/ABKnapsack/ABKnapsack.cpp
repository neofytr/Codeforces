#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: ABKnapsack
// URL: https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/H
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, A, B;
    cin >> n >> m >> s >> A >> B;

    vector<int> costA(n), costB(m);
    for (int &x : costA)
        cin >> x;
    for (int &x : costB)
        cin >> x;

    // Sort descending (take expensive items first)
    sort(costA.rbegin(), costA.rend());
    sort(costB.rbegin(), costB.rend());

    vector<int> prefA(n + 1, 0), prefB(m + 1, 0);
    for (int i = 0; i < n; i++)
        prefA[i + 1] = prefA[i] + costA[i];
    for (int i = 0; i < m; i++)
        prefB[i + 1] = prefB[i] + costB[i];

    int ans = 0;

    for (int i = 0; i <= n; i++) {
        int weightA = i * A;
        if (weightA > s)
            break; // too heavy already

        int rem = s - weightA;
        int j = min(m, rem / B);
        ans = max(ans, prefA[i] + prefB[j]);
    }

    cout << ans << "\n";
    return 0;
}
