#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
    int n;
    cin >> n;

    long long ones = 0, zeroes = 0;
    vector<int> even, odd;
    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        for (char c : s) {
            if (c == '0') ++zeroes;
            else ++ones;
        }
        if (!((int)s.length() & 1)) even.push_back(s.length());
        else odd.push_back(s.length());
    }

    sort(even.begin(), even.end());
    sort(odd.begin(), odd.end());

    long long pairs = (zeroes >> 1) + (ones >> 1);
    long long singles = (zeroes & 1) + (ones & 1);

    int res = 0;

    for (int len : even) {
        long long need = len >> 1;
        if (pairs >= need) {
            pairs -= need;
            ++res;
        } else break;
    }

    for (int len : odd) {
        long long need = len >> 1;
        if (pairs < need) break;
        pairs -= need;

        if (!singles) {
            if (!pairs) break;   // cannot create a single
            pairs--;                 // convert 1 pair -> 2 singles
            singles += 2;
        }
        --singles;
        ++res;
    }

    cout << res << '\n';
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
