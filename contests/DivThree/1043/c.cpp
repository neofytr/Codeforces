#include <iostream>

void solve() {
    long long n;
    std::cin >> n;

    long long total_cost = 0;
    long long power_of_3 = 1;

    for (int x = 0; n > 0; ++x) {
        int digit = n % 3;
        if (digit != 0) {
            long long cost_per_deal = power_of_3 * 3 + (long long)x * (power_of_3 / 3);
            total_cost += (long long)digit * cost_per_deal;
        }
        n /= 3;
        if (n > 0) {
            power_of_3 *= 3;
        }
    }
    std::cout << total_cost << std::endl;
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
