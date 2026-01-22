#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

typedef struct {
	int a, b;
} Dragon;

// the comparator should maintain struct weak ordering
auto cmp = [](Dragon &one, Dragon &two) -> bool {
	int m1 = max(one.a, two.a + one.b);
	int m2 = max(two.a, one.a + two.b);
	if (m1 < m2) return true;
	return false;
};

int32_t main() {
	int n;
	cin >> n;

	vector<Dragon> d(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> d[r].a >> d[r].b;

	sort(d.begin() + 1, d.end(), cmp);

	int left = 0;
	int right = 2 * 1e14 + 1;

	auto can = [&](int x) -> bool {
		for (int r = 1; r <= n; r++) {
			if (d[r].a > x) return false;
			x -= d[r].b;
		}
		return true;
	};

	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid))
			right = mid;
		else 
			left = mid;
	}

	cout << right << endl;
 	return 0;
}