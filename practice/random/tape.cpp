#include <bits/stdc++.h>
using namespace std;

#define int long long 

// 1 2 3 4 5 .... m

int32_t main() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<int> b(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> b[r];

	auto can = [&](int x) {
		// can we cover all the broken segments with (atmost) k tape pieces of total length (atmost) x?
		
	};

	int left = 0;
	int right = 1e18 + 1;

	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid))
			right = mid;
		else
			left = mid;
	}

	cout << right << endl;
	return 0;
}