#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int n;
    int y;
    cin >> n >> y;

    int max_c = 0;
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        max_c = max(max_c, c[i]);
    }

    const int LIMIT = max_c + 2;
    vector<int> counts(LIMIT, 0);
    for (int price : c) {
        counts[price]++;
    }

    vector<int> prefix_counts(LIMIT, 0);
    for (int i = 1; i < LIMIT; ++i) {
        prefix_counts[i] = prefix_counts[i - 1] + counts[i];
    }

    int max_income = -5e18;

    for (int x = 2; x < LIMIT; ++x) {
        int current_rev = 0;
        int tags_to_print = 0;

        for (int p = 1;; ++p) {
            int v_min = (p - 1) * x + 1;
            if (v_min > max_c) {
                break;
            }
            int v_max = p * x;
            int num_items_for_p = prefix_counts[min((int)max_c, v_max)] - prefix_counts[v_min - 1];
            if (num_items_for_p > 0) {
                current_rev += num_items_for_p * p;
                int old_tags_available = (p < LIMIT) ? counts[p] : 0;
                if (num_items_for_p > old_tags_available) {
                    tags_to_print += num_items_for_p - old_tags_available;
                }
            }
        }
        max_income = max(max_income, current_rev - y * tags_to_print);
    }
    int tags_baseline = 0;
    if (n > counts[1]) {
        tags_baseline = n - counts[1];
    }
    max_income = max(max_income, (int)n - y * tags_baseline);
    cout << max_income << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}