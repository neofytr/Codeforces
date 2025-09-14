#include <bits/stdc++.h>
using namespace std;

#define int long long

// runs in O(log(b))
// we always maintain a >= b
int gcd(const int a, const int b) {
    if (a < 0 || b < 0)
        return -1;
    if (!b)
        return a;
    return gcd(b, a % b);
}

int pw(const int a, const int b, const int mod) { // calculates (a^b) % mod
    if (!b)
        return 1;
    const int r = pw(a, b / 2, mod);
    if (b & 1)
        return (((r * r) % mod) * a) % mod;
    return (r * r) % mod;
}

vector<int> smallestFactor(const int b) {
    if (b <= 1)
        return {};
    // smallest[r] will store the smallest prime factor of r for r >= 2
    vector<int> smallest(b + 1, -1);
    for (int r = 2; r <= b; r++)
        for (int j = r; j <= b; j += r)
            if (smallest[j] == -1)
                smallest[j] = r;
    // Proposition -> At the end of execution, for all r in [2, b], smallest[r] is the smallest prime factor of r
    // Proof -> We prove via induction on r

    // Base Case (r = 2)
    // The inner loop for r = 2 starts with j = 2 and sets smallest[2] = 2 because it is initially -1
    // Thus, smallest[2] is correctly set to 2, which is the smallest prime factor of 2

    // Inductive Step
    // Assume the proposition holds for all 2 <= w < r
    // We need to show that it holds for r

    // Case 1: r is a prime number
    // Since it has no smaller prime factor, smallest[r] is -1 at this stage
    // When r = r in the outer loop, the inner loop starts at j = r and sets smallest[r] = r
    // Therefore, smallest[r] is set to r, which is its smallest prime factor

    // Case 2: r is composite
    // Let p be the smallest prime factor of r
    // Since p < r, in the iteration r = p, the inner loop for j = p, p*2, ..., would eventually reach j = r and set smallest[r] = p
    // smallest[r] is set at the earliest possible time to the smallest prime factor p, because the outer loop starts from the smallest r upwards
    // No later iteration will overwrite it because of the condition if (smallest[j] == -1)

    // Therefore, by induction, smallest[r] correctly stores the smallest prime factor for all r in [2, b]

    return smallest;
}

int countDiv(int n) {
    if (n <= 1)
        return -1;
    int cnt = 1;
    for (int r = 2; r * r <= n; r++) {
        int sum = 1;
        while (!(n % r))
            sum++, n /= r;
        cnt *= sum;
    }
    if (n > 1)
        cnt *= 2;
    return cnt;
}

// this returns all the prime factors of n with their multiplicity, maintained in sorted order
// this runs in O(root(n)) time
vector<int> factor(int n) {
    vector<int> ret;
    if (n <= 1)
        return ret;
    for (int r = 2; r * r <= n; r++)
        while (!(n % r))
            ret.push_back(r), n /= r;
    if (n > 1)
        ret.push_back(n);
    return ret;
}

// f(x) = number of distinct prime factors of x for all x >= 2
// then, f(x) is O(log(x))

// suppose you want to find the prime factorization of numbers in the range [2, MAX] efficiently
// first find the maximum prime factor of each [2, MAX] using the sieve, and then use it to calculate the
// prime factorization of any x in the range [2, MAX] easily
void factorTwo() {
    int n;
    cin >> n;

    // it is guaranteed that all x are in the range [2, MAX] where MAX = 10^6
    // maxPrime[r] is the maximum prime factor of r
    vector<int> maxPrime(1000000 + 1, -1);
    for (int r = 2; r <= 1000000; r++)
        if (maxPrime[r] == -1) // r is a prime itself
            for (int j = r; j <= 1000000; j += r)
                maxPrime[j] = r;

    int x;
    while (n--) {
        cin >> x;
        // prime contains the prime factors of x with their multiplicity, in descending order
        vector<int> prime;
        while (x != 1) {
            int p = maxPrime[x];
            while (!(x % p))
                prime.push_back(p), x /= p;
        }
    }
}

vector<int> div(const int b) {
    vector<int> ans;
    if (b <= 0)
        return ans;

    for (int r = 1; r * r <= b; r++) {
        if (!(b % r)) {
            ans.push_back(r);
            if (r != b / r)
                ans.push_back(b / r);
        }
    }
    return ans;
}

// function to find all primes <= n using the Sieve of Eratosthenes
vector<int> primes(const int n) {
    vector<int> ans;
    if (n <= 1)
        return ans;
    vector<bool> vis(n + 1, true);
    for (int r = 2; r <= n; r++) {
        if (vis[r]) {
            ans.push_back(r);
            for (int x = r * 2; x <= n; x += r)
                vis[x] = false;
        }
    }
    // Proposition -> If at the start of iteration r = x, vis[x] = true, then x is a prime; otherwise, it is not
    // Proof -> We prove via induction on x
    // Base Case (x = 2)
    // At the start of iteration x = 2, vis[2] = true since it's the first iteration of the loop.
    // The base case thus holds
    // Inductive Step
    // Assume the proposition is true for all 2 <= w <= x for some x >= 2
    // Assume that at the start of iteration r = x + 1, vis[x + 1] = true
    // Since the proposition is true for all 2 <= w <= x, the if statement would've run for all 2 <= w <= x that are primes
    // This would have resulted in the marking of all multiples w of p that are <= n for all 2 <= p <= x that are primes to value false
    // So, if vis[x + 1] is true, this means that it has not been marked false, and thus, it is not a multiple of any prime <= x
    // Thus, x + 1 is a prime itself
    // Otherwise, if it would've been marked false at the beginning of iteration r = x + 1, it must be a multiple of
    // some prime <= x, and thus not a prime itself
    // Thus the proposition is true for r = x + 1
    // The induction step thus holds
    return ans;
}