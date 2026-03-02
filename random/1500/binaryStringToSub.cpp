#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	string str; cin >> str;

	set<int> one, zero;
	for (int i = 0; i < n; i++)
		if (str[i] == '0') zero.insert(i);
		else one.insert(i);

	vector<int> s(n + 1, 0);
	int cnt = 0;
	while (!one.empty() && !zero.empty()) {
		cnt++;
		if (*one.begin() < *zero.begin()) {
			bool turn = false; 
			int last = *one.begin();
			s[last] = cnt;
			one.erase(one.begin());
			while (true) { 
				if (!turn) {
					auto itr = zero.lower_bound(last);
					if (itr == zero.end()) break;
					last = *itr, zero.erase(itr);
					turn = true;
				} else {
					auto itr = one.lower_bound(last);
					if (itr == one.end()) break;
					last = *itr, one.erase(itr);
					turn = false;
				}
				s[last] = cnt;
			}
		} else {
			bool turn = false; 
			int last = *zero.begin();
			s[last] = cnt;
			zero.erase(zero.begin());
			while (true) { 
				if (!turn) {
					auto itr = one.lower_bound(last);
					if (itr == one.end()) break;
					last = *itr, one.erase(itr);
					turn = true;
				} else {
					auto itr = zero.lower_bound(last);
					if (itr == zero.end()) break;
					last = *itr, zero.erase(itr);
					turn = false;
				}
				s[last] = cnt;
			}
		}
	}

	int x = cnt;
	cnt += one.size() + zero.size();
	cout << cnt << endl;
	for (int i = 0; i < n; i++)
		if (!s[i]) cout << ++x << " ";
		else cout << s[i] << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}