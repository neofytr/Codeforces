#include <bits/stdc++.h>

// Function to compare two non-negative numbers represented as strings.
// Returns true if n_str <= max_str.
bool is_less_equal(const std::string& n_str, const std::string& max_str) {
    if (n_str.length() < max_str.length()) {
        return true;
    }
    if (n_str.length() > max_str.length()) {
        return false;
    }
    // Lengths are equal, compare lexicographically.
    // std::string's operator<= performs lexicographical comparison.
    return n_str <= max_str;
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string n_str;
    std::cin >> n_str;

    // Maximum positive values for each type, represented as strings.
    // These correspond to the upper bounds for positive 'n'.
    const std::string byte_max_str = "127";
    const std::string short_max_str = "32767";
    const std::string int_max_str = "2147483647";
    const std::string long_max_str = "9223372036854775807";

    // Check types in increasing order of capacity to find the smallest one that fits.
    if (is_less_equal(n_str, byte_max_str)) {
        std::cout << "byte\n";
    } else if (is_less_equal(n_str, short_max_str)) {
        std::cout << "short\n";
    } else if (is_less_equal(n_str, int_max_str)) {
        std::cout << "int\n";
    } else if (is_less_equal(n_str, long_max_str)) {
        std::cout << "long\n";
    } else {
        // If it doesn't fit in 'long', it must require 'BigInteger'.
        std::cout << "BigInteger\n";
    }

    return 0;
}