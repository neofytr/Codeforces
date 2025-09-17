#include <bits/stdc++.h>
using namespace std;

#define int long long

// returns the prime factorization of a number
// O(root(n))
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
    return factors;
}

// prime factorization in O(log(x)) after O(nlog(n)) precomputation
#define MAX (1000000)
void fact() {
    int n;
    cin >> n;
    // p[r] is the smallest prime factor of r for r >= 2
    vector<int> p(MAX + 1, -1);
    for (int r = 2; r <= MAX; r++)
        for (int j = r; j <= MAX; j += r)
            if (p[j] == -1) // the smallest factor (not equal to 1) is a prime factor
                p[j] = r;

    while (n--) {
        int x;
        cin >> x;
        vector<int> primes;
        while (x != 1) {
            const int smallestP = p[x];
            primes.push_back(smallestP);
            x /= smallestP;
        }
        // primes now contains the prime factorization of x
    }
}

void factTwo() {
    int n;
    cin >> n;
    // p[r] is the largest factor of r for r >= 2
    vector<int> p(MAX + 1, -1);
    for (int r = 2; r <= MAX; r++)
        if (p[r] == -1)
            for (int j = r; j <= MAX; j += r)
                p[j] = r;

    while (n--) {
        int x;
        cin >> x;
        vector<int> primes;
        while (x != 1) {
            const int largestP = p[x];
            while (!(x % largestP))
                primes.push_back(x), x /= largestP;
        }
        // primes now contains the prime factorization of x
    }
}