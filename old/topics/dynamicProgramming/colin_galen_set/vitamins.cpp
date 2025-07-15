#include <bits/stdc++.h>
using namespace std;

int solve(vector<pair<int, string>> &juices, vector<vector<int>> &dp, int index, int mask)
{
    if (mask == 0b111) // all vitamins collected
        return 0;
    if (index >= juices.size())
        return -1;
    if (dp[index][mask] != -2)
        return dp[index][mask];

    // calculate new mask if we include this juice
    int new_mask = mask;
    for (char c : juices[index].second)
    {
        if (c == 'A')
            new_mask |= 1 << 0;
        if (c == 'B')
            new_mask |= 1 << 1;
        if (c == 'C')
            new_mask |= 1 << 2;
    }

    // include the juice
    int buy = solve(juices, dp, index + 1, new_mask);
    if (buy != -1)
        buy += juices[index].first;

    // don't include the juice
    int dont_buy = solve(juices, dp, index + 1, mask);

    // choose the best valid option
    if (buy == -1 && dont_buy == -1)
        return dp[index][mask] = -1;
    if (buy == -1)
        return dp[index][mask] = dont_buy;
    if (dont_buy == -1)
        return dp[index][mask] = buy;
    return dp[index][mask] = min(buy, dont_buy);
}

int main()
{
    int n;
    cin >> n;

    vector<pair<int, string>> juices(n);
    for (auto &juice : juices)
    {
        cin >> juice.first >> juice.second;
    }

    // dp[index][vitamin mask]
    vector<vector<int>> dp(n + 1, vector<int>(8, -2));
    cout << solve(juices, dp, 0, 0) << endl;

    return 0;
}
