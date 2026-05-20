#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> str(n + 1, -1);
	vector<int> divs;

	for (int f = 1; f * f <= n; f++) {
		if (n % f) continue;
		int one = f, two = n / f;
		divs.push_back(one);
		if (one != two) divs.push_back(two);
	}

	str[1] = 0;
	for (int i = 2; i <= n; i++) {
		bool bad[26] = {};
		if (i > 1 && str[i - 1] != -1)
			bad[str[i - 1]] = true;

		for (int d : divs)
			if (i - d >= 1 && str[i - d] != -1)
				bad[str[i - d]] = true;

		for (int c = 0; c <= 25; c++)
			if (!bad[c]) {
				str[i] = c;
				break;
			}
	}
		
	for (int i = 1; i <= n; i++)
		cout << (char)(str[i] + 'a');
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}