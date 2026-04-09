#include <bits/stdc++.h>
using namespace std;

#define int long long 

int cost(string str, char chr) {
	int n = str.length();
	vector<int> vec;

	int i = 0;
	for (int r = 0; r < n; r++)
		if (str[r] == chr)
			vec.push_back(r - i++);

	sort(vec.begin(), vec.end());
	int s = vec.size();
	vector<int> p(s + 1);
	p[0] = 0;
	for (int r =  1; r <= s; r++)
		p[r] = p[r - 1] + vec[r - 1];

	int c = LLONG_MAX;
	for (int r = 0; r < n; r++) {
		auto itr = lower_bound(vec.begin(), vec.end(), r);
		if (itr == vec.end())
			c = min(c, s * r - p[s]);
		else if (itr == vec.begin())
			c = min(c, p[s] - s * r);
		else {
			int idx = itr - vec.begin();
			c = min(c, (p[s] - p[idx]) - ((s - 1) - idx + 1) * r + (idx * r - p[idx]));
		}
	}

	return c;
}

void solve() {
	int n;
	cin >> n;

	string str;
	cin >> str;

	cout << min(cost(str, 'a'), cost(str, 'b')) << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}

	return 0;
}