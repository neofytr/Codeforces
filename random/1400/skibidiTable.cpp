#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Point {
	int x, y;
};

Point coord(int start, int l, Point curr) {
	if (!l) return curr;

	int side = (1ll << (l - 1));

}

int get(int start, int l, Point curr, Point topleft) {
	if (!l)
		return start;

	int side = (1ll << (l - 1));
	// first quadrant
	if (curr.x <= topleft.x + side - 1 && curr.y <= topleft.y + side - 1)
		return get(start, l - 1, curr, topleft);

	if (curr.y >= topleft.y + side && curr.x >= topleft.x + side)
		return get(start + side * side, l - 1, curr, {topleft.x + side, topleft.y + side});

	if (curr.x <= topleft.x + side - 1 && curr.y >= topleft.y + side)
		return get(start + 2 * side * side, l - 1, curr, {topleft.x, topleft.y + side});

	return get(start + 3 * side * side, l - 1, curr, {topleft.x + side, topleft.y});
}

void solve() {
	int n; cin >> n;
	int q; cin >> q;

	while (q--) {
		char q1, q2; cin >> q1 >> q2;
		if (q2 == '>') {
			int x, y; cin >> x >> y;
			cout << get(1, n, {y, x}, {1, 1}) << endl;
		} else {
			int d; cin >> d;
			cout << -1 << endl;
		}
	}
}

int32_t main() {
	int t; cin >> t;
	while(t--) solve();
	return 0;
}