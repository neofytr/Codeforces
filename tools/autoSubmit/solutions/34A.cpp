#include <bits/stdc++.h>

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> heights(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> heights[i];
    }

    int min_diff = std::numeric_limits<int>::max(); // Initialize with a very large value
    int ans_idx1 = -1;
    int ans_idx2 = -1;

    // Iterate through adjacent pairs (heights[i], heights[i+1]) for i from 0 to n-2
    // These correspond to 1-based indices (i+1, i+2)
    for (int i = 0; i < n - 1; ++i) {
        int current_diff = std::abs(heights[i] - heights[i+1]);
        if (current_diff < min_diff) {
            min_diff = current_diff;
            ans_idx1 = i + 1; // Store 1-based index
            ans_idx2 = i + 2; // Store 1-based index
        }
    }

    // Check the circular pair (heights[n-1], heights[0])
    // These correspond to 1-based indices 'n' and '1'
    int circular_diff = std::abs(heights[n-1] - heights[0]);
    if (circular_diff < min_diff) {
        // This pair has a strictly smaller difference than any other found so far.
        min_diff = circular_diff; // Update min_diff
        ans_idx1 = n;             // Store 1-based index for the last soldier
        ans_idx2 = 1;             // Store 1-based index for the first soldier
    }

    // Output the 1-based indices of the pair with minimal height difference
    std::cout << ans_idx1 << " " << ans_idx2 << std::endl;

    return 0;
}