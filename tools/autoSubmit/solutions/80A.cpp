#include <bits/stdc++.h>

// Function to check if a number is prime
bool is_prime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true; // 2 and 3 are prime
    if (num % 2 == 0 || num % 3 == 0) return false; // multiples of 2 or 3

    // Check for primes of the form 6k +/- 1
    for (int i = 5; i * i <= num; i = i + 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    // Find the next prime number after n
    int next_prime_after_n = n + 1;
    while (true) {
        if (is_prime(next_prime_after_n)) {
            break; // Found the smallest prime greater than n
        }
        next_prime_after_n++;
    }

    // Check if m is equal to the next prime after n
    if (next_prime_after_n == m) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}