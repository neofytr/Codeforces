#include <bits/stdc++.h>
using namespace std;

#define MOD 998244353

long long mod_pow(long long base, long long exp)
{
    long long res = 1;
    base %= MOD;
    while (exp)
    {
        if (exp & 1)
            res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

long long mod_inv(long long x)
{
    return mod_pow(x, MOD - 2);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<long long> a(n);
    for (auto &x : a)
        cin >> x;

    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; ++i)
        prefix[i] = (prefix[i - 1] + a[i - 1]) % MOD;

    vector<vector<long long>> powP(n + 1, vector<long long>(k + 1, 1));
    for (int i = 0; i <= n; ++i)
    {
        for (int p = 1; p <= k; ++p)
        {
            powP[i][p] = powP[i][p - 1] * prefix[i] % MOD;
        }
    }

    vector<vector<long long>> sumPow(k + 1, vector<long long>(n + 2, 0));
    for (int p = 0; p <= k; ++p)
    {
        for (int i = 1; i <= n + 1; ++i)
        {
            sumPow[p][i] = (sumPow[p][i - 1] + powP[i - 1][p]) % MOD;
        }
    }

    vector<vector<long long>> binom(k + 1, vector<long long>(k + 1, 0));
    for (int i = 0; i <= k; ++i)
    {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; ++j)
        {
            binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % MOD;
        }
    }

    long long result = 0;
    for (int m = 0; m <= k; ++m)
    {
        long long coef = binom[k][m];
        if ((k - m) % 2)
            coef = MOD - coef;

        for (int i = 1; i <= n; ++i)
        {
            long long left_sum = sumPow[k - m][i];
            long long right_pow = powP[i][m];
            result = (result + coef * right_pow % MOD * left_sum % MOD) % MOD;
        }
    }

    cout << result << '\n';
}
