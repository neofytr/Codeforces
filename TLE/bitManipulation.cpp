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


int32_t main() {
	int n;
	cin >> n;

	cout << truenot(n) << endl;
	return 0;
}