#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MX_CHR (int)(256)
#define MX_SHIFT (int)(62)

char nxt[MX_CHR][MX_SHIFT];

void solve() {
	string a, w, s; cin >> a >> w >> s;

	int t = a.length();
	for (int i = 0; i < t; i++)
		for (int j = 0; j < t; j++)
			nxt[a[i]][j] = a[(i - j + t) % t];

	int n = w.length();
	vector<int> p(n + 1, 0);
	int j = p[1];
	for (int i = 2; i <= n; i++) {
		while (j > 0 && w[j + 1 - 1] != w[i - 1])
			j = p[j];
		if (w[j + 1 - 1] == w[i - 1])
			++j;
		p[i] = j;
	}

	vector<int> ans;
	for (int i = 0; i < t; i++) {
		int cnt = 0;
		j = 0;
		for (char c : s) {
			while (j > 0 && w[j + 1 - 1] != nxt[c][i])
				j = p[j];
			if (w[j + 1 - 1] == nxt[c][i])
				++j;
			if (j == n)
				cnt++, j = p[j];
		}
		if (cnt == 1)
			ans.push_back(i);
	}

	if (ans.empty())
		cout << "no solution" << endl;
	else if (ans.size() == 1)
		cout << "unique: " << ans[0] << endl;
	else { 
		cout << "ambiguous:";
		for (int f : ans)
			cout << " " << f;
		cout << endl;
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;	
}