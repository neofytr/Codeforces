#include <bits/stdc++.h>
using namespace std;

#define int long long

string s; int n;
inline int cmp_substr(int pos, const string &t) {
	int m = t.length();

	for (int i = 0; i < m; i++) {
		if (pos + i >= n)
			return -1;
		if (s[pos + i] < t[i])
			return -1;
		if (s[pos + i] > t[i])
			return 1;
	}
	return 0;
}

int32_t main() {
    std::ios_base::sync_with_stdio(false);    
    std::cin.tie(NULL);
	cin >> s;
	n = s.length();

	vector<int> sa(n + 1), rank(n + 1), tmp(n + 1);
	vector<int> t(n + 1), cnt(n + 1);

	vector<int> f(26 + 1, 0);
	for (int i = 1; i <= n; i++) {
		int r = s[i - 1] - 'a' + 1;
		f[r]++;
	}
	for (int i = 1; i <= 26; i++) 
		f[i] += f[i - 1];
	for (int i = n; i >= 1; i--) {
		int r = s[i - 1] - 'a' + 1;
		sa[f[r]--] = i;
	}
	rank[sa[1]] = 1;
	for (int i = 2; i <= n; i++)
		rank[sa[i]] = rank[sa[i - 1]] + (s[sa[i - 1] - 1] != s[sa[i] - 1]); 


	auto cmp = [&] (int a, int b, int k) {
		if (rank[a] != rank[b])
			return rank[a] < rank[b];
		int ra = (a + k <= n ? rank[a + k] : 0);
		int rb = (b + k <= n ? rank[b + k] : 0);
		return ra < rb;
	};
	for (int k = 1; k < n; k <<= 1) {
		int ptr = 1;
		for (int i = n - k + 1; i <= n; i++)
			t[ptr++] = i; // these suffixes don't even have the second part of the tuple
		
		for (int i = 1; i <= n; i++)
			if (sa[i] - k >= 1)
				t[ptr++] = sa[i] - k; // the remaining suffixes ordered by their second part in the tuple

		// now we have to sort the elements of t stably by the first part of tuple, i.e, by rank[t[i]]
		fill(cnt.begin(), cnt.end(), 0ll);
		for (int i = 1; i <= n; i++) {
			int c = rank[t[i]];
			cnt[c]++;
		}

		for (int i = 1; i <= n; i++)
			cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; i--) {
			int c = rank[t[i]];
			sa[cnt[c]--] = t[i];
		}

		tmp[sa[1]] = 1;
		for (int i = 2; i <= n; i++)
			tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i], k);
		swap(rank, tmp);

		if (rank[sa[n]] == n)
			break;
	}

	string tt;
	int k; cin >> k;
	while (k--) {
		cin >> tt;
		int left = 1;
		int right = n;

		int first = n + 1;
		while (left <= right) {
			int m = left + ((right - left) >> 1);
			int i = sa[m];

			int res = cmp_substr(i - 1, tt);
			if (res >= 0) {
				if (!res)
					first = m;
				right = m - 1;
			}
			else 
				left = m + 1;
		}

		if (first == n + 1) {
			cout << 0 << endl;
			continue;
		}

		int last = -1;
		left = 1, right = n;
		while (left <= right) {
			int m = left + ((right - left) >> 1);
			int i = sa[m];
			int res = cmp_substr(i - 1, tt);
			if (res <= 0) {
				if (!res)
					last = m;
				left = m + 1;
			}
			else 
				right = m - 1;
		}

		cout << last - first + 1 << endl;
	}
	return 0;
}