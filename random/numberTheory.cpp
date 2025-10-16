#include <bits/stdc++.h>
using namespace std;

#define int long long 

// Let x >= 4
// If x is a composite number, then it must have a factor in the range [2, root(x)]
// Proof:
// Let x is a composite number and let all it's factors are > root(x)
// Let x = a * b, where a, b > root(x) are it's factors
// Since a, b > root(x), it follows that a * b > x, a contradiction
bool isPrime(int x) {
	for (int r = 2; r * r <= x; r++)
		if (!(x % r))
			return false;

	return x >= 2;
}

#include <bits/stdc++.h>
using namespace std;

#define int long long 

// Checks if a number x is prime using trial division
// Runs in O(√x)
bool isPrime(int x) {
	for (int r = 2; r * r <= x; r++)
		if (x % r == 0)
			return false;
	return x >= 2;
}

/*
	Optimized Sieve of Eratosthenes
	--------------------------------
	Goal:
		Find all prime numbers in the range [2, n].

	Idea:
		If x is a composite number, it must have at least one factor p ≤ √x.
		Thus, when we reach any prime p ≤ √n, all multiples of p
		can be safely marked as non-prime.

	Optimization:
		When marking multiples of p, we can start from p², because:
			- Any number smaller than p² that is a multiple of p
			  would have already been marked by a smaller prime factor.
			  (Example: 3 * 5 = 15 will already be marked when p = 3.)
*/

/*
	Correctness Sketch
	------------------
	Base Case:
		At the start, all numbers ≥ 2 are assumed prime.

	Induction Step:
		When processing prime r, all numbers that are multiples of primes < r
		have already been marked. So marking r's multiples starting from r²
		preserves correctness.

	Result:
		After finishing, prime[x] = true if and only if x is a prime.

	Time Complexity:
		The number of operations is roughly:
			n * (1/2 + 1/3 + 1/5 + 1/7 + ...)
		≈ O(n log log n)

	Space Complexity: O(n)
*/

vector<int> sieve(int n) {
	if (n <= 1)
		return {};

	// prime[r] = true means r is currently considered prime
	vector<bool> prime(n + 1, true);

	// For every number r ≤ √n:
	// If r is still marked as prime, mark all multiples of r (starting from r²) as composite.
	for (int r = 2; r * r <= n; r++)
		if (prime[r])
			for (int j = r * r; j <= n; j += r)
				prime[j] = false;

	// Return the prime flags for all numbers [0, n].
	return prime;
}

// Let n >= 2
// We then claim that naiveSieve(n) returns an array prime[0, n + 1] such that
// prime[r] = true iff r is a prime for all 2 <= r <= n

// We prove our claim by induction
// Let P(k) = "At the beginning of iteration r = k,  prime[i] = true iff i is a prime for all 2 <= i <= k" for all k >= 2

// Base Case (k = 2)
// This holds trivially

// Inductive Step
// Let P(m) is true for all 2 <= m <= k
// We show that P(k + 1) is also true

// Let 2 <= m <= k
// Since P(m) is true, at the beginning of iteration r = m, prime[m] = true iff m is a prime
// If m is a prime, the inner loop marks all the multiples of m that are >= 2 * m as not prime

// Thus, for any 2 <= m <= k that are prime, all their multiples are marked not prime at the beginning of iteration r = k + 1
// If k + 1 is a composite number it must have all its prime factors in the range [2, k]
// So, if k + 1 was composite, it must've been marked prime[k + 1] = false at the beginning of iteration r = k + 1, otherwise not
// P(k + 1) then holds since P(k) is true

// Thus P(r) is true for all r >= 2

// Since P(n) is true (because n >= 2), at the beginning of iteration r = n, we would've marked
// all primes that are in the range [2, n]
// For the rest of this iteration, any value in the range [2, n] is not altered, so the array remains the
// same after the iteration too
// Thus, our claim is proved

// Time Complexity is (N / 2 + N / 3 + ... ) = N * (summation over all primes p <= N of 1 / p) ~ O(Nlog(log(N)))
vector<int> naiveSieve(int n) {
	if (n <= 1)
		return {};

	// find all primes in the range [2, n]
	vector<bool> prime(n + 1, true);

	for (int r = 2; r <= n; r++)
		if (prime[r])
			for (int j = 2 * r; j <= n; j += r)
				prime[j] = false;
	return prime;
}

// Let x >= 2
// Then, the smallest divisor of x is prime

// Let x >= 2
// Atmost one prime factor of x is greater than root(x)

vector<int> primeFact(int x) {
	if (x <= 1)
		return {};

	vector<int> fact;
	for (int r = 2; r * r <= n; r++)
		while(!(n % r))
			fact.push_back(r), n /= r;
	if (n > 1) fact.push_back(n);
	return fact;
}

int gcd(int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}