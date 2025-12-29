#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    string s1, s2;
    cin >> s1 >> s2;

    int final = 0;
    for (const char c : s1)
        if (c == '+')
            final++;
        else
            final--;

    const int len = (int)s2.length();
    int totalcnt = 0, finalcnt = 0;
    for (int subset = 0; subset < (1ll << len); subset++) {
        bool isvalid = true;
        for (int b = 0; b < len; b++)
            if (s2[b] != '?' && s2[b] != ((1ll << b) & subset ? '+' : '-')) {
                isvalid = false;
                break;
            }

        int org = 0;
        if (isvalid) {
            for (int b = 0; b < len; b++)
                if ((1ll << b) & subset)
                    org++;
                else
                    org--;

            if (org == final)
                finalcnt++;
            totalcnt++;
        }
    }

    cout << setprecision(24) << ((double)finalcnt) / totalcnt << endl;
    return 0;
}