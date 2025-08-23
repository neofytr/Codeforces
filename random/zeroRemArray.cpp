#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;

        unordered_map<int, int> freq;

        for (const int val : arr) {
            if (const int r = val % k) {
                int need = k - r;
                freq[need]++;
            }
        }

        long long ans = 0;
        for (auto &[need, c] : freq) {
            long long moves = (c - 1) * 1LL * k + need;
            ans = max(ans, moves);
        }

        if (!ans)
            cout << 0 << "\n";
        else
            cout << ans + 1 << "\n"; // +1 because we need to actually perform the final increment
    }

    return 0;
}
