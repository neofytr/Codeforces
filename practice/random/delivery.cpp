#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> A(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> A[r];

	vector<int> B(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> B[r];

	auto can = [&](int x) -> bool {
		// can we recv all the dishes in <= x time?
		int sum = 0;
		for (int r = 1; r <= n; r++)
			if (A[r] > x)
				sum += B[r];
		return sum <= x;
	};

	int left = 0; // no dishes can be at petyas in 0 time
	int right = min(*max_element(A.begin() + 1, A.end()), accumulate(B.begin() + 1, B.end(), 0LL)) + 1; // can be done in this time

	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid))
			right = mid;
		else 
			left = mid;
	}
	cout << right << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}