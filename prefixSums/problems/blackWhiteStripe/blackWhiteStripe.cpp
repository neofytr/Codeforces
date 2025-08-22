#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: blackWhiteStripe
// URL: https://codeforces.com/contest/1690/problem/D
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        string str;
        cin >> str;

        int l = 0;
        int count = 0;
        int mini = LLONG_MAX;
        for (int r = 0; r < n; r++) {
            if (str[r] == 'W')
                count++;
            while ((r - l + 1) > k) {
                if (str[l] == 'W')
                    count--;
                l++;
            }

            if (r - l + 1 == k) {
                mini = min(count, mini);
            }
        }

        cout << mini << endl;
    }
    return 0;
}