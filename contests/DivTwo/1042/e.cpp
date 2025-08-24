#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

const long long INF = 4e18; // A large enough value for infinity

void solve() {
    int num_mobs;
    cin >> num_mobs;
    vector<long long> healths(num_mobs);
    for (int i = 0; i < num_mobs; ++i) {
        cin >> healths[i];
    }

    vector<long long> dp_values(num_mobs + 1, INF);
    dp_values[0] = 0;

    vector<long long> prefix_health_sum(num_mobs + 1, 0);
    for (int i = 0; i < num_mobs; ++i) {
        prefix_health_sum[i + 1] = prefix_health_sum[i] + healths[i];
    }

    long long min_tracker = INF;

    for (int i = 1; i <= num_mobs; ++i) {
        // This corresponds to min_{0 <= j < i} (dp[j] - H[j] + j)
        long long prev_j = i - 1;
        long long val_to_track = dp_values[prev_j] - prefix_health_sum[prev_j] + prev_j;
        min_tracker = min(min_tracker, val_to_track);

        // Baseline strategy cost
        dp_values[i] = prefix_health_sum[i] - i + 1 + min_tracker;

        // Check for a better strategy by causing a chain reaction
        // This is particularly effective if h[i-1] is 1.
        // We consider an attack on mob i-2.
        if (i >= 2 && healths[i-1] == 1) {
            long long alternative_cost;
            if (i == 2) {
                // Stack is [h0, h1=1]. Attack h0. Mob h1 falls by 1 and dies. Cost is h0.
                alternative_cost = healths[0];
            } else {
                // Mobs 1..i-3 are cleared (cost dp[i-2]). We have stack i-2, i-1, i.
                // We clear stack [h_{i-2}, h_{i-1}=1]. Attack h_{i-2}. Cost h_{i-2}. Mob h_{i-1} dies.
                alternative_cost = dp_values[i-2] + healths[i-2];
            }
            dp_values[i] = min(dp_values[i], alternative_cost);
        }
    }

    cout << dp_values[num_mobs] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test_cases;
    cin >> test_cases;
    while (test_cases--) {
        solve();
    }
    return 0;
}