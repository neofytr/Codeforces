#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	string str;
	cin >> str;

	vector<int> s;
	for (int i = 0; i < n; i++)
		if (str[i] == '*')
			s.push_back(i + 1);

	int cnt = s.size();
	if (!cnt) {
		cout << 0 << endl;
		return;
	}

	vector<int> g(cnt);
	for (int i = 0; i < cnt; i++)
		g[i] = s[i] - (i + 1);   

	sort(g.begin(), g.end());

	int x = g[cnt / 2];        

	long long cost = 0;
	for (int i = 0; i < cnt; i++)
		cost += llabs(g[i] - x);

	cout << cost << '\n';
}

void solve2() {
	int n;
	cin >> n;

	string str;
	cin >> str;

	int cnt = 0;
	vector<int> vec(n + 1);
	for (int r = 1; r <= n; r++)
		vec[r] = (str[r - 1] == '*' ? (cnt++, 1) : 0);

	int i = 1;
	vector<int> s(cnt + 1);
	unordered_map<int, int> f;
	for (int r = 1; r <= n; r++)
		if (vec[r]) s[i] = r, f[n - cnt + i - s[i]]++, i++;

	int cost = 0;
	int d = 0;

	for (int k = 1; k <= cnt; k++)
		cost += abs(n - cnt + k - s[k]);

	d += f[0];
	int mini = cost;
	for (int r = 2; r <= n - cnt + 1; r++) {
		cost += (2 * d - cnt);
		d += f[r - 1];
		mini = min(mini, cost);
	}

	cout << mini << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}