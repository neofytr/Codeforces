#include <bits/stdc++.h>

// Function to implement Sieve of Eratosthenes and find primes up to N
std::vector<bool> sieve(int N) {
    std::vector<bool> is_prime(N + 1, true);
    if (N >= 0) is_prime[0] = false;
    if (N >= 1) is_prime[1] = false;
    for (int p = 2; p * p <= N; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= N; i += p)
                is_prime[i] = false;
        }
    }
    return is_prime;
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    std::cin >> n >> k;

    // Sieve to find all primes up to n
    std::vector<bool> is_prime = sieve(n);

    // Collect all prime numbers up to n
    std::vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    int noldbach_count = 0;

    // Iterate through neighboring primes to check Noldbach condition
    // We need at least two primes to form a pair.
    // The loop iterates from i=0 to primes.size()-2 to get primes[i] and primes[i+1]
    for (size_t i = 0; i + 1 < primes.size(); ++i) {
        int p1 = primes[i];
        int p2 = primes[i+1];
        int sum = p1 + p2 + 1;

        // Check if the sum is within the range [2, n] and if it is itself a prime number
        if (sum <= n && is_prime[sum]) {
            noldbach_count++;
        }
        
        // Optimization: if the current sum exceeds n, any further sums will also exceed n
        // because the prime_list is sorted in ascending order.
        if (sum > n) {
            break; 
        }
    }

    // Output the result
    if (noldbach_count >= k) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}