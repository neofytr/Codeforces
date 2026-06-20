#include <bits/stdc++.h>
using namespace std;

// A string s of length n (for n >= 1) is a sequence of n characters, with the ith of them represented by
// s[i] for 1 <= i <= n
// "" is the string of length 0, also known as the empty string 

// Let s is a string of length n >= 1
// s[i, j] is the string s[i], ..., s[j] for 1 <= i <= j <= n, and is the 
// empty string ("") for 1 <= i, j <= n such that i > j

// The prefix of s of length k, for 0 <= k <= n, is the string s[1, k]. It is proper
// iff k < n

// The suffix of s of length k, for 0 <= k <= n, is the string s[n - k + 1, n]. It is proper
// iff k < n

// The border of length k of s, for 0 <= k < n, is said to exist iff s[1, k] == s[n - k + 1]
// and is the string s[1, k]

// A string t is a border of s iff |t| < n, the border of length |t| of s exists and is equal to t

// We define B(s) = {t | t is a border of s} to be the
// set of all borders of s

// We define b(s) = {0 <= k < n | border of length k of s exists} to be the set of all
// border lengths of s

// Border of length 0 always exists for any string t, and is the empty string
// Thus, "" belongs to B(s), and 0 belongs to b(s) 