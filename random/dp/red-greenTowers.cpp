#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)
#define MOD (int)(1e9 + 7)

int32_t main() {
    int r, g;
    cin >> r >> g;

    int left = 1;
    int right = MAX + 1;
    while (right != left + 1)
        if (const int mid = left + (right - left) / 2; (mid * (mid + 1)) / 2 <= (r + g))
            left = mid;
        else
            right = mid;

    // dp[r][s] is the number of red-green towers of height r possible using s red blocks
    vector<int> front(r + 1, 0), back(r + 1, 0);
    front[0] = 1;
    for (int h = 1; h <= left; h++) {
        for (int s = 0; s <= r; s++) {
            back[s] = 0;
            if (const int f = (h * (h + 1)) / 2 - s; f <= g && f >= h)
                back[s] = (back[s] + front[s]) % MOD;
            if (s >= h)
                back[s] = (back[s] + front[s - h]) % MOD;
        }
        swap(front, back);
    }

    int ans = 0;
    for (int s = 0; s <= r; s++) {
        if (const int f = (left * (left + 1)) / 2 - s; f <= g)
            ans = (ans + front[s]) % MOD;
    }
    cout << ans << endl;
    return 0;
}