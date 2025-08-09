#include <bits/stdc++.h>
const int MAX_VAL = 1000001;

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    long long q;
    std::cin >> n >> q;

    std::vector<long long> counts(MAX_VAL, 0);
    long long max_a = 0;

    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        if (a < MAX_VAL) {
            counts[a]++;
        } else {
            counts[MAX_VAL - 1]++;
        }
        if (a > max_a) {
            max_a = a;
        }
    }

    std::vector<long long> prefix_sum_counts(MAX_VAL, 0);

    std::vector<long long> prefix_sum_values(MAX_VAL, 0);

    prefix_sum_counts[0] = counts[0];

    for (int i = 1; i < MAX_VAL; ++i) {
        prefix_sum_counts[i] = prefix_sum_counts[i - 1] + counts[i];
        prefix_sum_values[i] = prefix_sum_values[i - 1] + counts[i] * (long long)i;
    }

    for (long long j = 0; j < q; ++j) {
        int b;
        std::cin >> b;

        if (max_a < b) {
            std::cout << -1 << std::endl;
            continue;
        }

        long long max_losing_bags = 0;

        if (b > 0) {
            long long sum_from_small_flavors = (b > 1) ? prefix_sum_values[b - 2] : 0;

            long long count_of_large_flavors = (b > 1) ? (n - prefix_sum_counts[b - 2]) : n;

            long long sum_from_large_flavors = (long long)(b - 1) * count_of_large_flavors;

            max_losing_bags = sum_from_small_flavors + sum_from_large_flavors;
        }

        std::cout << max_losing_bags + 1 << std::endl;
    }

    return 0;
}
