#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	vector<vector<int>> st(n + 1, vector<int>(31));
	for (int bit = 0; bit < 31; bit++)
		st[n][bit] = ((arr[n] & (1LL << bit)) ? n : -1);
	for (int r = n - 1; r >= 1; r--) 
		for (int bit = 0; bit < 31; bit++) {
			if (arr[r] & (1LL << bit)) {
				if (st[r + 1][bit] != -1)
					st[r][bit] = st[r + 1][bit];
				else 
					st[r][bit] = r;
			}
			else 
				st[r][bit] = -1;
		}
	
	auto query = [&]() -> void {
	 	int l, k;
	 	cin >> l >> k;

	 	int one = LLONG_MAX;
	 	int zro = -1;
	 	for (int bit = 30; bit >= 0; bit--) 
	 		if (k & (1LL << bit)) {
	 			if (st[l][bit] == -1) {
	 				cout << zro << " ";
	 				return;
	 			}
	 			one = min(one, st[l][bit]);
	 		} else {
	 			zro = max(zro, min(st[l][bit], one));
	 		}
	 	cout << max(one, zro) << " ";
	 };

	 int q;
	 cin >> q;

	 while(q--) {
	 	query();		
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