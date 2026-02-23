#include <bits/stdc++.h>
using namespace std;

#define LEFT 0
#define RIGHT (int)(2 * 1e5)
#define INF (int)(1e17)

typedef pair<int, int> Line;

void init(int l = LEFT, int r = RIGHT, int idx) {
	tree[idx] = {INF, INF};
	if (l == r) return;

	int m = (l + r) >> 1;
	init(l, m, idx << 1), init(m + 1, r, (idx << 1) | 1);
}