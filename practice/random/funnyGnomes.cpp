#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX_N 500

int32_t main() {
	int n;
	cin >> n;

	int val;
	vector<bitset<MAX_N + 1>> g(n + 1, bitset<MAX_N + 1>(0));
	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= n; col++) {
			cin >> val;
			if (val) g[row][col] = true;
			else g[row][col] = false;
		}


	
	return 0;
}


// 1 -> 2 -> 3 -> 1
// 		  -> 4 -> 4