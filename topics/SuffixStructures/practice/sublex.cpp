#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N (int)(90000)
#define MAX_Q (int)(500)

string s; int n, q;
int sa[MAX_N + 1], rnk[MAX_N + 1], tmp[MAX_N + 1];
int lcp[MAX_N + 1];
int queries[MAX_Q + 1];
int cnt[MAX_N + 1];

int32_t main() {
	cin >> s; n = s.length(); cin >> q;
	for (int i = 1; i <= q; i++)
		cin >> queries[i];

	for (int i = 1; i <= n; i++)
		sa[i] = i, rnk[i] = s[i - 1] - 'a' + 1;
	for (int k = 1; k < n; k <<= 1) {
		auto cmp = [&] (int a, int b) {
			if (rnk[a] != rnk[b])
				return rnk[a] < rnk[b];
			int ra = (a + k <= n ? rnk[a + k] : 0);
			int rb = (b + k <= n ? rnk[b + k] : 0);
			return ra < rb;
		};
		sort(sa + 1, sa + n + 1, cmp);
		tmp[sa[1]] = 1;
		for (int i = 2; i <= n; i++)
			tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		swap(tmp, rnk);
		if (rnk[sa[n]] == n)
			break;
	}

	int h = 0;
	for (int i = 1; i <= n; i++) {
		if (rnk[i] == 1) {
			lcp[rnk[i]] = h = 0;
			continue;
		}
		int j = sa[rnk[i] - 1];
		while (i + h <= n && j + h <= n && s[i + h - 1] == s[j + h - 1])
			h++;
		lcp[rnk[i]] = h;
		if (h)
			h--;
	}

	cnt[0] = 0;
	for (int i = 1; i <= n; i++)
		cnt[i] = cnt[i - 1] + (n - sa[i] + 1) - lcp[i];

	for (int i = 1; i <= q; i++) {
		int k = queries[i];
		int j = upper_bound(cnt + 1, cnt + n + 1, k) - cnt;
		
		if (cnt[j - 1] == k) {
			int start = sa[j - 1] - 1;
			cout << s.substr(sa[j - 1] - 1, n - start) << endl;
			continue;
		}

		int need = k - cnt[j - 1] - 1;
		int start = sa[j] - 1;
		int end = sa[j] + lcp[j] + need - 1;
		cout << s.substr(start, end - start + 1) << endl;
	}
	return 0;
}