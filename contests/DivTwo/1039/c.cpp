#include <iostream>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<long long> b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    if (n == 1) {
        std::cout << "YES\n";
        return;
    }

    long long surplus = 0;
    for (int i = n - 1; i > 0; --i) {
        long long current_b = b[i];
        long long previous_b = b[i - 1];

        if (previous_b + surplus < current_b) {
            std::cout << "NO\n";
            return;
        }
        surplus = previous_b + surplus - current_b;
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