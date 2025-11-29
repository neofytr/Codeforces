#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n;
	cin >> n;

	// 1 <= n <= 1e5
	// 0 <= arr[r] <= r for 1 <= r <= n 
	// arr[r] <= arr[r + 1] for 1 <= r <= n - 1

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	// Find an array b[1, n] such that
	// MEX{b[1], ..., b[r]} = arr[r] for 1 <= r <= n
	// Or determine that such an array is not possible

	set<int> s;
	vector<int> b(n + 1);
	for (int r = 0; r <= n; r++)
		s.insert(r);

	for (int r = 1; r <= n; r++)
		s.erase(arr[r]);

	int i = 1, j = i;
	while (i <= n) {
		j = i;
		while (j <= n && arr[j] == arr[i])
			b[j] = *s.begin(), s.erase(b[j]), j++;
		s.insert(arr[i]);
		i = j;
	}

	for (int r = 0; r <= n; r++)
		s.insert(r);

	for (int r = 1; r <= n; r++) {
		s.erase(b[r]);
		if (arr[r] != *s.begin()) {
			cout << -1 << endl;
			return 0;
		}
	}

	for (int r = 1; r <= n; r++)
		cout << b[r] << " ";
	cout << endl;
	return 0;
}