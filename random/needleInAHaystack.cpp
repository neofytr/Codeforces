#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s, t;
    cin >> s >> t;

    vector<int> rem(26, 0), need(26, 0);
    for (char c : t) rem[c - 'a']++;
    for (char c : s) need[c - 'a']++;

    // Frequency feasibility
    for (int i = 0; i < 26; i++) {
        if (need[i] > rem[i]) {
            cout << "Impossible\n";
            return;
        }
    }

    int ptr = 0;              
    string ans;

    for (int step = 0; step < (int)t.size(); step++) {
        for (int c = 0; c < 26; c++) {
            if (rem[c] == 0) continue;

            rem[c]--;

            bool advances = false;
            if (ptr < (int)s.size() && c == s[ptr] - 'a') {
                need[c]--;
                ptr++;
                advances = true;
            }

            bool ok = true;
            for (int i = 0; i < 26; i++) {
                if (need[i] > rem[i]) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                ans.push_back(char(c + 'a'));
                break;
            }

            rem[c]++;
            if (advances) {
                ptr--;
                need[c]++;
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
}
