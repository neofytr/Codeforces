#include <bits/stdc++.h>
using namespace std;

#define int long long 

bool cmp(
    const pair<vector<int>, pair<int,int>> &a,
    const pair<vector<int>, pair<int,int>> &b
) {
    const vector<int> &va = a.first;
    const vector<int> &vb = b.first;

    size_t n = min(va.size(), vb.size());
    for (size_t i = 0; i < n; ++i) {
        if (va[i] != vb[i]) {
            return va[i] > vb[i];
        }
    }
    return va.size() < vb.size();
}


void solve() {
	string str;
	cin >> str;

	int n = str.length();
	vector<int> v(n + 1);
	for (int r = 0; r < n; r++)
		v[r + 1] = str[r] - '0';

	int cnt = 0;
	while (cnt + 1 <= n && v[cnt + 1]) cnt++;

	if (cnt == n) {
		cout << 1 << " " << n << " " << 1 << " " << 1 << endl;
		return;
	}

	// [cnt + 1, n]
	int len = n - cnt;
	vector<pair<vector<int>, pair<int, int>>> vec;
	for (int r = 1; r <= n - len + 1; r++) {
		vector<int> tmp;
		for (int i = 1; i <= len; i++) 
			if (v[cnt + i] ^ v[r + i - 1])
				tmp.push_back(i);
		vec.push_back({tmp, {r, r + len - 1}});
	}
		
	sort(vec.begin(), vec.end(), cmp);
	cout << 1 << " " << n << " " << vec[vec.size() - 1].second.first << " " << vec[vec.size() - 1].second.second << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}