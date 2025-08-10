#include <algorithm>
#include <iostream>
#include <vector>

void add_to_basis(std::vector<long long> &basis, long long mask) {
    for (long long &b_vec : basis) {
        mask = std::min(mask, mask ^ b_vec);
    }
    if (mask > 0) {
        basis.push_back(mask);
        std::sort(basis.rbegin(), basis.rend());
    }
}

bool is_in_span(const std::vector<long long> &basis, long long mask) {
    for (long long b_vec : basis) {
        mask = std::min(mask, mask ^ b_vec);
    }
    return mask == 0;
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<long long> a(n), b(n);
    for (int i = 0; i < n; ++i)
        std::cin >> a[i];
    for (int i = 0; i < n; ++i)
        std::cin >> b[i];

    std::vector<long long> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = a[i] ^ b[i];
    }

    std::vector<long long> basis;

    for (int i = n - 1; i >= 0; --i) {
        if (!is_in_span(basis, c[i])) {
            std::cout << "NO\n";
            return;
        }
        add_to_basis(basis, a[i]);
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