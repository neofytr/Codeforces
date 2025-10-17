#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int a, b;
	cin >> a >> b;
	if (b == 1) {
		cout << "NO\n";
		return;
	}

	cout << "YES\n";
	if (b == 2) {
		cout << a << " " << 3 * a << " " << 4 * a << endl;
		return;
	}

	cout << a << " " << (b - 1) * a << " " << a * b << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--){
		solve();
	}	
	return 0;
}