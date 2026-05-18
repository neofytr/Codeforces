#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	string tmp; cin >> tmp;

	vector<int> str(n + 1);
	for (int i = 1; i <= n; i++) str[i] = ((tmp[i - 1] == '(') ? 1 : -1);

	int open = 0, close = 0;
	for (int i = 1; i <= n; i++)
		if (str[i] == 1) open++;
		else close++;

	if (open != close) {
		cout << -1 << endl;
		return;
	}

	bool fw = true, bck = true;
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += str[i];
		if (sum < 0) {
			fw = false;
			break;
		}
	}

	sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += str[i];
		if (sum > 0) {
			bck = false;
			break;
		}
	}

	if (!fw && !bck) {
		cout << 2 << endl;

		vector<int> color(n + 1);
		int i = 1;
		int c;
		while (i <= n) {
			int j = i;
			sum = 0;
			if (str[j] == 1) c = 1;
			else c = 2;
			while (j <= n && sum + str[j] != 0) 
				color[j] = c, sum += str[j], j++;

			color[j] = c;
			i = j + 1;
		}

		for (int i = 1; i <= n; i++)
			cout << color[i] << " ";
	} else {
		cout << 1 << endl;
		for (int i = 1; i <= n; i++)
			cout << 1 << " ";
	}
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}