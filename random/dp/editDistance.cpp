#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(5 * 1e3)

int v1[MAX + 1], v2[MAX + 1];
int dp[MAX + 1][MAX + 1];

int32_t main() {
    string s1, s2;
    cin >> s1 >> s2;

    int sz1 = (int)s1.length();
    int sz2 = (int)s2.length();

    for (int r = 1; r <= sz1; r++)
        v1[r] = s1[r - 1] - 'A';
    for (int r = 1; r <= sz2; r++)
        v2[r] = s2[r - 1] - 'A';

    // dp[n][m] is the minimum number of operations required to convert v1[1, n] into v2[1, m]
    dp[0][0] = 0;
    for (int n = 1; n <= sz1; n++)
        dp[n][0] = n;
    for (int m = 1; m <= sz2; m++)
        dp[0][m] = m;
    for (int n = 1; n <= sz1; n++)
        for (int m = 1; m <= sz2; m++)
            if (v1[n] == v2[m])
                dp[n][m] = dp[n - 1][m - 1];
            else {
                int one = dp[n - 1][m - 1] + 1; // replace
                int two = dp[n][m - 1] + 1;     // insert a character into v1
                int three = dp[n - 1][m] + 1;   // deleting a character from v1
                dp[n][m] = min(one, min(two, three));
            }

    cout << dp[sz1][sz2] << endl;
    return 0;
}