#include <bits/stdc++.h>

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;

    // Use a vector to store the minimum viability for each row.
    // Initialize with a value larger than the maximum possible viability (10^6).
    // This ensures that the first viability encountered for a row will correctly
    // become the minimum. Using `m + 1` size for 1-indexed row numbers.
    std::vector<int> min_viability_per_row(m + 1, 1000001); // Max c is 10^6

    // Read tooth data and update minimum viability for each row
    for (int i = 0; i < n; ++i) {
        int r, c;
        std::cin >> r >> c;
        min_viability_per_row[r] = std::min(min_viability_per_row[r], c);
    }

    // Calculate the total number of crucians Valerie can eat based on her teeth's capacity.
    // Each row's capacity is limited by its weakest tooth. Since eating a crucian
    // uses one entire row, the capacities of different rows are independent and additive.
    // Use long long for sum to prevent potential overflow, as m * max_c could exceed INT_MAX.
    long long total_teeth_capacity = 0;
    for (int i = 1; i <= m; ++i) {
        total_teeth_capacity += min_viability_per_row[i];
    }

    // The final answer is the minimum of two values:
    // 1. The total crucians Valerie's teeth can safely handle (total_teeth_capacity).
    // 2. The total crucians available in her portion (k).
    long long result = std::min((long long)k, total_teeth_capacity);
    std::cout << result << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    solve();

    return 0;
}