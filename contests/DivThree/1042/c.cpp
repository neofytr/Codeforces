#include <algorithm>
#include <iostream>
#include <map>

#define int long long

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::map<int, int> s_counts;
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;

        int remainder = val % k;
        int canonical_rep = std::min(remainder, k - remainder);
        s_counts[canonical_rep]++;
    }
    std::map<int, int> t_counts;
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;
        int remainder = val % k;
        int canonical_rep = std::min(remainder, k - remainder);
        t_counts[canonical_rep]++;
    }

    if (s_counts == t_counts) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int32_t main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
