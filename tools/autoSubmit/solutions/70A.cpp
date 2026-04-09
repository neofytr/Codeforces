#include <bits/stdc++.h>

long long power(long long base, long long exp) {
    long long res = 1;
    long long MOD = 1000003; // The modulus is 10^6 + 3
    base %= MOD; // Ensure base is within the modulo range
    while (exp > 0) {
        if (exp % 2 == 1) { // If exp is odd, multiply res by base
            res = (res * base) % MOD;
        }
        base = (base * base) % MOD; // Square the base
        exp /= 2; // Halve the exponent
    }
    return res;
}

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    if (n == 0) {
        // For n=0, the box is 2^0 x 2^0 = 1x1.
        // There are no cookies of size 1, so the 1x1 cell remains empty.
        std::cout << 1 << std::endl;
    } else {
        // Based on the example (n=3 output 9) and the base cases (n=0 output 1, n=1 analysis output 1),
        // the recurrence relation for the number of empty cells f(n) appears to be:
        // f(0) = 1
        // f(1) = 1 (calculated: 2x2 box, place 2x2 cookie (upper triangle), 3 cells filled, 1 empty (lower-left))
        // f(2) = 3 * f(1) = 3
        // f(3) = 3 * f(2) = 9 (matches example)
        // In general, for n >= 1, f(n) = 3^(n-1).
        // This suggests a recursive decomposition where each step generates three smaller subproblems that contribute to the empty cell count.
        std::cout << power(3, n - 1) << std::endl;
    }

    return 0;
}