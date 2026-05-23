#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)

int32_t main() {
	string s; cin >> s;
	int n = s.length();
	vector<char> str(n + 1);
	for (int i = 1; i <= n; i++) str[i] = s[i - 1];

	int k; cin >> k;
	unordered_map<string, bool> f;
	for (int i = 1; i <= k; i++) cin >> s, f[s] = true;
	return 0;
}