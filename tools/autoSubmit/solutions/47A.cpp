#include <bits/stdc++.h>

int main() {
    // Optimize C++ standard streams for competitive programming.
    // Unties cin from cout and disables synchronization with C's stdio.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the input integer n

    bool is_triangular = false;
    int k = 1; // k represents the side length of the triangle (or the 'index' of the triangular number)

    // Iterate to generate triangular numbers T(k) = k * (k + 1) / 2
    // and check if n matches any of them.
    // We can stop once the generated triangular number exceeds n,
    // because triangular numbers are strictly increasing.
    while (true) {
        // Calculate the k-th triangular number.
        // Use long long for intermediate product k * (k + 1) to prevent potential overflow
        // before division, although for n <= 500, int would suffice here.
        long long current_triangular = (long long)k * (k + 1) / 2;

        if (current_triangular == n) {
            // If n matches a triangular number, set the flag and break.
            is_triangular = true;
            break;
        }

        if (current_triangular > n) {
            // If the current triangular number exceeds n,
            // n cannot be a triangular number as all subsequent ones will be even larger.
            break;
        }

        k++; // Move to the next potential triangular number
    }

    // Output the result based on the flag
    if (is_triangular) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0; // Indicate successful execution
}