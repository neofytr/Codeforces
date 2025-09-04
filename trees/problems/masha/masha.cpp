#include <bits/stdc++.h>
using namespace std;

#define int long long

int cnt = 0;

struct node {
    int mini, maxi;
};

node can(int level, int index, int n, const vector<int> &perm) {
    if (level == n)
        return {perm[index], perm[index]};

    node left = can(level + 1, index * 2, n, perm);
    node right = can(level + 1, index * 2 + 1, n, perm);

    if (left.mini == -1 || right.mini == -1)
        return {-1, -1};

    if (abs(left.maxi - right.mini) > 1 && abs(left.mini - right.maxi) > 1)
        return {-1, -1};

    if (left.mini > right.maxi)
        cnt++;

    return {min(left.mini, right.mini), max(left.maxi, right.maxi)};
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int m;
        cin >> m;

        vector<int> perm(m);
        for (int &val : perm)
            cin >> val;

        cnt = 0;

        int depth = log2(m); // works only if m is a power of two
        node res = can(0, 0, depth, perm);
        if (res.mini == -1)
            cout << -1 << endl;
        else
            cout << cnt << "\n";
        cnt = 0;
    }

    return 0;
}
