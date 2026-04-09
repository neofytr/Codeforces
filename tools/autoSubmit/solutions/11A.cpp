#include <bits/stdc++.h>

int main() {
    // Enable fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    long long d; // d can be up to 10^6. Using long long to ensure intermediate products (num_adds * d) do not overflow,
                 // even though the final b[i] value will fit in an int.
    std::cin >> n >> d;

    std::vector<int> b(n); // Vector elements b[i] can grow up to ~2 * 10^6, which fits within an int.
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    long long total_moves = 0; // Total moves can be up to (n-1) * (max_b_val / min_d) approx.
                               // For n=2000, b_i=10^6, d=1, this is ~2000 * 10^6 = 2 * 10^9.
                               // This value fits in a 32-bit signed int, but barely. Using long long is safer.

    // Iterate through the sequence starting from the second element (b_1)
    // and compare it with the previous element (b_0).
    for (int i = 1; i < n; ++i) {
        // If the current element b[i] is not strictly greater than the previous b[i-1],
        // we need to increase b[i].
        if (b[i] <= b[i-1]) {
            // The minimum target value for b[i] is b[i-1] + 1.
            // Calculate how much b[i] needs to be increased by to reach this target.
            // We use long long for calculation to prevent overflow if b[i-1] is large.
            long long diff_needed = (long long)b[i-1] + 1 - b[i];

            // Calculate the number of times 'd' needs to be added.
            // This is equivalent to ceil(diff_needed / d) using integer arithmetic.
            // Formula for ceil(a/b) with positive integers a, b is (a + b - 1) / b.
            long long num_adds = (diff_needed + d - 1) / d;

            // Increment b[i] by num_adds * d.
            // The resulting value of b[i] will still fit in an int.
            b[i] += num_adds * d;
            
            // Add the number of additions to the total moves count.
            total_moves += num_adds;
        }
    }

    // Output the minimal number of moves.
    std::cout << total_moves << std::endl;

    return 0;
}