#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n = 10;

	int sum = 0;
	for (int r = 3; r < n; r += 3)
		sum += r;

	for (int r = 5; r < n; r += 5)
		sum += r;

	for (int r = 15; r < n; r += 15)
		sum -= r;

	cout << sum << endl;
	return 0;
}