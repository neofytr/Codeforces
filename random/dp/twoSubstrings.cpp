#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    string str;
    cin >> str;

    int n = (int)str.length();
    vector<char> chr(n + 1);

    for (int r = 1; r <= n; r++)
        chr[r] = str[r - 1];

    vector<bool> ab(n + 1, false);
    vector<bool> ba(n + 1, false);
    vector<bool> done(n + 1, false);

    if (chr[2] == 'A' && chr[1] == 'B')
        ba[2] = true;
    if (chr[1] == 'A' && chr[2] == 'B')
        ab[2] = true;
    for (int r = 3; r <= n; r++) {
        ba[r] = ba[r - 1] || (chr[r] == 'A' && chr[r - 1] == 'B');
        ab[r] = ab[r - 1] || (chr[r] == 'B' && chr[r - 1] == 'A');

        if (done[r - 1])
            done[r] = true;

        if (chr[r] == 'A' && chr[r - 1] == 'B')
            if (ab[r - 2])
                done[r] = true;

        if (chr[r] == 'B' && chr[r - 1] == 'A')
            if (ba[r - 2])
                done[r] = true;
    }

    cout << (done[n] ? "YES" : "NO") << endl;
    return 0;
}