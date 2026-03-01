#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e3)

int A[MAX + 1], B[MAX + 1];
int32_t main() {
	int n, k1, k2; cin >> n >> k1 >> k2;
	int t = k1 + k2;

	for (int r = 1; r <= n; r++) cin >> A[r];
	for (int r = 1; r <= n; r++) cin >> B[r];

	priority_queue<pair<int, int>> pq;
	for (int r = 1; r <= n; r++)  
		pq.push({llabs(2 * (A[r] - B[r])), r});
	

	while (t) {
		auto [d, r] = pq.top(); pq.pop();
		if (A[r] > B[r]) 
			A[r]--, pq.push({llabs(2 * (A[r] - B[r])), r}), t--;
		else  
			A[r]++, pq.push({llabs(2 * (A[r] - B[r])), r}), t--;
	}

	int res = 0;
	for (int r = 1; r <= n; r++)
		res += (A[r] - B[r]) * (A[r] - B[r]);
	cout << res << endl;
	return 0;
}