#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= 1000000007;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % 1000000007;
        base = (base * base) % 1000000007;
        exp /= 2;
    }
    return res;
}

long long calculate_ruler_product(long long pos, long long d) {
    if (d <= 0)
        return 1;

    long long res = 1;
    long long p_start = pos;
    long long p_end = pos + d - 1;

    for (long long j = 1; j <= 62; ++j) {
        long long pw2_jm1 = 1LL << (j - 1);

        if (pw2_jm1 > p_end)
            break;

        long long L = (p_start + pw2_jm1 - 1) / pw2_jm1;
        long long R = p_end / pw2_jm1;

        if (L > R)
            continue;

        long long num_odds = (R + 1) / 2 - L / 2;

        if (num_odds > 0) {
            res = (res * power(j, num_odds)) % 1000000007;
        }
    }
    return res;
}

void solve() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    sort(s.begin(), s.end());

    long long C = 0;
    long long ans = 1;
    long long ruler_idx = 1;

    for (int i = 0; i < n; ++i) {
        long long current_s = s[i];

        long long ops_on_gen = min(k, C);

        if (ops_on_gen > 0) {
            long long product = calculate_ruler_product(ruler_idx, ops_on_gen);
            ans = (ans * product) % 1000000007;

            ruler_idx += ops_on_gen;
            k -= ops_on_gen;
            C -= ops_on_gen;
        }

        if (k == 0)
            break;

        k--;
        ans = (ans * current_s) % 1000000007;
        C += current_s - 1;

        if (k == 0)
            break;
    }

    if (k > 0) {
        long long ops_on_gen = min(k, C);
        if (ops_on_gen > 0) {
            long long product = calculate_ruler_product(ruler_idx, ops_on_gen);
            ans = (ans * product) % 1000000007;
        }
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}