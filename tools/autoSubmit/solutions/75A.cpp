#include <bits/stdc++.h>

// Function to remove all zeros from an integer.
// For example:
// remove_zeros(101) returns 11
// remove_zeros(203) returns 23
// remove_zeros(105) returns 15
long long remove_zeros(int n) {
    long long res = 0;           // Stores the number with zeros removed
    long long power_of_10 = 1;   // Represents the place value for the current non-zero digit

    // Iterate through the digits of n from right to left (least significant to most significant)
    while (n > 0) {
        int digit = n % 10; // Get the last digit
        if (digit != 0) {
            // If the digit is not zero, add it to the result at the correct place value
            res += digit * power_of_10;
            // Increase the place value for the next non-zero digit
            power_of_10 *= 10;
        }
        // Move to the next digit (by removing the last digit)
        n /= 10;
    }
    return res;
}

// Function for fast input/output operations
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

int main() {
    fast_io(); // Enable fast I/O

    int a, b;
    // Read the two integers a and b
    std::cin >> a >> b;

    // Calculate c as the sum of a and b
    int c = a + b;

    // Remove zeros from a, b, and c to get their prime versions
    long long a_prime = remove_zeros(a);
    long long b_prime = remove_zeros(b);
    long long c_prime = remove_zeros(c);

    // Check if the equation a_prime + b_prime == c_prime holds true
    if (a_prime + b_prime == c_prime) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}