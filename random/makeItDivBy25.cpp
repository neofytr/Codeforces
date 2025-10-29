#include <bits/stdc++.h>
using namespace std;

#define int long long

int solve_one(long long n) {
    string s = to_string(n);
    int ans = 1e9;

    vector<string> targets = {"00", "25", "50", "75"};
    for (auto &t : targets) {
        int j = t.size() - 1;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == t[j])
                j--;
            if (j < 0) {
                int deletions = (s.size() - 1 - i) - (t.size() - 1 - j) - 1;
                deletions = (s.size() - i - 2);
                ans = min(ans, deletions);
                break;
            }
        }
    }

    if (ans == 1e9)
        return s.size(); // not possible
    return ans;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        cout << solve_one(n) << "\n";
    }
    return 0;
}
