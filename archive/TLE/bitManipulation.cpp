#include <bits/stdc++.h>
using namespace std;

#define int long long 

// Where is Bit Manipulation Used?
// Problems may or may not directly involve bit manipulation

// Some problems use bitwise operators in the problem statement itself,
// whereas some problems might use bit manipulation indirectly
// For eg, if the problem involves powers of 2, it might be related to binary
// Similarly, powers of other numbers might be in their own base

// When solving a bitwise problem, think in bitwise
// When solving a problem that uses addition, multiplication, etc., we use
// decimal, which is the most appropriate base in that case
// When solving a problem that uses bitwise operators, we need to use binary,
// which is the most appropriate base in this case

// Let x is a signed int
// Then ~x = -(x + 1)

// In a signed y-bit int, the largest power of 2 (i.e, 2 ^ (y - 1)) is
// multiplied with a -1 before calculating the value of the number
// Let x is a signed y-bit int
// Then x is onto the range [-2^(y - 1), 2^(y - 1) - 1]

// A bitmask is a sequence of N bits that encodes a subset, where the
// element is taken if a bit is set, and not taken if a bit is unset
// Eg, 10110 would mean indices 1, 2, and 4 are taken, while 0 and 3 are not

// By generating all bitmasks of some size, we can easily generate all
// subsets of an array
// This way, we can use iteration instead of recursion to generate subsets

// Types of problems:
// 1. Bit-independent problems:
// Can solve for each bit separately. The solution for a bit x will not depend
// on the solution for a bit y. (&, |, ^)

// 2. Bit-dependent problems:
// Cannot solve for each bit separately. All the bits are interconnected
// and cannot be treated as independent. (+, -, *, /)

// a ^ b = 0 iff a = b
// A number is its own inverse under XOR
// 0 is the identity element under XOR
// A ^ A = 0
// A ^ 0 = A

// Some Properties
// 1. OR/AND/XOR are associative and commutative
// 2. A ^ 0 = A
// 3. A ^ A = 0
// 4. If A ^ B = C, then A ^ C = B
// 5. A ^ B ^ B = A
// 6. A & B <= min(A, B)
// 7. A | B >= max(A, B)
// 8. (A | B) + (A & B) = A + B
// 9. For A >= 1, A is a power of 2 iff A & (A - 1) = 0
// 10. m & (m - 1) turns off the lowest bit that was set to 1 in a 
// positive integer m
// 11. For a positive number x, x ^ (x & (x - 1)) is the lowest (rightmost) bit set to 1 in x
// 12. For a signed integer x, -x = ~x + 1, and -x contains all zeroes
// to the right of lowest set bit in x, contains 1 at the position of the
// lowest set bit in x, and contains the bitwise not of x to the left of 
// the lowest set bit in x
// 13. For a signed integer x, x & (-x) is the lowest (rightmost) bit set to 1 in x
// 14. For positive integer x, __builtin_ctzll(x) is the power of 2 in the prime-factorization of x
// 15. For x >= 0
// i. floor(x / 2) = x >> 1
// ii. ceil(x / 2) = (x >> 1) + (x & 1)

// AND: Commutative, Associative, Identity(0xFF), Annihilator(0x00), Idempotent
// OR: Commutative, Associative, Identity(0x00), Annihilator(0xFF), Idempotent
// XOR: Commutative, Associative, Identity(0x00), Inverse (itself)
// NOT: Inverse(itself)

// AND and OR absorb each other
// 1. a & (a | b) = a
// 2. a | (a & b) = a

// There are some pairs of distributive operations:
// 1. AND over OR
// 2. OR over AND
// 3. AND over XOR (a & (b ^ c) = (a & b) ^ (a & c))

// Sum of Products:
// (a ^ b) & (c ^ d) = (a & c) ^ (a & d) ^ (b & c) ^ (b & d)

// XOR doesn't distribute over OR or AND, and neither does OR distribute
// over XOR

// DeMorgan's Laws:
// 1. ~(a | b) = ~a & ~b
// 2. ~(a & b) = ~a | ~b

// Some Properties
// 1. a - b = ~(~a + b)
// 2. a + b = (a ^ b) + ((a & b) << 1)
// 3. min(a, b) = ~max(~a, ~b)
// 4. max(a, b) = ~min(~a, ~b)

// One Liners
// 1. Upper case english alphabet ch to lower case
// ch | ''
// 2. Lowercase english alphabet ch to upper case
// ch | '_'

// Computing XOR from 1 to n
int rangeXOR(int n) {
	if (n <= 0)
		return -1;

	switch (n & 3) {
		case 0:
			return n;
		case 1:
			return 1;
		case 2:
			return n + 1;
		case 3:
			return 0;
	}
	return -1;
}

// Let A = {x | n >= x >= 0 and n + x = n ^ x}
// Let k = number of 0 bits after the most significant set bit in n
// We define k = 0 when n = 0
// Then |A| = 2^k
int cnt(int n) {
	if (n < 0)
		return -1;
	if (!n)
		return 1;

	int k = (64 - __builtin_clzll(n)) - __builtin_popcountll(n);
	return (1LL << k);
}

// We can quickly check if bits in a number are in an alternate pattern (like 101010).
// Compute bitwise XOR (XOR denoted using ^) of n and (n >> 1). If n has an alternate pattern, then n ^ (n >> 1) operation will produce a number having all bits set
// after (and including) the most significant set bit of n

void subset() {
	int n;
	cin >> n;

	// 1 <= n <= 20
	vector<int> arr(n);
	for (int &val : arr) cin >> val;

	// Iterate through all the subsets of arr
	for (int subset = 0; subset < (1LL << n); subset++) {
		for (int bit = 0; bit < n; bit++)
			if (subset & (1LL << bit))
				cout << arr[bit] << " ";
		cout << endl;
	}
}

// gives the true not of x
int truenot(int x) {
	if (!x) return 1;
	if (x < 0) return ~x; // this operation is consistent with the
	// true not for numbers who have no leading zeroes
	int leadingZeroes = __builtin_clzll(x); // undefined for x <= 0
	int left = sizeof(int) * 8 - leadingZeroes;
	// left will never be equal to 32/64 now since that is possible
	// only for negative numbers; so, (1ll << left) won't ever overflow
	int mask = (1LL << left) - 1;
	return (~x) & mask;
}

// __builtin_popcount(x) / __builtin_popcountll(x)
// Counts the number of 1s in the binary representation of x

// __builtin_clz(x) / __builtin_clzll(x)
// Counts the number of leading zeroes in the binary representation
// of a positive integer x

// __builtin_ctz(x) / __builtin_ctzll(x)
// Counts the number of trailing zeroes in the binary representation
// of a positive integer x

int popcnt(unsigned int x) {
	if (!x) return 0;

	int cnt = 0;
	while(x)
		cnt++, x &= (x - 1);
	return cnt;
}

bool isPowOfTwo(unsigned int x) {
	return x && !(x & (x - 1));
}

// You are given a sequence of 1 <= n <= 1e7 numbers, each 
// in the interval [0, 1e9]
// How many different values appear in the sequence?
void diffNumbers() {
	int n; // 1 <= n <= 1e7
	cin >> n;

	int val;
	bitset<1e9 + 1> b(0);
	while(n--) {
		cin >> val; // 0 <= val <= 1e9
		b[val] = true;
	}

	cout << b.count() << endl;
}

// You are given 1 <= n <= 1000 items, each with some weight wi
// Is there a subset of items with total weight W <= 1e6
void knapsack() {
	int n, w;
	cin >> n >> w;

	int wi;
	bitset<1e6 + 1> wt;

	wt[0] = true;
	while(n--) 
		cin >> wi, wt |= (wt << wi);
	
	cout << (wt[w] ? "YES" : "NO") << endl;
}

// Iterate efficiently over all submasks of a mask
// Given a bitmask m, we want to efficiently iterate through all
// of its submasks, that is, masks s in which only bits
// that were included in mask m are set
void submaskEnumeration() {
	int m;
	cin >> m; // m >= 1

	// The following loop iterates over all the 
	// submasks of m (including m and 0), without repetition, and in
	// descending order
	for (int s = m; s = (s - 1) & m) {
		// s is a submask of m
		if (!s) break;
	}

	// Lemma 1:
	// If an iteration r = k occurs, s >= 0 at its beginning, for any k >= 1
	// Base Case (k = 1)
	// The first iteration occurs and s = m >= 1 >= 0 at its beginning
	// Inductive Step
	// Assume that the claim is true for r = k
	// Assume that the iteration r = k + 1 occurs
	// Then, at the end of iteration r = k, s > 0
	// Since then, s is transformed to m & (s - 1) at the beginning of iteration r = k + 1
	// , s >= 0 holds at the beginning of iteration r = k + 1

	// Lemma 2
	// If an iteration r = k occurs, s <= m at its beginning, for any k >= 1

	// Lemma 3:
	// The value of s at the beginning of each iteration decreases strictly
	// Proof:
	// Let both iteration r = k and r = k + 1 occur for some k >= 1
	// Let s1 is the value of s at the beginning of iteration r = k
	// Let s2 is the value of s at the beginning of iteration r = k + 1

	// Since iteration r = k + 1 occurs, s1 > 0
	// Also, s2 = m & (s1 - 1)
	// Thus s2 <= min(m, s1 - 1) <= s1 - 1
	// Thus s2 < s1

	// Since s decreases strictly and s >= 0 at the beginning of each iteration and the
	// break statement executes when s = 0, the loop terminates after a finite number of steps

	// Lemma 4:
	// If an iteration r = k occurs, s is a submask of m at its beginning, for any k >= 1
	// Base Case (k = 1)
	// The iteration r = 1 occurs and s = m at its beginning
	// Inductive Step
	// Let the claim is true for iteration r = k
	// Let the iteration r = k + 1 occur
	// Let s1 is the value of s at the beginning of iteration r = k
	// Let s2 is the value of s at the beginning of iteration r = k + 1

	// Since iteration r = k + 1 occurs, then so does r = k, and hence,
	// s1 is a submask of m

	// Now, s2 = m & (s1 - 1)
	// Also, s1 > 0 since iteration r = k + 1 occurs
	// Since s1 - 1 < m, s2 is a submask of m

	// Lemma 7:
	// Let m > 0 and s <= m
	// Then r = m & s is the largest submask of m that is <= s

	// Lemma 6:
	// Let m > 0, s > 0 and s <= m
	// Then r = (s - 1) & m is the largest submask of m, smaller than s 
	// , and r >= 0

	// The loop iterates over all submasks of m, in descending order, and
	// without repetition

	// If m has k bits set (k >= 0), the loop iterates 2^k times as there
	// are 2^k submasks of m then

	int n;
	cin >> n;
	for (int m = 0; m < (1LL << n); m++)
		for (int s = m; s = m & (s - 1)) {
			// use s and m
			if (!s) break;
		}

	// The time complexity of the above loop is O(3^n)
	// Any 0 <= m < (1LL << n), will have exactly k bits set for some 0 <= k <= n
	// For an m having k bits set, the inner loop will execute exactly 2^k times, for some 0 <= k <= n
	// The number of m having k bits set is C(n, k)

	// Thus, the total number of iterations of the loop is summation from (k = 0 to n) of C(n, k) * 2^k = 3^n
}

int32_t main() {
	int n;
	cin >> n;

	cout << truenot(n) << endl;
	return 0;
}

// Observations
// 1. For non-negative integers a, b and c, the expression
//    	f(a, b, c) = (a ^ b) + (b ^ c) + (c ^ a)
// 	  is always even