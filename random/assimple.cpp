#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	string str;
	cin >> str;

	int n = (int)str.length();
	vector<int> res;
	int i = 0;
	while (i < n - 2) {
		string sub = str.substr(i, 3);
		if (sub == "one")
			res.push_back(i + 1), i += 3;
		else if (sub == "two" && str.substr(i + 2, 3) == "one")
			res.push_back(i + 2), i += 5;
		else if (sub == "two")
			res.push_back(i + 1), i += 3;
		else 
			i++;
	}

	cout << res.size() << endl;
	for (int r : res)
		cout << r + 1 << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}