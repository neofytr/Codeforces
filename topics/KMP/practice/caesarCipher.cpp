#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MX_CHR (int)(256)
#define MX_SHIFT (int)(62)

char nxt[MX_CHR][MX_SHIFT];

void solve() {
	string a, w, s; cin >> a >> w >> s;

	int t = a.length();
	sort(a.begin(), a.end());
	for (int i = 0; i < t; i++)
		for (int j = 0; j < t; j++)
			nxt[a[i]][j] = a[(i + j) % t];

	int n = w.length();
	vector<int> p(n + 1, 0);
	for (int i = 0; i < t; i++) {

	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;	
}