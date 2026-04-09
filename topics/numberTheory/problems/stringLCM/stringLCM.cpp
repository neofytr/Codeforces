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

        int len = lcm((int)s.size(), (int)t.size());

        string S = repeat(s, len / s.size());
        string T = repeat(t, len / t.size());

        if (S == T)
            cout << S << "\n";
        else
            cout << -1 << "\n";
    }
    return 0;
}
