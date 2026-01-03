#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)
#define MAXNUM (int)(1e1)

int str[MAX + 1];
int odd[MAX + 1][MAXNUM];
int even[MAX + 1][MAXNUM][MAXNUM];

// a1 a2 a3 a4 a5
// a2 a3 a4 a5 a1
// a5 a1 a2 a3 a4

void solve() {
    string s;
    cin >> s;

    const int n = (int)s.length();
    for (int r = 1; r <= n; r++)
        str[r] = s[r - 1] - '0';

    for (int r = 1; r <= n; r++)
        for (int c = 0; c <= 9; c++)
            odd[r][c] = 0;

    odd[1][str[1]] = 1;
    for (int r = 2; r <= n; r++)
        for (int c = 0; c <= 9; c++)
            odd[r][c] += odd[r - 1][c] + (str[r] == c ? 1 : 0);

    for (int r = 1; r <= n; r++)
        for (int c1 = 0; c1 <= 9; c1++)
            for (int c2 = 0; c2 <= 9; c2++)
                even[r][c1][c2] = 0;

    even[2][str[1]][str[2]] = 2;
    for (int c = 0; c <= 9; c++)
        even[1][c][str[1]] = 1;
    for (int c = 0; c <= 9; c++)
        if (c != str[1])
            even[2][c][str[2]] = 1;
    for (int r = 3; r <= n; r++)
        for (int c1 = 0; c1 <= 9; c1++)
            for (int c2 = 0; c2 <= 9; c2++)
                if (c2 == str[r])
                    even[r][c1][c2] += even[r - 1][c2][c1] + 1;
                else
                    even[r][c1][c2] += even[r - 1][c1][c2];

    for (int c1 = 0; c1 <= 9; c1++)
        for (int c2 = 0; c2 <= 9; c2++)
            cout << c1 << " " << c2 << " " << even[n][c1][c2] << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}