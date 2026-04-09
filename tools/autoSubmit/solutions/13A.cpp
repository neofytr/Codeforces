#include <bits/stdc++.h> // Includes iostream, numeric, etc. for convenience

// Function to calculate GCD using Euclidean algorithm
// This is typically available as std::gcd in <numeric> since C++17
// but implementing it ensures compatibility and self-containment.
long long calculate_gcd(long long a, long long b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C stdio.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int A;
    std::cin >> A;

    long long total_sum_of_digits = 0;
    // The problem asks to calculate the sum of digits for A in all bases
    // from 2 to A-1.
    for (int b = 2; b < A; ++b) {
        int current_A = A;
        long long sum_digits_in_base_b = 0;
        // Calculate sum of digits of A in base b
        // This is done by repeatedly taking modulo b to get the last digit
        // and then dividing by b to remove it.
        while (current_A > 0) {
            sum_digits_in_base_b += current_A % b;
            current_A /= b;
        }
        total_sum_of_digits += sum_digits_in_base_b;
    }

    // The number of bases considered is A-1 - 2 + 1 = A-2.
    // For A=3, bases are only b=2. Count = 1. (3-2=1)
    // For A=5, bases are b=2,3,4. Count = 3. (5-2=3)
    long long num_bases = A - 2;

    // To express the average as an irreducible fraction X/Y,
    // we need to divide both the total sum (numerator) and the number of bases (denominator)
    // by their greatest common divisor (GCD).
    long long common_divisor = calculate_gcd(total_sum_of_digits, num_bases);
    
    long long numerator = total_sum_of_digits / common_divisor;
    long long denominator = num_bases / common_divisor;

    // Output the result in the specified X/Y format.
    std::cout << numerator << "/" << denominator << std::endl;

    return 0;
}