#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		int n;
		cin >> n;

		int val;
		map<int, int> mp;
		for (int r = 1; r <= (n * (n - 1)) / 2; r++)
			cin >> val, mp[val]++;

		unordered_map<int, int> finalArr;

		int beta = 0, alpha;
		for (auto itr = mp.rbegin(); itr != mp.rend(); ++itr) {
			auto [val, delta] = *itr;
			int rt = sqrt((2 * beta - 1) * (2 * beta - 1) + 8 * delta);
			rt += (-1 * 2 * beta + 1);
			rt /= 2;
			alpha = rt;
			beta += alpha;
			finalArr[val] = alpha;
		}

		for (auto &[val, cnt] : finalArr) {
			while(cnt--)
				cout << val << " ";
		}
		cout << endl;
	}
	return 0;
}