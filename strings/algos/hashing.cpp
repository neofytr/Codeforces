#include <bits/stdc++.h>
using namespace std;

#define int long long

// We want to solve the problem of comparing strings efficiently

// The brute force way is just to compare the letters of both strings, which has a time complexity
// of O(min(n1, n2)) if n1 and n2 are the sizes of the two strings.

// The idea behind string hashing is the following: we map each string into an integer and compare
// those instead of the string. Doing this allows us to reduce the execution time of the string comparison
// to O(1)

// For the conversion, we need a so-called hash function.
// The goal of it is to convert a string into an integer, the so-called hash of the string.
// The following condition has to hold: 
// If two strings s and t are equal, then their hashes also have to be equal. 
// Otherwise, we will not be able to compare strings.

// Notice, the opposite direction doesn't have to hold. If the hashes are equal, then the strings
// do not necessarily have to be equal. The reason why the opposite direction doesn't have to hold, is
// because there are exponentially many strings.

// So usually, we want the hash function to map strings onto numbers of a fixed range [0, m), then,
// comparing strings is just a comparison of two integers with a fixed length. And of course, we want
// hash(s) != hash(t) to be very likely if s != t.

// That's the important part that you have to keep in mind. Using hashing will not be 100% deterministically
// correct, because two complete different strings might have the same hash (the hashes collide). However, in 
// a wide variety of tasks, this can be safely ignored as the probability of the hashes of two different strings
// colliding is still very small.

// Calculation of the hash of a string
// The good and widely used way to define the hash of a string s[1, n] of length n is:

// hash(s) = (s[1] * p^0 + s[2] * p^1 + ... + s[n] * p^(n - 1)) % m

// where p and m are some chosen, positive numbers. It is called a polynomial rolling hash function.

// It is reasonable to make p a prime number roughly equal to the number of characters in the input
// alphabet. For example, if the input is composed of only lowercase letters of the English alphabet,
// then p = 31 is a good choice. If the input may contain both uppercase and lowercase letters, then
// p = 53 is a possible choice. 

// Obviously m should be a large number since the probability of two random strings colliding is about 1 / m.
// Sometimes, m = 2^64 is chosen, since then the integer overflows of unsigned 64-bit integers works exactly like
// the modulo operation. However, there exists a method, which generates colliding strings using this m (which works
// independently from the choice of p). So, in practice m = 2^64 is not recommended. 

// A good choice for m is some large prime number. A good choice is m = 10^9 + 9. This is a large number
// , but still small enough so that we can perform multiplication of two values using signed/unsigned 64-bit integers.

// Here is an example of calculating the hash of a string s, which consists of only lowercase letters
// of the English alphabet. We convert each character of s to an integer. Here we use the conversion
// a -> 1, b -> 2, ..., z -> 26. Converting a -> 0 is not a good idea, because then the hashes of the
// strings a, aa, aaa, ...  all evaluate to 0.

int compute_hash(const string &s) {
	const int p = 31;
	const int m = (int)(1e9 + 9);

	int hash = 0;
	int p_pow = 1;
	int n = s.size();
	for (int c : s)
		hash = (hash + p_pow * (c - 'a' + 1)) % m, p_pow = (p * p_pow) % m;
	return hash;
}

// Precomputing the powers of p might give a performance boost.

// Fast hash calculation of substrings of a given string
// Problem: Given a string s and indices i and j, find the hash of the substring s[i, j] for 0 <= i <= j < len(s)

// By definition, we have
// hash(s[0, -1]) = 0
// hash(s[i, j]) = summation(s[k] * p^(k - i) for i <= k <= j) mod m

// Multiplying by p^i gives:

// hash(s[i, j]) * p^i = summation(s[k] * p^k for i <= k <= j) mod m
// 					   = (hash(s[0, j]) - hash(s[0, i - 1]) + m) mod m
// hash(s[i, j]) = ((hash(s[0, j]) - hash(s[0, i - 1]) + m) % m * inv(p^i, m)) % m

// Define 
// h[0] = 0
// h[i] = hash of the first i characters of s = hash[0, i - 1] for 1 <= i <= n
// The array h can be computed as

int h[n + 1];
string s(n);

h[0] = 0;
int pp = 1;
int p = 31;
for (int r = 1; r <= n; r++)
	h[r] = (h[r - 1] + (s[r - 1] - 'a' + 1) * pp % m) % m, pp = pp * p % m;

// Then,
// hash(s[i, j]) = ((h[j + 1] - h[i] + m) % m * inv(p^i, m)) % m
// 

// So, by knowing the hash value of each prefix of string s, we can compute the hash of any substring
// directly using this formula. The only problem that we face in calculating it is that we must be able
// to divide (hash(s[0, j]) - hash(s[0, i - 1])) mod m by p^i. Therefore, we need to find the modular
// multiplicative inverse of p^i (under modulo m) and then perform multiplication with this inverse. We
// can precompute the inverse of every p^i, which allows computing the hash of any substring of s in O(1) time.

// However, there does exist an easier way. In most cases, rather than calculating the hashes of 
// substring exactly, it is enough to compute the hash multiplied by some power of p. Suppose we have 
// two hashes of two substrings, one multiplied by p^i and other multiplied by p^j. If i < j, then we multiply
// the first hash by p^(j - i), otherwise, we multiply the second hash by p^(i - j). By doing this, we 
// get both the hashes multiplied by the same power of p (which is the maximum of i and j) and now these
// hashes can be compared easily with no need for any division.

// Improve no-collision probability

// Quite often the above mentioned polynomial hash is good enough, and no collisions will
// happen during tests. Remember, the probability that collision happends is only 1 / m. For m = 1e9 + 9,
// the probability is about 1e(-9) which is quite low. But notice, that we only did one comparison.

// What if we compared a string s with 10^6 different strings? The probability of at least one collsion
// is now about 1e(-3). And if we want to compare 10^6 different strings with each other (e.g., by counting
// how many unique strings exists), then the probability of at least one collision happening is already about 1.
// It is pretty much guaranteed that this task will end with a collision and return the wrong result.

// There is a really easy trick to get better probabilities. We can just compute two different hashes
// for each string (by using two different p, and/or different m), and compare these pairs instead. 
// If m is about 10^9 for each of the two hash functions, than this is more or less equivalent as having
// one hash function with m about 1e18. When comparing strings 1e6 strings with each other, the probability
// that at least one collision happens is now reduced to 1e(-6).