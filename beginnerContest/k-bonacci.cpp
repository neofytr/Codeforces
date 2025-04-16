#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000000

int main()
{
    int n, k;
    cin >> n >> k;

    vector<long long> A(n + 1);
    vector<long long> prefix(n + 2);

    for (int i = 0; i <= n; ++i)
    {
        if (i < k)
        {
            A[i] = 1;
        }
        else
        {
            A[i] = (prefix[i] - prefix[i - k] + MOD) % MOD;
        }
        prefix[i + 1] = (prefix[i] + A[i]) % MOD;
    }

    cout << A[n] << endl;
    return 0;
}
