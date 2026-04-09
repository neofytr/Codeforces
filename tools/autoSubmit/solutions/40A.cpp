#include <bits/stdc++.h>

int main() {
    // Enable fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long x, y;
    std::cin >> x >> y;

    // Calculate squared distance from origin (0,0)
    // Using long long for d_sq to be safe, though int would suffice for given constraints.
    long long d_sq = x * x + y * y;

    // Calculate actual distance
    double d = std::sqrt(static_cast<double>(d_sq));

    // Rule 1: All points with integral distance from origin are black.
    // Check if 'd' is an integer. Using std::round and comparing squared values
    // is more robust against floating point inaccuracies than direct comparison or epsilon check.
    long long rounded_d = static_cast<long long>(std::round(d));
    
    if (rounded_d * rounded_d == d_sq) {
        std::cout << "black\n";
    } else {
        // Rule 2: If distance is not an integer, determine color based on floor(d) and x-coordinate.
        long long k = static_cast<long long>(std::floor(d)); // k = floor(d)

        // The pattern observed from examples:
        // Combined parity: (k + (x > 0 ? 1 : 0)) % 2
        // where 0 maps to white, 1 maps to black.

        bool combined_parity_is_odd; // True if combined_parity is 1 (black), False if 0 (white)

        if (x > 0) {
            // If x is positive, the base parity of k is inverted.
            // If k is even, (k + 1) % 2 = 1 (black)
            // If k is odd, (k + 1) % 2 = 0 (white)
            combined_parity_is_odd = (k % 2 == 0);
        } else {
            // If x is non-positive (x <= 0), the base parity of k is used directly.
            // If k is even, (k + 0) % 2 = 0 (white)
            // If k is odd, (k + 0) % 2 = 1 (black)
            combined_parity_is_odd = (k % 2 != 0);
        }

        if (combined_parity_is_odd) {
            std::cout << "black\n";
        } else {
            std::cout << "white\n";
        }
    }

    return 0;
}