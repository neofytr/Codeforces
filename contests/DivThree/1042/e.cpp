#include <iostream>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<long long> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    if (a[n - 1] != b[n - 1]) {
        std::cout << "NO\n";
        return;
    }

    for (int i = n - 2; i >= 0; --i) {
        long long no_op_val = a[i];

        long long early_op_val = a[i] ^ a[i + 1];

        long long late_op_val = a[i] ^ b[i + 1];

        if (b[i] != no_op_val && b[i] != early_op_val && b[i] != late_op_val) {
            std::cout << "NO\n";
            return;
        }
    }

    std::cout << "YES\n";
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