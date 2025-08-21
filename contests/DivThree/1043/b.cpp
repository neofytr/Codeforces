#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

void solve() {
    long long n;
    std::cin >> n;

    std::vector<long long> solutions;
    long long power_of_10 = 10;

    while (true) {
        long long divisor = power_of_10 + 1;

        if (divisor > n) {
            break;
        }

        if (n % divisor == 0) {
            solutions.push_back(n / divisor);
        }

        if (power_of_10 > LLONG_MAX / 10) {
            break;
        }
        power_of_10 *= 10;
    }

    std::sort(solutions.begin(), solutions.end());

    if (!solutions.size()) {
        std::cout << 0 << "\n";
        return;
    }
    std::cout << solutions.size() << std::endl;
    for (long long x_val : solutions) {
        std::cout << x_val << " ";
    }
    std::cout << "\n";
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