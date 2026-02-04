#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;
	if (m > (n * (n + 1)) / 2 || m < n) {
		cout << -1 << endl;
		return;
	}

	if (n == 1) {
		cout << 1 << endl;
		return;
	}

	set<int> s;
	s.insert(0);

	int sum = m - n;
	for (int r = n - 1; r >= 1; r--)
		if (r <= sum)
			s.insert(r), sum -= r;

	vector<int> front;
	vector<bool> seen(n + 1, false);

	for (int e : s) front.push_back(e + 1);
	sort(front.rbegin(), front.rend());

	cout << front[0] << endl;
	seen[front[0]] = true;

	for (int r = 0; r + 1 < front.size(); r++) {
		cout << front[r] << " " << front[r + 1] << endl;
		seen[front[r + 1]] = true;
	}

	vector<int> back;
	for (int r = 1; r <= n; r++)
		if (!seen[r]) back.push_back(r);

	if (!back.empty())
		cout << 1 << " " << back[0] << endl;

	for (int r = 0; r + 1 < back.size(); r++)
		cout << back[r] << " " << back[r + 1] << endl;
}


int32_t main() {
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}