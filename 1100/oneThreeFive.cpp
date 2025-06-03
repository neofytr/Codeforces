#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int answer(vector<int> &dp, int num)
{
    if (num <= 0)
        return 0;

    if (dp[num] != -1)
        return dp[num];

    switch (num)
    {
    case 1:
        return dp[num] = 1;
    case 2:
        return dp[num] = 2;
    case 3:
        return dp[num] = 3;
    case 4:
        return dp[num] = 1;
    case 5:
        return dp[num] = 0;
    default:
        return dp[num] = min({1 + answer(dp, num - 1),
                              answer(dp, num - 3),
                              answer(dp, num - 5)});
    }
}

void solve()
{
    int n;
    cin >> n;
    vector<int> dp(n + 1, -1);
    cout << answer(dp, n) << '\n';
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
