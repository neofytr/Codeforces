#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	string a, b; cin >> a >> b;

	int n = a.length(), m = b.length();
	vector<int> p(m + 1, 0);
	int j = 0;
	for (int i = 2; i <= m; i++) {
		while (j > 0 && b[j + 1 - 1] != b[i - 1])
			j = p[j];
		if (b[j + 1 - 1] == b[i - 1])
			++j;
		p[i] = j;
	}

	vector<vector<int>> aut(m + 1, vector<int>(26));
	for (int j = 0; j <= m; j++)
		for (int c = 0; c < 26; c++)
			if (j < m && b[j + 1 - 1] - 'a' == c)
				aut[j][c] = j + 1;
			else if (!j)
				aut[j][c] = 0;
			else 
				aut[j][c] = aut[p[j]][c];

	vector<int> pos;

	j = 0;
	for (int i = 1; i <= n; i++) {
		j = aut[j][a[i - 1] - 'a'];
		if (j == m)
			pos.push_back(i - m + 1);
	}

	if (pos.empty()) 
		cout << "Not Found" << endl;
	else {
		cout << pos.size() << endl;
		for (int e : pos)
			cout << e << " ";
		cout << endl;
	}
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}