#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string s; cin >> s;
	int n = s.length();
	vector<int> sa(n + 1), rank(n + 1), tmp(n + 1);
	vector<int> t(n + 1), cnt(n + 1);

	for (int k = 1; k < n; k <<= 1) {
		int ptr = 1;
		for (int i = n - k + 1; i <= n; i++)
			t[ptr++] = i;

		for (int i = 1; i <= n; i++)
			if (sa[i] - k >= 1)
				t[ptr++] = sa[i] - k;

		// sort t[1, n] now according to rank[t[i]] stably
		fill(cnt.begin() + 1, cnt.end(), 0);
		for (int i = 1; i <= n; i++)
			cnt[rank[t[i]]]++;
		for (int i = 1; i <= n; i++)
			cnt[i] += cnt[i - 1];
		for (i = n; i >= 1; i--) {
			int r = rank[t[i]];
			sa[cnt[r]--] = t[i];
		}

		tmp[sa[1]] = 1;
		for (int i = 1; i <= n; i++)
			tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
	}
	return 0;
}