#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> p(n + 1), g(n + 1);
	for (int i = 1; i <= n; i++) cin >> p[i], g[p[i]] = i;

	vector<int> used(n + 1, 0);
	int cnt = 0;
	int left = 1, right = n;
	int l = 1, r = n;
	int j = 0;
	while (left < right) {
		while (l <= n && used[l]) l++;
		while (r >= 1 && used[r]) r--;

		if (l >= r) break;

		if (p[l] == left && p[r] == right) {
			used[g[left]] = used[g[right]] = 1;
			left++, right--;
			j++;
			continue;
		}

		used[g[left]] = used[g[right]] = 1;
		cnt += (j + 1);
		left++, right--;
	}

	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}