#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;

		vector<int> arr(n);
		for (int &val : arr)
			cin >> val;

		sort(arr.begin(), arr.end());
		int x = arr.front() * arr.back();

		vector<int> divs;
		for (int r = 2; r * r <= x; r++)
			if (!(x % r)) {
				divs.push_back(r);
				if (x / r != r)
					divs.push_back(x / r);
			}

		sort(divs.begin(), divs.end());
		if (arr == divs)
			cout << x << endl;
		else 
			cout << -1 << endl;
	}
	return 0;
}