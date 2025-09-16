#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> primeFactorization(int n) {
    vector<int> factors;
    if (n <= 1)
        return factors;
    // 1. At most, one prime factor of n can be > root(n), and its exponent in the prime factorization of
    // n will be one
    // 2. All other prime factors are <= root(n)
    for (int r = 2; r * r <= n; r++)
        while (!(n % r))
            factors.push_back(r), n /= r;
    // During any iteration r = k, n % k will be true iff k is a prime,
    // because if k is a composite number, its prime factorization will have primes < k
    // and n has been stripped off of all the prime factors < k it initially had (before iteration r = 2), at the start of iteration r = k
    if (n > 1)
        factors.push_back(n); // getting the > root(n) prime factor
}