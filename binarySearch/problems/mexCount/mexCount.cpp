#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;

#define int long long

// Problem: mexCount
// URL: https://codeforces.com/problemset/problem/2123/E
// Difficulty: hard
// Tags:
// Strategy:

void solve() {
    int n;
    cin >> n;

    unordered_map<int, int> freq;
    vector<int> arr(n);
    int val;
    for (int i = 0; i < n; i++) {
        cin >> val;
        arr[i] = val;
        freq[val]++;
    }

    int totalConsec = 0;
    for (int i = 0; i <= n; i++) {
        if (!freq[i])
            break;
        else {
            totalConsec++;
        }
    }

    // mex(arr) can only belong to the set {0, 1, ..., totalConsec - 1, totalConsec}, no matter how
    // many times we delete

    int canDelete = 0;
    for (auto &[val, f] : freq) {
        if (val < totalConsec)
            canDelete += (f - 1); // since we need atleast one
        else
            canDelete += f;
    }

    for (int k = 0; k <= n; k++) {
        if (!k) {
            cout << 1 << " ";
            continue;
        }

        int cnt = 0;
        for (int c = 0; c <= totalConsec; c++) {
            // we can make this mex after exactly k deletions iff freq[c] <= k and the values that we can delete >= (k - freq[c])
            if (freq[c] <= k && (canDelete - freq[c] + 1 * (totalConsec - c)) >= (k - freq[c])) // since we can delete anything  > c and < totalConsec one more time, we add one for them
                                                                                                // since we already deleted all c, we remove it from canDelete
                cnt++;
        }

        cout << cnt << " ";
    }
    cout << endl;
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