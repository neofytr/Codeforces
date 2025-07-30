#include <bits/stdc++.h>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

#define int long long

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> b(n);

    unordered_map<int, int> freq;
    vector<bool> assigned(n, false);
    priority_queue<int, vector<int>, greater<>> que;
    for (int index = 0; index < n; index++) {
        int x;
        cin >> x;
        freq[x]++;
    }

    int total = 0;
    for (int index = 0; index < n; index++) {
        if (freq[m - b[index]]) {
            freq[m - b[index]]--;
            assigned[index] = true;
            continue;
        }
        total = (total + b[index]) % m;
    }

    for (auto &elt : freq) {
        int a = elt.first;
        total = (total + (a * freq[a]) % m) % m;
    }

    cout << total << endl;
    return;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}