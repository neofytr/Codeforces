#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	vector<int> even;
	vector<int> odd;

	for (int r = 1; r <= n; r++)
		if (arr[r] & 1)
			odd.push_back(r);
		else 
			even.push_back(r);

	if (even.size() == 1)
		cout << even[0] << endl;

	if (odd.size() == 1)
		cout << odd[0] << endl;

	return 0;
}