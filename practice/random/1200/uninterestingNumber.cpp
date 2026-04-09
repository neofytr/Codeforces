#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	string num;
	cin >> num;

	int sum = 0;
	vector<int> f(4, 0);
	for (int c : num) {
		if (c == '2') f[2]++;
		else if (c == '3') f[3]++;
		sum += c - '0';
	}

	set<int> two, three;
	for (int r = 0; r <= f[2]; r++)
		two.insert((2 * r) % 9);
	for (int r = 0; r <= f[3]; r++)
		three.insert((6 * r) % 9);

	int need = 9 - (sum % 9);
	if (need == 9) {
		cout << "YES\n";
		return;
	}

	for (int r1 : two)
		if (three.find((need - r1 + 9) % 9) != three.end()) {
			cout << "YES\n";
			return;
		}

	cout << "NO\n";
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}	