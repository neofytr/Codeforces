#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: threeActivities
// URL: https://codeforces.com/problemset/problem/1914/D
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> ski(n), movie(n), board(n);

        for (int i = 0; i < n; i++)
            cin >> ski[i].first, ski[i].second = i;
        for (int i = 0; i < n; i++)
            cin >> movie[i].first, movie[i].second = i;
        for (int i = 0; i < n; i++)
            cin >> board[i].first, board[i].second = i;

        auto getTop = [&](vector<pair<int, int>> &arr) {
            sort(arr.begin(), arr.end(), greater<>());
            vector<pair<int, int>> top;
            for (int i = 0; i < min(3LL, (int)arr.size()); i++)
                top.push_back(arr[i]);
            return top;
        };

        auto topSki = getTop(ski);
        auto topMovie = getTop(movie);
        auto topBoard = getTop(board);

        int best = 0;
        for (auto [sval, si] : topSki) {
            for (auto [mval, mi] : topMovie) {
                for (auto [bval, bi] : topBoard) {
                    if (si != mi && mi != bi && si != bi) {
                        best = max(best, sval + mval + bval);
                    }
                }
            }
        }
        cout << best << "\n";
    }
}
