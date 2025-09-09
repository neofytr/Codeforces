#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: hayBale
// URL: https://usaco.org/index.php?page=viewproblem2
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    // freopen(stdin, "hayfeast.in");
    // freopen(stdout, "hayfeast.out");

    int n, m;
    cin >> n >> m;

    vector<int> flavor(n);
    vector<int> spice(n);
    for (int r = 0; r < n; r++)
        cin >> flavor[r] >> spice[r];

    // supersegment monotonic
    multiset<int> sp;
    int sum = 0;
    int l = 0;
    int miniSpice = LLONG_MAX;
    for (int r = 0; r < n; r++) {
        sum += flavor[r];
        sp.insert(spice[r]);
        while (l <= r && sum >= m)
            miniSpice = min(miniSpice, *sp.rbegin()), sp.erase(sp.find(spice[l])), sum -= flavor[l++];
    }
    cout << miniSpice << endl;
    return 0;
}