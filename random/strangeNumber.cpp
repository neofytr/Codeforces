#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		int x, k;
		cin >> x >> k;

		int cnt = 0;
		for (int r = 2; r * r <= x; r++)
			while(!(x % r))
				cnt++, x /= r;
		if (x > 1) cnt++;

		if (cnt >= k)
			cout << 1 << endl;
		else 
			cout << 0 << endl;
	}
	return 0;
}