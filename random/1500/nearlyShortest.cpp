#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	vector<int> str(n + 1);
	for (int i = 1; i <= n; i++) str[i] = s[i - 1] - 'a' + 1;
		
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
} 