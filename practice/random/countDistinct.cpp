#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	string s; cin >> s;
	unordered_map<string, bool> f;
	int cnt = 0;

	f[""] = true; cnt++;
	for (int i = 0; i < s.length(); i++) {
		string curr;
		for (int j = i; j >= 0; j--){
			curr.push_back(s[j]);
			if (!f[curr]) f[curr] = true, cnt++;
		}
	}

	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}