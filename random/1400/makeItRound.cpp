#include <bits/stdc++.h>
using namespace std;

#define int long long

int pw(int base, int exp, int limit) {
    int res = 1;
    while (exp) {
        if (exp & 1) {
            if (res > limit / base) return limit + 1;
            res *= base;
        }
        if (base > limit / base) base = limit + 1;
        else base *= base;
        exp >>= 1;
    }
    return res;
}

void solve(int) {
    int n, m;
    cin >> n >> m;

    int x = 0, y = 0;
    int nc = n;

    while (nc % 2 == 0) {
        nc /= 2;
        x++;
    }
    while (nc % 5 == 0) {
        nc /= 5;
        y++;
    }

    if (x < y) {
        if (pw(2, y - x, m) <= m) {
            for (int r = 12; r >= 0; r--) {
                int g = pw(2, y - x + r, m);
                if (g > m) continue;
                g *= pw(5, r, m);
                if (g > m) continue;

                for (int t = 9; t >= 1; t--) {
                    if (t * g <= m) {
                        cout << n * t * g << '\n';
                        return;
                    }
                }
            }
        } else {
            for (int r = y - x - 1; r >= 0; r--) {
                int g = pw(2, r, m);
                if (g <= m) {
                    cout << n * g << '\n';
                    return;
                }
            }
        }
    } else {
        if (pw(5, x - y, m) <= m) {
            for (int r = 12; r >= 0; r--) {
                int g = pw(2, r, m);
                if (g > m) continue;
                g *= pw(5, x - y + r, m);
                if (g > m) continue;

                for (int t = 9; t >= 1; t--) {
                    if (t * g <= m) {
                        cout << n * t * g << '\n';
                        return;
                    }
                }
            }
        } else {
            for (int r = x - y - 1; r >= 0; r--) {
                int g = pw(5, r, m);
                if (g > m) continue;

                for (int t = 4; t >= 1; t--) {
                    if (t * g <= m) {
                        cout << n * t * g << '\n';
                        return;
                    }
                }
            }
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve(0);
    return 0;
}
