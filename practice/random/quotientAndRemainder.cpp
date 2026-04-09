#include <bits/stdc++.h>
using namespace std;

#define int long long

multiset<int>::iterator largest_leq(multiset<int>& ms, int x) {
	auto it = ms.upper_bound(x); 
	if (it == ms.begin()) 
		return ms.end();          
	--it;                     
	return it;
}

void solve() {
	int n, k;
	cin >> n >> k;

	int v;
	multiset<int> quo, rem;
	for (int r = 1; r <= n; r++)
		cin >> v, quo.insert(v);
	for (int r = 1; r <= n; r++)
		cin >> v, rem.insert(v);

	int cnt = 0;
	for (int r : rem) 
		if (r + 1 <= k) {
			int m = (k + 1) / (r + 1);

			auto itr = largest_leq(quo, m - 1);
			if (itr == quo.end())
				break;

			cnt++, quo.erase(itr);
		}
	
	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) solve();
}