#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::string a, b;
    std::cin >> a >> b;

    std::vector<ll> ca(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        ca[i + 1] = ca[i] + (a[i] - '0');
    }
    std::vector<ll> cb(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        cb[i + 1] = cb[i] + (b[i] - '0');
    }
    std::map<ll, std::vector<int>> groups;
    for (int y = 1; y <= n; ++y) {
        ll d_y = 2 * cb[y] - y;
        groups[d_y].push_back(y);
    }

    std::vector<ll> sorted_keys;
    sorted_keys.reserve(groups.size());
    for (auto const &[key, val] : groups) {
        sorted_keys.push_back(key);
    }
    int num_keys = sorted_keys.size();

    std::vector<ll> prefix_count(num_keys + 1, 0);
    std::vector<ll> prefix_sum_cb(num_keys + 1, 0);
    std::vector<ll> prefix_sum_y(num_keys + 1, 0);

    for (int i = 0; i < num_keys; ++i) {
        ll key = sorted_keys[i];
        ll current_sum_cb = 0;
        ll current_sum_y = 0;
        for (int y : groups[key]) {
            current_sum_cb += cb[y];
            current_sum_y += y;
        }
        prefix_count[i + 1] = prefix_count[i] + groups[key].size();
        prefix_sum_cb[i + 1] = prefix_sum_cb[i] + current_sum_cb;
        prefix_sum_y[i + 1] = prefix_sum_y[i] + current_sum_y;
    }

    ll total_y_count = prefix_count[num_keys];
    ll total_cb_sum = prefix_sum_cb[num_keys];
    ll total_y_sum = prefix_sum_y[num_keys];

    ll total_f_sum = 0;

    for (int x = 1; x <= n; ++x) {
        ll A = ca[x];
        ll C = x - ca[x];
        ll K_x = x - 2 * A;

        auto it = std::upper_bound(sorted_keys.begin(), sorted_keys.end(), K_x);
        int m_idx = std::distance(sorted_keys.begin(), it);

        ll count_le = prefix_count[m_idx];
        ll sum_cb_le = prefix_sum_cb[m_idx];
        ll S_le = count_le * A + sum_cb_le;

        ll count_gt = total_y_count - count_le;
        ll sum_cb_gt = total_cb_sum - sum_cb_le;
        ll sum_y_gt = total_y_sum - prefix_sum_y[m_idx];
        ll S_gt = count_gt * C + sum_y_gt - sum_cb_gt;

        total_f_sum += S_le + S_gt;
    }

    std::cout << total_f_sum << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}