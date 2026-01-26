#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> p(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> p[r];
	
	int maxi = n;
	int start = -1;
	for (int r = 1; r <= n; r++)
		if (p[r] == maxi) maxi--;
		else {
			start = r;
			break;
		}

	if (start == -1) {
		for (int r = 1; r <= n; r++)
			cout << p[r] << " ";
		cout << endl;
		return;
	}

	int end;
	for (int r = 1; r <= n; r++)
		if (p[r] == maxi) end = r;

	reverse(p.begin() + start, p.begin() + end + 1);
	for (int r = 1; r <= n; r++)
		cout << p[r] << " ";
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