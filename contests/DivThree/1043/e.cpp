#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<long long> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());

    vector<long long> pref_a(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pref_a[i + 1] = pref_a[i] + a[i];
    }

    vector<long long> pref_b(m + 1, 0);
    for (int i = 0; i < m; ++i) {
        pref_b[i + 1] = pref_b[i] + b[i];
    }

    vector<int> count_a_in_top_k(n + m + 1, 0);
    int ptr_a = 0;
    int ptr_b = 0;
    for (int i = 1; i <= n + m; ++i) {
        count_a_in_top_k[i] = count_a_in_top_k[i - 1];
        if (ptr_a < n && (ptr_b >= m || a[ptr_a] >= b[ptr_b])) {
            count_a_in_top_k[i]++;
            ptr_a++;
        } else {
            ptr_b++;
        }
    }

    for (int k = 0; k < q; ++k) {
        int x, y, z;
        cin >> x >> y >> z;

        int k_opt = count_a_in_top_k[z];

        int k_low = max(0, z - y);
        int k_high = min(x, z);

        int k_final = max(k_low, min(k_opt, k_high));

        long long result_sum = pref_a[k_final] + pref_b[z - k_final];
        cout << result_sum << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}