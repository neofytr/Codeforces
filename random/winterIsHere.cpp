#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N (int)(2 * 1e5)
#define MAX (int)(1e6)
#define MOD (int)(1e9 + 7)

int arr[MAX_N + 1];

// cnt[x] is the number of elements in arr[1, n] that are divisible by x for all x >= 0
int cnt[MAX + 1];

// dp[x] is the number of non-empty subsets of arr[1, n] that have their GCD = x for all x >= 1
int dp[MAX + 1];

// sz[r] is the sum of sizes of non-empty subsets of arr[1, n] that have their GCD = r for all r >= 1
int sz[MAX + 1];

int pw(int base, int exp) {
	int res = 1;
	base = base % MOD;

	while (exp) {
		if (exp & 1)
			res = res * base % MOD;
		base = base * base % MOD;
		exp >>= 1;
	}
	return res;
}


int32_t main() {
	int n;
	cin >> n;

	for (int r = 1; r <= n; r++) cin >> arr[r];

	// A subset of arr[1, n] is said to be good iff it's non-empty and
	// the GCD of all the elements in it is > 1

	// Find the sum of m * GCD(a1, ..., am) over all the good subsets A = {a1, ..., am} of arr[1, n]

	memset((void *)cnt, 0, sizeof(int) * (MAX + 1));
	memset((void *)dp, 0, sizeof(int) * (MAX + 1));
	memset((void *)sz, 0, sizeof(int) * (MAX + 1));

	cnt[0] = n;
	for (int r = 1; r <= n; r++) {
		int x = arr[r];
		for (int y = 1; y * y <= x; y++)
			if (!(x % y)) {
				cnt[y]++;
				if (y * y != x)
					cnt[x / y]++;
			}
	}

	for (int r = 1; r <= MAX; r++) {
		// dp[r] is currently the number of subsets of arr[1, n] whose elements are all 
		// divisible by r for r >= 1;
		// thus dp[r] is the sum of ((number of subsets of arr[1, n] whose GCD is r) + (number of subsets of arr[1, n] whose GCD is 2 * r) + .. and so on)
		// all these counts are disjoint and thus can easily be subtracted without using inclusion-exclusion
		dp[r] = pw(2, cnt[r]) - 1; 
		if (dp[r] < 0) dp[r] += MOD;

		if (cnt[r])
			sz[r] = cnt[r] * pw(2, cnt[r] - 1) % MOD;
	}

	for (int r = MAX; r >= 1; r--)
		for (int x = 2 * r; x <= MAX; x += r) {
			dp[r] -= dp[x]; // subtract from dp[r], which is currently
			// the number of subsets of arr[1, n] whose elements are divisible by r,
			// the number of subsets of arr[1, n] the GCD of whose elements is 2 * r, 3 * r, ...;
			// there is no oversubtraction since the counts being subtracted are of disjoint sets (the set of subsets whose GCD is 2 * r is disjoint
			// from the set of subsets whose GCD is 3 * r and so on)
			if (dp[r] < 0) dp[r] += MOD;

			sz[r] -= sz[x];
			if (sz[r] < 0) sz[r] += MOD;
		}

	int cnt = 0;
	for (int g = 2; g <= MAX; g++) {
		cnt += g % MOD * sz[g] % MOD;
		if (cnt >= MOD) cnt -= MOD;
	}

	cout << cnt << endl;
	return 0;
}