#include <bits/stdc++.h>
using namespace std;

#define int long long

string repeat(const string &s, int times) {
    string result;
    result.reserve(s.size() * times);
    for (int i = 0; i < times; i++)
        result += s;
    return result;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    while (q--) {
        string s, t;
        cin >> s >> t;

        const char ch = s[0];
        bool ssame = true, tsame = true;
        for (char c : s)
            if (ch != c)
                ssame = false;

        if (ssame) {
            for (char c : t)
                if (ch != c)
                    tsame = false;

            if (tsame) {
                cout << repeat(string(1, ch), lcm(s.size(), t.size())) << "\n";
                continue;
            } else {
                cout << -1 << "\n";
                continue;
            }
        }

        if (t.size() % s.size() == 0) {
            string n = repeat(s, t.size() / s.size());
            if (n == t) {
                cout << t << "\n";
            } else {
                cout << -1 << "\n";
            }
        } else if (s.size() % t.size() == 0) {
            string n = repeat(t, s.size() / t.size());
            if (n == s)
                cout << s << "\n";
            else
                cout << -1 << "\n";
        } else {
            cout << -1 << "\n";
        }
    }

    return 0;
}
