#include <bits/stdc++.h>

int main() {
    // Enable fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n; // Number of soldiers
    int d; // Maximum allowed height difference
    std::cin >> n >> d;

    // Read the heights of all soldiers
    std::vector<int> heights(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> heights[i];
    }

    long long count = 0; // Counter for valid reconnaissance units.
                         // Using long long for safety, although int would suffice for N=1000.

    // Iterate through all possible pairs of distinct soldiers
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // A unit must consist of exactly two *distinct* soldiers.
            if (i == j) {
                continue;
            }

            // Check if their height difference does not exceed d
            if (std::abs(heights[i] - heights[j]) <= d) {
                count++;
            }
        }
    }

    // Output the total number of ways
    std::cout << count << std::endl;

    return 0;
}