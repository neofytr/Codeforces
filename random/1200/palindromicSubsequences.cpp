#include <bits/stdc++.h>
using namespace std;

#define int long long 

string getnum(int x) {
	ostringstream oss;
	oss << x << " " << x << " " << x + 1 << " " << x + 2 << " " << x << " " << x + 1 << " " << x + 1 << " ";
	return oss.str();
}

void solve() {
	int n;
	cin >> n;

	int k = n / 7;
	int i = 1;
	for (int r = 1; r <= k; r++)
		cout << getnum(i) << " ", i += 3;

	switch(n % 7) {
	case 0:
	case 1:
	case 2:
		for (int r = 1; r <= n % 7; r++)
			cout << i++ << " ";
		break;
	case 3:
		cout << i << " " << i << " " << i;
		break;
	case 4:
		cout << i << " " << i + 1 << " " << i << " " << i + 1;
		break;
	case 5:
		cout << i << " " << i + 1 << " " << i << " " << i + 1 << " " << i + 1;
		break;
	case 6:
		cout << i << " " << i << " " << i + 1 << " " << i + 2 << " " << i << " " << i + 1;
		break;
	}
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
} 