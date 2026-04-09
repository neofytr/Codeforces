#include <bits/stdc++.h>
using namespace std;

// Let p(k) denote the kth prime for k >= 1
// Let P(k) = product of the first k primes for k >= 1

// Let f(x) denote the smallest prime that doesn't divide x for any x >= 2
// Suppose for any number <= A, we want to find the smallest prime that doesn't divide
// that number

// What can be maximum value of this smallest prime?
// Let P(a) <= A and P(a + 1) > A for some a >= 1
// Its evident then that the maximum value of this smallest prime is p(a)

// Product of the first 16 primes > 10^18
// Precompute the first 17 primes and then for some x >= 2, check what is the smallest
// prime among these precomputed ones that do not divide x. That prime is f(x).