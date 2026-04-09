#include <bits/stdc++.h>
using namespace std;

#define int long long 

int c, m, x;

bool can(int k) {
	// can we form atleast k teams?
	// we can do this if we have atleast k coders, k mathematicians, and atleast k left

	return c >= k && m >= k && (c - k + m - k + x >= k);
}

int32_t main() {
	int q;
	cin >> q;

	while(q--) {
		cin >> c >> m >> x;

		int left = 0; // can form atleast 0 teams
		int right = 1e8 + 1; // cannot form this many teams

		// if we can form atleast x teams, we can form atleast x - 1 teams
		while (right != left + 1) {
			int mid = left + (right - left) / 2;

			if (can(mid))
				left = mid;
			else 
				right = mid;
		}

		cout << left << endl;
	}
	return 0;
}