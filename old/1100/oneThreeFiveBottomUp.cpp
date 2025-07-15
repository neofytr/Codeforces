#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> dp(n + 1, -1);
    // dp[r], where 1 <= r <= n is the minimum number of one burles needed to make r

    dp[0] = 0; // base case
    for (int index = 1; index <= n; index++)
    {
        dp[index] = 1 + dp[index - 1];
        if (index >= 3)
        {
            dp[index] = min(dp[index], dp[index - 3]);
        }
        if (index >= 5)
        {
            dp[index] = min(dp[index], dp[index - 5]);
        }
    }

    cout << dp[n] << '\n';
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
