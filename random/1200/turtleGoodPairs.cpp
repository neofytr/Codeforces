#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	string str;
	cin >> str;

	vector<int> f(26);
	for (char c : str)
		f[c - 'a']++;

	while (true) {
		bool placed = false;
		for (int c = 0; c < 26; c++)
			if (f[c]) cout << char(c + 'a'), f[c]--, placed = true;
		if (!placed) break;
	}
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}