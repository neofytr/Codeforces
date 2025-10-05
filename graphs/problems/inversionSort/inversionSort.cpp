#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: inversionSort
// URL: https://www.spoj.com/problems/INVESORT/
// Difficulty: hard
// Tags: 
// Strategy: 

string invert(string &str, int l, int r) {
    string cp = str;
    for (int i = l, j = r; i <= r, j >= l; i++, j--)
        cp[i] = str[j];
    return cp;
}

vector<pair<int,int>> all_ops;

int bfs_bidirectional(string src, string dst) {
    if (src == dst) return 0;

    unordered_map<string, int> dist1, dist2;
    queue<string> q1, q2;

    dist1[src] = 0;
    dist2[dst] = 0;
    q1.push(src);
    q2.push(dst);

    while (!q1.empty() && !q2.empty()) {
        if (q1.size() > q2.size()) {
            swap(q1, q2);
            swap(dist1, dist2);
        }

        int sz = q1.size();
        while (sz--) {
            string s = q1.front(); q1.pop();
            int d = dist1[s];

            for (auto [l, r] : all_ops) {
                string t = invert(s, l, r);
                if (!dist1.count(t)) {
                    dist1[t] = d + 1;
                    if (dist2.count(t))
                        return dist1[t] + dist2[t];
                    q1.push(t);
                }
            }
        }
    }
    return -1; // unreachable
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for (int len = 2; len <= 10; len++)
        for (int l = 0; l <= 10 - len; l++) {
            int r = l + len - 1;
            all_ops.push_back({l, r});
        }

    string src, dst;
    while(cin >> src >> dst) {
        if (src == "*" && dst == "*")
            break;

        cout << bfs_bidirectional(src, dst) << "\n";
    }
    return 0;
}
