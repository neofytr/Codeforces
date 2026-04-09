#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define LOG2(x) (63 - __builtin_clzll(x)) // x should be of 64 bits

// An operation x is associative iff
// (a x b) x c = a x (b x c)

// An operation x is idempotent iff a x a = a

// The op used in the following sparse table implementation must be both associative
// and idempotent

// A few example of such operations are min, max and gcd

template<typename T>
class SparseTable {
private:
	// table[r][j] = minimum of the range [arr[r], ..., arr[r + (1LL << j) - 1]] 
	// for 0 <= j <= LOG2(MAX_N) and 1 <= r <= (MAX_N + 1 - (1LL << j))
	vector<vector<T>> table;
	function<T(T, T)> op;

public:
	// table[r][j] = min(table[r][j - 1], table[r + (1LL << (j - 1))][j - 1]) 
	// table[r][0] = arr[r] 
	SparseTable(vector<T> &arr, function<T(T, T)> operation) {
		int n = (int)arr.size(); // 1-based indexed array
		n--;
		if (!n) return; // handle empty case

		int lg = LOG2(n);
		table.resize(n + 1, vector<T>(lg + 1));

		op = operation;
		// build base case for j = 0
		for (int r = 1; r <= n; r++)
			table[r][0] = arr[r];

		// build sparse table for higher powers of 2
		for (int j = 1; j <= lg; j++)
			for (int r = 1; r <= (n + 1 - (1LL << j)); r++)
				table[r][j] = op(table[r][j - 1], table[r + (1LL << (j - 1))][j - 1]);
	}

	// query the minimum value in range [l, r] (1-based indexing)
	int query(int l, int r) {
		int lg = LOG2(r - l + 1);
		// min of the two overlapping intervals covering [l, r]
		return op(table[l][lg], table[r - (1LL << lg) + 1][lg]);
	}
};