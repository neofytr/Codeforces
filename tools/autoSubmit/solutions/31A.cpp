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

    // Iterate through all possible combinations of three distinct indices i, j, k
    // The problem asks for a_i = a_j + a_k, where i, j, k are distinct.
    // We use 0-indexed arrays internally and convert to 1-indexed for output.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Ensure i and j are distinct
            if (i == j) {
                continue;
            }
            for (int k = 0; k < n; ++k) {
                // Ensure k is distinct from i and j
                if (k == i || k == j) {
                    continue;
                }

                // Check if the condition a[i] = a[j] + a[k] holds
                if (a[i] == a[j] + a[k]) {
                    // Found a valid triple. Print 1-indexed indices and terminate.
                    std::cout << i + 1 << " " << j + 1 << " " << k + 1 << std::endl;
                    return 0; // Exit successfully
                }
            }
        }
    }

    // If the loops complete without finding any solution, output -1.
    std::cout << -1 << std::endl;

    return 0; // Program finished
}