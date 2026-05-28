#include <bits/stdc++.h>
using namespace std;

#define MAX (int)(1e5)

string s; int n;
int sa[MAX + 1], rnk[MAX + 1], tmp[MAX + 1];
int lcp[MAX + 1], p[MAX + 1];

int get_cnt(string &sub) {
	int left = 1;
	int right = n;
	int len = sub.length();

	int first = -1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		int i = sa[mid];

		if (sub < s.substr(i - 1, len))
			right = mid - 1;
		else if (sub > s.substr(i - 1, len))
			left = mid + 1;
		else
			first = mid, right = mid - 1; 
	}

	if (first == -1)
		return 0;

	left = 1, right = n;
	int last = -1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		int i = sa[mid];

		if (sub < s.substr(i - 1, len))
			right = mid - 1;
		else if (sub > s.substr(i - 1, len))
			left = mid + 1;
		else
			last = mid, left = mid + 1; 
	}
	return p[last] - p[first - 1] - (last - first + 1) * (len - 1);
}

int get_exact(string &sub) {
	int left = 1;
	int right = n;
	int len = sub.length();

	int first = -1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		int i = sa[mid];

		if (sub < s.substr(i - 1, len))
			right = mid - 1;
		else if (sub > s.substr(i - 1, len))
			left = mid + 1;
		else
			first = mid, right = mid - 1; 
	}

	if (first == -1)
		return 0;

	left = 1, right = n;
	int last = -1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		int i = sa[mid];

		if (sub < s.substr(i - 1, len))
			right = mid - 1;
		else if (sub > s.substr(i - 1, len))
			left = mid + 1;
		else
			last = mid, left = mid + 1; 
	}

	return last - first + 1;
}

int32_t main() {
	cin >> s;
	n = s.length();

	for (int i = 1; i <= n; i++)
		sa[i] = i, rnk[i] = s[i - 1] - 'a' + 1;
	for (int k = 1; k < n; k <<= 1) {
		auto cmp = [&](int a, int b) {
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
		swap(rnk, tmp);
		if (rnk[sa[n]] == n)
			break;
	}

	p[0] = 0;
	for (int i = 1; i <= n; i++)
		p[i] = p[i - 1] + (n - sa[i] + 1);

	int k; cin >> k;
	string res; 
	int cnt = 0;
	char curr = 'a';
	while (true) {
		res.push_back(curr);
		int c = get_cnt(res);
		if (cnt + c < k) {
			curr++;
			cnt += c;
			res.pop_back();
			continue;
		}

		int cdash = get_exact(res);
		if (cnt + cdash < k) {
			cnt += cdash;
			curr = 'a'; // generate the next in order
			continue;
		}
		
		if (cnt + cdash == k) 
			break;
		curr = 'a';
	}

	cout << res << endl;
	return 0;
}