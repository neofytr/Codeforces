#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: basketball
// URL: https://codeforces.com/problemset/problem/1195/C
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> first(n), second(n);
    for (int &val : first)
        cin >> val;
    for (int &val : second)
        cin >> val;

    // 2 * n students have come
    // they are lined up into two rows of the same size (n)
    // students are numbered 0 to n-1 from left to right in each row

    // we want to choose a team to play basketball
    // we will choose players from left to right, and the index of each chosen player (excluding the first one taken)
    // will be strictly greater than the index of the previously chosen player
    // no two consecutive students should belong to the same row

    // the first student can be chosen among all 2n students and a team can consist of any number of students
    // we want to maximize the total height of the players in the team

    // dp[r][k] is the maximum total height possible when we choose in the index range [0, r]
    // with the last player chosen from row k
    // k = 3 means not chosen
    vector<vector<int>> dp(n, vector<int>(3));
    dp[0][0] = first[0];
    dp[0][1] = second[0];
    dp[0][2] = 0;

    for (int r = 1; r < n; r++) {
        dp[r][0] = max(dp[r - 1][1], dp[r - 1][2]) + first[r];
        dp[r][1] = max(dp[r - 1][0], dp[r - 1][2]) + second[r];
        dp[r][2] = max(dp[r - 1][0], max(dp[r - 1][1], dp[r - 1][2]));
    }

    cout << max(dp[n - 1][0], dp[n - 1][1]) << endl;
    return 0;
}