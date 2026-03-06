#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
================================================================================
SQRT DECOMPOSITION (MASTER REFERENCE)
================================================================================

IDEA
----
Divide array of size n into blocks of size b ≈ sqrt(n).

block(x) = floor((x-1)/b) + 1

Block i covers:
	[b*(i-1)+1 , min(n, b*i)]

Queries touch:
	• ≤2 partial blocks  → O(b)
	• middle full blocks → O(n/b)

Total per operation:
	O(b + n/b)

Minimized at b ≈ sqrt(n).

Typical complexity:
	preprocess : O(n)
	query      : O(sqrt(n))
	update     : O(sqrt(n))
	memory     : O(n)


================================================================================
BLOCK STRUCTURE
================================================================================

For each block maintain:

a[i]     → base element value
block[i] → summary of block
lazy[i]  → pending block update

Example summaries:

	sum
	min / max
	gcd
	frequency maps
	sorted vector
	hash
	bitsets

Technique works whenever block summaries can answer full-block queries.


================================================================================
CORE INVARIANT
================================================================================

In this implementation:

	true_value(k) = a[k] + lazy[block(k)]

Meaning:

• a[k] stores base value
• lazy[b] stores pending update for whole block
• block_sum[b] always stores TRUE sum of block

Thus full block queries read block_sum directly.


================================================================================
QUERY STRUCTURE
================================================================================

Query [l, r].

i = block(l)
j = block(r)

Cases:

1. i == j
	process directly

2. i < j
	process:

	left partial block
	full middle blocks
	right partial block


Visual:

[l ... |------|------| ... r]
 partial  full   full   partial


================================================================================
UPDATE STRUCTURE
================================================================================

Same partition.

For full blocks:
	update lazy tag

For partial blocks:
	update elements individually.

Always keep block summaries consistent.


================================================================================
WHEN TO USE SQRT DECOMPOSITION
================================================================================

Useful when:

• segment tree merge is complicated
• operations not associative
• block-level brute force is acceptable
• constraints ~2e5

Segment tree:
	O(log n) but rigid

Sqrt decomposition:
	O(sqrt n) but flexible


================================================================================
COMMON APPLICATIONS
================================================================================

Range queries:
	sum / min / max / xor / gcd

Range updates:
	add / assign

More advanced:
	mode queries
	distinct count
	k-th statistics
	string hashes
	bitset blocks

Also appears in:

Mo's algorithm → sqrt decomposition on queries.


================================================================================
VARIANTS
================================================================================

1) Lazy blocks
	range updates

2) Rebuild blocks
	handle complex updates

3) Ordered blocks
	store sorted arrays per block

4) Frequency blocks
	used in distinct queries

5) Bitset blocks
	fast bitwise operations


================================================================================
PERFORMANCE NOTES
================================================================================

b ≈ sqrt(n) theoretically optimal.

Often faster in practice:

	b = 300–700

due to cache locality and fewer divisions.

Last block may be smaller than b.


================================================================================
IMPLEMENTATION
================================================================================
*/

int32_t main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n; cin >> n;

	int b = sqrt(n);

	vector<int> a(n + 1);
	vector<int> p(n / b + 2, 0);
	vector<int> lazy(n / b + 2, 0);

	for (int i = 1; i <= n; i++)
		cin >> a[i];

	auto get = [&](int x) {
		return (x - 1) / b + 1;
	};

	for (int i = 1; i <= n; i++)
		p[get(i)] += a[i];

	int q; cin >> q;

	while (q--) {

		int t; cin >> t;

		if (t == 1) {

			int l, r; cin >> l >> r;

			int sum = 0;

			int i = get(l);
			int j = get(r);

			if (i == j) {

				for (int k = l; k <= r; k++)
					sum += a[k] + lazy[i];

				cout << sum << "\n";
				continue;
			}

			for (int k = i + 1; k <= j - 1; k++)
				sum += p[k];

			for (int k = l; k <= min(n, b * i); k++)
				sum += a[k] + lazy[i];

			for (int k = b * (j - 1) + 1; k <= r; k++)
				sum += a[k] + lazy[j];

			cout << sum << "\n";
		}

		else {

			int l, r, x;
			cin >> l >> r >> x;

			int i = get(l);
			int j = get(r);

			if (i == j) {

				for (int k = l; k <= r; k++) {
					a[k] += x;
					p[i] += x;
				}

				continue;
			}

			for (int k = i + 1; k <= j - 1; k++) {
				lazy[k] += x;
				p[k] += b * x;
			}

			for (int k = l; k <= min(n, b * i); k++) {
				a[k] += x;
				p[i] += x;
			}

			for (int k = b * (j - 1) + 1; k <= r; k++) {
				a[k] += x;
				p[j] += x;
			}
		}
	}

	return 0;
}