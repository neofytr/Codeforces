#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: dividingSeq
// URL: https://open.kattis.com/problems/sequence
// Difficulty: medium
// Tags: 
// Strategy: 

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> lenEnd(n + 1, 1);
    vector<int> parent(n + 1, -1);

    for (int d = 1; d <= n; d++) {
        for (int m = 2 * d; m <= n; m += d) {
            if (lenEnd[d] + 1 > lenEnd[m]) {
                lenEnd[m] = lenEnd[d] + 1;
                parent[m] = d;
            }
        }
    }

    int bestEnd = max_element(lenEnd.begin(), lenEnd.end()) - lenEnd.begin();
    cout << lenEnd[bestEnd] << "\n";

    vector<int> seq;
    for (int x = bestEnd; x != -1; x = parent[x]) seq.push_back(x);
    reverse(seq.begin(), seq.end());

    for (int x : seq) cout << x << " ";
    cout << "\n";

    return 0;
}