#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

#define int long long

// Problem: districtConnections
// URL: https://codeforces.com/problemset/problem/1433/D
// Difficulty: medium
// Tags:
// Strategy:

void solve() {
    int n;
    cin >> n;

    unordered_set<int> gangs;
    unordered_map<int, vector<int>> members;

    int gang;
    for (int index = 1; index <= n; index++) {
        cin >> gang;
        gangs.insert(gang);
        members[gang].push_back(index);
    }

    if (gangs.size() < 2) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    int first = *gangs.begin();
    for (int i = 0; i < members[first].size(); i++) {
        if (!i) {
            // connect this to all other gangs
            for (int gng : gangs) {
                if (gng != first) {
                    for (int v : members[gng]) {
                        cout << members[first][i] << " " << v << endl;
                    }
                }
            }
        } else {
            int second = *(++gangs.begin());
            int elt = members[second][0];
            cout << members[first][i] << " " << elt << endl;
        }
    }

    return;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}