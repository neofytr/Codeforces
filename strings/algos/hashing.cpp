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
// 					   = (hash[0, j] - hash[0, i - 1] + m) mod m

// So, by knowing the hash value of each prefix of string s, we can compute the hash of any substring
// directly using this formula. The only problem that we face in calculating it is that we must be able
// to divide (hash(s[1, j]) - hash(s[1, i - 1]))