#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Point {
	int x, y;
};

Point coord(int start, int l, int d, Point curr) {
	if (!l) return curr;
	int side = (1ll << (l - 1));

	if (d <= start + side * side - 1)
		return coord(start, l - 1, d, curr);

	if (d >= start + side * side && d <= start + 2 * side * side - 1)
		return coord(start + side * side, l - 1, d, {curr.x + side, curr.y + side});

	if (d >= start + 2 * side * side && d <= start + 3 * side * side - 1)
		return coord(start + 2 * side * side, l - 1, d, {curr.x, curr.y + side});

	return coord(start + 3 * side * side, l - 1, d, {curr.x + side, curr.y});
}

int get(int start, int l, Point curr, Point topleft) {
	if (!l)
		return start;

	int side = (1ll << (l - 1));
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
			auto [x, y] = coord(1, n, d, {1, 1});
			cout << y << " " << x << endl;
		}
	}
}

int32_t main() {
	int t; cin >> t;
	while(t--) solve();
	return 0;
}