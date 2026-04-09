#include <bits/stdc++.h>

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    long long total_magical_subarrays = 0;
    int i = 0; // Current index for processing blocks

    while (i < n) {
        long long current_block_length = 0;
        int j = i; // Iterator for finding the end of the current block

        // Count consecutive identical elements starting from a[i]
        while (j < n && a[j] == a[i]) {
            current_block_length++;
            j++;
        }

        // If a block has 'k' identical elements, it can form k*(k+1)/2 magical subarrays.
        // For example, if k=3 (e.g., [X,X,X]):
        // Single element subarrays: [X], [X], [X] (3 subarrays)
        // Two element subarrays: [X,X], [X,X] (2 subarrays)
        // Three element subarrays: [X,X,X] (1 subarray)
        // Total = 3 + 2 + 1 = 6. Formula: 3*(3+1)/2 = 6.
        total_magical_subarrays += current_block_length * (current_block_length + 1) / 2;

        // Move 'i' to the beginning of the next distinct block.
        // 'j' is already positioned at the first element *different* from a[i]
        // or at 'n' if a[i] was the last element.
        i = j;
    }

    std::cout << total_magical_subarrays << std::endl;

    return 0;
}