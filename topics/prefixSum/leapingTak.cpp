// https://atcoder.jp/contests/abc179/tasks/abc179_d

#include <bits/stdc++.h>
using namespace std;

#define MOD 998244353

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> arr(n + 1, 0);
    arr[1] = 1;

    vector<pair<int, int>> segments(k);
    for (auto &segment : segments)
    {
        cin >> segment.first >> segment.second;
    }

    vector<int> prefix(n + 2, 0);
    prefix[1] = 1;
    for (int index = 2; index <= n; index++)
    {
        for (auto [l, r] : segments)
        {
            int left = max(1, index - r);
            int right = index - l;
            if (right < 1)
                continue;

            int add = (prefix[right] - prefix[left - 1] + MOD) % MOD;
            arr[index] = (arr[index] + add) % MOD;
        }

        prefix[index] = (prefix[index - 1] + arr[index]) % MOD;
    }

    cout << arr[n] << endl;
    return EXIT_SUCCESS;
}