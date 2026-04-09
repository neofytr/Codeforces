#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, x;
	cin >> n >> x;
	string s;
	cin >> s;

	bool wallLeft = false, wallRight = false;
	for (int i = 0; i < x - 1; i++)
		if (s[i] == '#') wallLeft = true;
	for (int i = x; i < n; i++)
		if (s[i] == '#') wallRight = true;

	if (!wallLeft || !wallRight) {
		cout << 1 << "\n";
		return;
	}

	int leftEmpty = 0;
	for (int i = x - 2; i >= 0 && s[i] == '.'; i--)
		leftEmpty++;

	int rightEmpty = 0;
	for (int i = x; i < n && s[i] == '.'; i++)
		rightEmpty++;

	cout << max(leftEmpty, rightEmpty) + 1 << "\n";
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
