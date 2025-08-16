#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, l;
    cin >> n >> m >> l;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<vector<long long>> costs(l, vector<long long>(m, 0));

    for (int i = 0; i < l; ++i) {
        vector<int> counts(m, 0);
        long long group_size = 0;

        for (int j = i; j < n; j += l) {
            counts[a[j]]++;
            group_size++;
        }

        if (group_size == 0) {
            continue;
        }

        long long cost_at_zero = 0;
        for (int v = 1; v < m; ++v) {
            cost_at_zero += (long long)counts[v] * (m - v);
        }
        costs[i][0] = cost_at_zero;

        for (int target_x = 1; target_x < m; ++target_x) {
            costs[i][target_x] = costs[i][target_x - 1] + group_size - (long long)m * counts[target_x];
        }
    }

    vector<vector<long long>> dp(2, vector<long long>(m, INF));

    dp[0] = costs[0];

    for (int i = 1; i < l; ++i) {
        int curr = i % 2;
        int prev = (i - 1) % 2;
        fill(dp[curr].begin(), dp[curr].end(), INF);

        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < m; ++k) {
                int prev_sum = (j - k + m) % m;
                if (dp[prev][prev_sum] != INF) {
                    dp[curr][j] = min(dp[curr][j], dp[prev][prev_sum] + costs[i][k]);
                }
            }
        }
    }

    long long final_answer = dp[(l - 1) % 2][0];

    if (final_answer == 0) {
        cout << "O" << endl;
    } else {
        cout << final_answer << endl;
    }

    return 0;
}