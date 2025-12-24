#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<int> b(n + 1);
	for (int r = 1; r <= n; r++) cin >> b[r];
	
	set<int> x;
	for (int i = 1; i * i <= b[n]; i++) 
		if (!(b[n] % i)) {
			int one = i, two = b[n] / i;
			if (!(b[n - 1] % one)) x.insert(b[n - 1] / one);
			if (one != two && !(b[n - 1] % two)) x.insert(b[n - 1] / two);
		}

	for (int r = n - 2; r >= 1; r--) {
		if (!(b[r + 1] % b[r]))
			continue;

		vector<int> no;
		for (int e : x)
			if (b[r] % e) no.push_back(e);
			else if (b[r + 1] % (b[r] / e)) no.push_back(e);

		for (int k : no) x.erase(k);
	}

	for (int e : x) cout << e << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}