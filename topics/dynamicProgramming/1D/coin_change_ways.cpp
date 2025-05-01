#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, target;
    cin >> n >> target;
    vector<int> arr(n);
    for (int &val: arr) {
        cin >> val;
    }

    // we are given coin denominations in arr and a target amount
    // we can use each coin any number of times
    // we want to count how many different combinations of coins make up the target
    // combination means order doesn't matter, so [1,2] and [2,1] are counted as the same

    vector<int> dp(target + 1, 0);
    dp[0] = 1; // there's exactly 1 way to make amount 0 — use no coins at all

    // loop over each coin first — this fixes the order in which coins are considered
    for (const int coin: arr) {
        // for the current coin, update all amounts it can contribute to
        for (int amount = coin; amount <= target; amount++) {
            // add the number of ways to make (amount - coin) to dp[amount]
            // because for each way to make (amount - coin), we can add one coin to make 'amount'
            dp[amount] += dp[amount - coin];

            // for example, if coin = 2 and amount = 5, we add dp[3] to dp[5]
            // this means: take all the ways to make 3, and add a 2 at the end to make 5

            // the key idea: since we're processing coins in order,
            // we only build combinations using current and previously seen coins
            // so [1,2] and [2,1] are not both counted — only one path gets formed
            // we never count the same set of coins in a different order
        }
    }

    // print the total number of unique combinations to make the target amount
    cout << dp[target] << endl;
}
