#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, k;
	cin >> n >> k;

	unordered_map<int, int> p;
	vector<int> facts;
	for (int r = 2; r * r <= n; r++)
		while(!(n % r))
			facts.push_back(r), p[r]++, n /= r;
	if (n > 1) p[n]++, facts.push_back(n);

	int cnt = 0;
	for (auto &[pr, c] : p)
		cnt += c;

	if (k > cnt) {
		cout << -1 << endl; 
		return 0;
	}

	for (int r = 0; r < k - 1; r++)
		cout << facts[r] << " ";

	int last = 1;
	for (int r = k - 1; r < facts.size(); r++)
		last *= facts[r];
	cout << last << endl;
	return 0;
}