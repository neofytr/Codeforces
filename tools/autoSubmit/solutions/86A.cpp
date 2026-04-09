#include <iostream>
#include <string>
#include <algorithm> // For std::max
#include <vector>    // Not strictly needed but common for competitive programming

// Function to set up fast I/O
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

// Function to calculate psi(n), the reflection of n
long long calculate_psi(long long n) {
    // Convert n to a string to process its digits
    std::string s = std::to_string(n);
    std::string psi_s = "";

    // Replace each digit 'a' with '9 - a'
    for (char c : s) {
        psi_s += std::to_string(9 - (c - '0'));
    }

    // Remove leading zeros from the reflected string.
    // For example: psi(91) -> "08". After removing leading zeros, it becomes "8".
    // Example: psi(9) -> "0". After removing leading zeros, it means the number is 0.
    size_t first_digit_pos = psi_s.find_first_not_of('0');
    if (std::string::npos == first_digit_pos) {
        // If find_first_not_of('0') returns npos, it means all digits were '0'.
        // This occurs for numbers like psi(9), psi(99), etc.
        // In such cases, the reflection is 0.
        return 0;
    }

    // Convert the (possibly trimmed) string back to a long long
    return std::stoll(psi_s.substr(first_digit_pos));
}

int main() {
    fast_io();

    long long l, r;
    std::cin >> l >> r;

    long long max_weight = 0;

    // 1. Check the weight of the boundary numbers l and r.
    // These are often good candidates for maximums in range problems.
    max_weight = std::max(max_weight, l * calculate_psi(l));
    if (l != r) { // Avoid duplicate calculation if l and r are the same
        max_weight = std::max(max_weight, r * calculate_psi(r));
    }
    
    // 2. Check numbers around 5 * 10^p for various powers of 10.
    // The product n * psi(n) tends to be maximized when n is roughly in the middle
    // of its digit-count range, e.g., for k-digit numbers, around 10^k / 2.
    // These critical points are typically numbers like 49...9 and 50...0.
    // The loop iterates for p from 0 up to 8, covering numbers with up to 9 digits.
    // (5*10^0 = 5, ..., 5*10^8 = 500,000,000)
    long long power_of_10 = 1;
    for (int p = 0; p <= 8; ++p) { 
        long long mid = 5 * power_of_10;

        // Candidate 1: mid - 1 (e.g., 4, 49, 499, ..., 499,999,999)
        long long candidate1 = mid - 1;
        // Check if candidate1 is within the given range [l, r]
        if (candidate1 >= l && candidate1 <= r) {
            max_weight = std::max(max_weight, candidate1 * calculate_psi(candidate1));
        }
        
        // Candidate 2: mid (e.g., 5, 50, 500, ..., 500,000,000)
        long long candidate2 = mid;
        // Check if candidate2 is within the given range [l, r]
        if (candidate2 >= l && candidate2 <= r) {
            max_weight = std::max(max_weight, candidate2 * calculate_psi(candidate2));
        }

        // Prepare for the next power of 10.
        // `power_of_10` will go up to 10^9 (after p=8 iteration).
        // Since r <= 10^9, 5 * 10^9 would be too large for n.
        // The current loop covers relevant candidates up to 5 * 10^8.
        power_of_10 *= 10;
    }

    // Output the maximum weight found.
    std::cout << max_weight << std::endl;

    return 0;
}