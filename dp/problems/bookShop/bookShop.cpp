#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N (1001)
#define MAX_X (int)(1e5 + 1)

// Problem: bookShop
// URL: https://cses.fi/problemset/task/1158
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> price(n);
    vector<int> pages(n);

    for (int i = 0; i < n; i++)
        cin >> price[i];
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    // we are in a bookshop that sells n different books
    // we know the price and number of pages of each book

    // we have decided that the total price of your purchases will be at most x
    // what is the maximum number of pages we can buy?

    // dp[r][k] is the maximum number of pages we can buy using the books [0, r] and atmost k money

    vector<int> prev(x + 1, 0);
    vector<int> curr(x + 1, 0);

    for (int k = price[0]; k <= x; k++)
        prev[k] = pages[0];
    for (int r = 1; r < n; r++) {
        for (int k = price[r]; k <= x; k++)
            curr[k] = max(prev[k - price[r]] + pages[r], prev[k]); // should we even get the current book or not?
        for (int k = 0; k < price[r]; k++)
            curr[k] = prev[k];
        prev = curr;
    }

    cout << curr[x] << endl;
    return 0;
}