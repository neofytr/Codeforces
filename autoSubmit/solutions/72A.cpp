#include <iostream>
#include <vector>
#include <numeric>
#include <set>
#include <algorithm> // For std::fill

// Maximum value for n is 10000. We need primes up to this value.
const int N_MAX = 10000;
bool is_prime[N_MAX + 1]; // is_prime[i] is true if i is a prime number

// Sieve of Eratosthenes to precompute prime numbers up to N_MAX
void sieve() {
    // Initialize all numbers as potentially prime
    std::fill(is_prime, is_prime + N_MAX + 1, true);
    is_prime[0] = is_prime[1] = false; // 0 and 1 are not prime

    // Iterate from 2 up to sqrt(N_MAX)
    for (int p = 2; p * p <= N_MAX; ++p) {
        // If p is prime, mark all its multiples as not prime
        if (is_prime[p]) {
            for (int i = p * p; i <= N_MAX; i += p)
                is_prime[i] = false;
        }
    }
}

// Function to set up fast I/O
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

int main() {
    fast_io(); // Enable fast I/O
    sieve();   // Precompute primes

    int n;
    std::cin >> n; // Read the input integer n

    std::vector<int> solution_elements; // Stores the elements a_i of the sum
    std::set<int> used_numbers;         // Keeps track of numbers already used to ensure distinctness
    int current_n = n;                  // The remaining sum we need to form
    bool possible = true;               // Flag to indicate if n is rich

    // Greedy approach to find the lexicographically latest sequence
    // At each step, we pick the largest possible valid number (prime or 1, not used yet)
    // that is less than or equal to the current remaining sum.
    while (current_n > 0) {
        int chosen_val = -1; // Stores the number chosen for the current step

        // Iterate downwards from current_n to 1
        // We want the largest possible a_i, so we start checking from current_n
        for (int i = current_n; i >= 1; --i) {
            // Check if 'i' is a valid number:
            // 1. It must be prime or 1.
            // 2. It must not have been used in the sum before.
            if ((is_prime[i] || i == 1) && used_numbers.find(i) == used_numbers.end()) {
                chosen_val = i; // Found the largest valid number for this step
                break;          // Take it and move to the next iteration of the while loop
            }
        }

        if (chosen_val != -1) {
            // If a valid number was found, add it to our solution
            solution_elements.push_back(chosen_val);
            used_numbers.insert(chosen_val); // Mark it as used
            current_n -= chosen_val;         // Reduce the remaining sum
        } else {
            // If no valid number could be found for the current_n > 0,
            // then n cannot be formed by the rules, meaning n is not rich.
            possible = false;
            break; // Exit the loop
        }
    }

    // Output the result
    if (possible) {
        // Print the sequence in the format a1+a2+...+am=n
        for (size_t i = 0; i < solution_elements.size(); ++i) {
            std::cout << solution_elements[i];
            if (i < solution_elements.size() - 1) {
                std::cout << "+"; // Add '+' between numbers
            }
        }
        std::cout << "=" << n << std::endl;
    } else {
        // If n is not rich, print 0
        std::cout << 0 << std::endl;
    }

    return 0;
}