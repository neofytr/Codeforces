#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int p = 33;
const int MOD = 1000000007;

#define get_hash(l, r, hash) \
( \
	(ll)ipw[(l) - 1] * \
	((((hash)[r] - (hash)[(l) - 1]) + MOD) % MOD) \
	% MOD \
)

string s;
int n;

vector<int> hashs, hasht, pw, ipw;
int modpow(int base, int exp) {
	int res = 1;
	while (exp) {
		if (exp & 1)
			res = (ll)res * base % MOD;

		base = (ll)base * base % MOD;
		exp >>= 1;
	}
	return res;
}

int cmp_substr(int i, string &t) {
	int len1 = n - i + 1;
	int len2 = (int)t.length();

	int left = 0;
	int right = min(len1, len2);

	int lcp = 0;

	while (left <= right) {
		int mid = (left + right) >> 1;
		if (
			mid == 0 ||
			get_hash(i, i + mid - 1, hashs)
			==
			get_hash(1, mid, hasht)
		) {
			lcp = mid;
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	if (lcp == len2)
		return 0;
	if (lcp == len1)
		return -1;
	if (s[i + lcp - 1] < t[lcp])
		return -1;
	return 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> s;

	n = (int)s.length();

	hashs.resize(n + 1);
	pw.resize(n + 1);
	ipw.resize(n + 1);

	pw[0] = ipw[0] = 1;

	for (int i = 1; i <= n; i++) {
		pw[i] = (ll)pw[i - 1] * p % MOD;
		ipw[i] = modpow(pw[i], MOD - 2);
	}

	for (int i = 1; i <= n; i++) {
		hashs[i] = (
			hashs[i - 1] +
			(ll)(s[i - 1] - 'a' + 1) * pw[i - 1]
		) % MOD;
	}

	vector<int> sa(n + 1);
	vector<int> rank(n + 1);
	vector<int> tmp(n + 1);

	vector<int> t(n + 1);
	vector<int> cnt(n + 1);

	vector<int> f(27);

	for (int i = 1; i <= n; i++) {
		int c = s[i - 1] - 'a' + 1;
		f[c]++;
	}

	for (int i = 1; i <= 26; i++)
		f[i] += f[i - 1];

	for (int i = n; i >= 1; i--) {
		int c = s[i - 1] - 'a' + 1;
		sa[f[c]--] = i;
	}

	rank[sa[1]] = 1;

	for (int i = 2; i <= n; i++) {
		rank[sa[i]] =
			rank[sa[i - 1]] +
			(s[sa[i - 1] - 1] != s[sa[i] - 1]);
	}

	auto cmp = [&](int a, int b, int k) {
		if (rank[a] != rank[b])
			return rank[a] < rank[b];

		int ra = (a + k <= n ? rank[a + k] : 0);
		int rb = (b + k <= n ? rank[b + k] : 0);

		return ra < rb;
	};

	for (int k = 1; k < n; k <<= 1) {
		int ptr = 1;

		for (int i = n - k + 1; i <= n; i++)
			t[ptr++] = i;

		for (int i = 1; i <= n; i++)
			if (sa[i] - k >= 1)
				t[ptr++] = sa[i] - k;

		fill(cnt.begin(), cnt.end(), 0);

		for (int i = 1; i <= n; i++)
			cnt[rank[t[i]]]++;

		for (int i = 1; i <= n; i++)
			cnt[i] += cnt[i - 1];

		for (int i = n; i >= 1; i--)
			sa[cnt[rank[t[i]]]--] = t[i];

		tmp[sa[1]] = 1;

		for (int i = 2; i <= n; i++) {
			tmp[sa[i]] =
				tmp[sa[i - 1]] +
				cmp(sa[i - 1], sa[i], k);
		}

		swap(rank, tmp);

		if (rank[sa[n]] == n)
			break;
	}

	int q;
	cin >> q;

	while (q--) {
		string tt;
		cin >> tt;

		int len = (int)tt.length();

		if (len > n) {
			cout << 0 << '\n';
			continue;
		}

		hasht.assign(len + 1, 0);

		for (int i = 1; i <= len; i++) {
			hasht[i] = (
				hasht[i - 1] +
				(ll)(tt[i - 1] - 'a' + 1) * pw[i - 1]
			) % MOD;
		}

		int left = 1;
		int right = n;

		int first = -1;

		while (left <= right) {
			int mid = (left + right) >> 1;

			int res = cmp_substr(sa[mid], tt);

			if (res >= 0) {
				if (res == 0)
					first = mid;

				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}

		if (first == -1) {
			cout << 0 << '\n';
			continue;
		}

		int last = -1;

		left = first;
		right = n;

		while (left <= right) {
			int mid = (left + right) >> 1;

			int res = cmp_substr(sa[mid], tt);

			if (res > 0) {
				right = mid - 1;
			}
			else {
				if (res == 0)
					last = mid;

				left = mid + 1;
			}
		}

		cout << last - first + 1 << '\n';
	}

	return 0;
}