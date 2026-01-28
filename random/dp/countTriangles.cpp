#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int A, B, C, D;
	cin >> A >> B >> C >> D;

	int res = 0;
	for (int r = C; r <= D + 1; r++) {
		int x = 0;
		x += max(0ll, (r - (A + B) + 1));
		x -= max(0ll, r - 2 * B);
		x -= max(0ll, r - A - C);
		x += max(0ll, r - B - C - 1);

		res += x * max(0ll, r - C);
	}

	for (int r = D + 2; r <= B + C; r++) {
		int x = 0;
		x += max(0ll, (r - (A + B) + 1));
		x -= max(0ll, r - 2 * B);
		x -= max(0ll, r - A - C);
		x += max(0ll, r - B - C - 1);

		res += x * max(0ll, D - C + 1);
	}

	cout << res << endl;
}