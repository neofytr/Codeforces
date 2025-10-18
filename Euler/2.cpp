#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int a = 1;
	int b = 2;

	int sum = 2;
	while (b <= 4000000) {
		int tmp = b;
		b += a;
		if (!(b & 1))
			sum += b;
		a = tmp;
	}

	cout << sum << endl;
	return 0;
}