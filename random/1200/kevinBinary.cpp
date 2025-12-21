#include <bits/stdc++.h>
using namespace std;

#define int long long 

bool cmp(
	const pair<vector<int>, pair<int,int>> &a,
	const pair<vector<int>, pair<int,int>> &b
) {
	const vector<int> &va = a.first;
	const vector<int> &vb = b.first;

	for (size_t i = 0; i < va.size(); ++i) {
		if (va[i] != vb[i])
			return va[i] > vb[i];  // 0 < 1
	}
	return false;
}

void solve() {
	string str;
	cin >> str;

	int n = str.length();
	vector<int> v(n + 1);
	for (int r = 0; r < n; r++)
		v[r + 1] = str[r] - '0';

	int cnt = 0;
	while (cnt + 1 <= n && v[cnt + 1]) cnt++;

	if (cnt == n) {
		cout << 1 << " " << n << " " << 1 << " " << 1 << endl;
		return;
	}

	// [cnt + 1, n]
	int len = n - cnt;
	vector<pair<vector<int>, pair<int, int>>> vec;
	for (int r = 1; r <= n - len; r++) {
		vector<int> tmp(len + 1, 0);
		for (int i = 1; i <= len; i++) 
			tmp[i] = v[cnt + i] ^ v[r + i];
		vec.push_back({tmp, {r, r + len - 1}});
	}
		
	sort(vec.begin(), vec.end(), cmp);
	cout << 1 << " " << n << " " << vec[vec.size() - 1].second.first << " " << vec[vec.size() - 1].second.second << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}