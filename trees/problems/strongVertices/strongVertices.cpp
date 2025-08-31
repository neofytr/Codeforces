#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: strongVertices
// URL: https://codeforces.com/problemset/problem/1857/D
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n + 1), b(n + 1);
        for (int r = 1; r <= n; r++)
            cin >> a[r];
        for (int r = 1; r <= n; r++)
            cin >> b[r];

        // there is an edge from u to v in the graph where 1 <= u != v <= n iff
        // a[u] - a[v] >= b[u] - b[v]
        // iff a[u] - b[u] >= a[v] - b[v]
        // iff c[u] >= c[v]

        vector<int> c(n + 1);
        for (int r = 1; r <= n; r++)
            c[r] = a[r] - b[r];

        // the largest element of c will have vertices to all the other indexes, i.e, to all other
        // possible nodes
        // the next largest element won't be able to reach the largest element anyhow
        // since it would have edges to only smaller elements and any smaller elements will have edges to other smaller elements

        // so, only the maximal vertices will be strong

        int maxi = c[1];
        for (int r = 1; r <= n; r++)
            maxi = max(maxi, c[r]);

        int count = 0;
        vector<int> indexes;
        for (int r = 1; r <= n; r++)
            if (c[r] == maxi)
                indexes.push_back(r), count++;
        cout << count << endl;
        for (int r : indexes)
            cout << r << " ";
        cout << endl;
    }
    return 0;
}