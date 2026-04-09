#include <bits/stdc++.h>

// Function to count distinct prime factors of a number
int countDistinctPrimeFactors(int num) {
    if (num <= 1) {
        return 0; // Numbers less than or equal to 1 have no prime factors
    }

    std::set<int> factors; // Use a set to automatically store only distinct factors
    int temp_num = num;

    // Iterate from 2 up to sqrt(temp_num) to find prime factors
    for (int i = 2; (long long)i * i <= temp_num; ++i) {
        if (temp_num % i == 0) {
            factors.insert(i); // i is a distinct prime factor
            while (temp_num % i == 0) {
                temp_num /= i; // Remove all occurrences of i
            }
        }
    }
    // If temp_num is still greater than 1 after the loop, it means the remaining temp_num is a prime factor itself
    // (This handles cases where the original number is prime, or has a large prime factor)
    if (temp_num > 1) {
        factors.insert(temp_num);
    }
    return factors.size();
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    int almost_prime_count = 0;

    // Iterate through all numbers from 1 to n (inclusive)
    for (int i = 1; i <= n; ++i) {
        if (countDistinctPrimeFactors(i) == 2) {
            almost_prime_count++;
        }
    }

    std::cout << almost_prime_count << std::endl;

    return 0;
}