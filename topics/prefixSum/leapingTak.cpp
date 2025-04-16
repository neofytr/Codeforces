// https://atcoder.jp/contests/abc179/tasks/abc179_d

#include <bits/stdc++.h>
using namespace std;

#define MOD 998244353

int calculate(vector<int> &allowed, vector<int> &memoized, int index)
{
    if (index < 1)
    {
        return 0;
    }

    if (index == 1)
    {
        return 1;
    }

    int sum = 0;
    for (int i = 1; i < allowed.size(); i++)
    {
        if (allowed[i])
        {
            if (memoized[index - i] == -1)
            {
                memoized[index - i] = calculate(allowed, memoized, index - i) % MOD;
            }
            sum += memoized[index - i] % MOD;
        }
    }

    return sum % MOD;
}

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> allowed(n + 2, 0);

    int l, r;
    while (k--)
    {
        cin >> l >> r;

        allowed[l] += 1;
        allowed[r + 1] -= 1;
    }

    // propagate
    for (int index = 1; index <= n + 1; index++)
    {
        allowed[index] += allowed[index - 1];
    }

    vector<int> memoized(n + 1, -1);
    cout << calculate(allowed, memoized, n) << endl;
}