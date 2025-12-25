#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MOD (998244353)

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

void solve() {
	int n;
	cin >> n;

	vector<int> p(n), q(n);
	for (int r = 0; r < n; r++) cin >> p[r];
	for (int r = 0; r < n; r++) cin >> q[r];


	set<pair<int, int>> parr;
	set<pair<int, int>> qarr;
	vector<int> res(n);
	for (int r = 0; r < n; r++) {
		parr.insert({p[r], r}), qarr.insert({q[r], r});
		auto [pval, pidx] = *parr.rbegin();
		auto [qval, qidx] = *qarr.rbegin();

		if (pval > qval) 
			res[r] = (pw(2, pval) + pw(2, q[r - pidx])) % MOD;
		else if (qval > pval)
			res[r] = (pw(2, qval) + pw(2, p[r - qidx])) % MOD;
		else {
			int pval2 = q[r - pidx];
			int qval2 = p[r - qidx];
			if (pval2 > qval2)
				res[r] = (pw(2, pval) + pw(2, pval2)) % MOD;
			else
				res[r] = (pw(2, qval) + pw(2, qval2)) % MOD;
		}
	}

	for (int r = 0; r < n; r++)
		cout << res[r] << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}