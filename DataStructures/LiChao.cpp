#include <bits/stdc++.h>
using namespace std;

#define int long long
#define LEFT 0
#define RIGHT (int)(2 * 1e5)
#define INF (int)(1e17)

typedef pair<int, int> Line; 
Line tree[RIGHT + 1];

int val(Line &l, int x) {
	return l.first * x + l.second;
}

void init(int l = 0, int r = RIGHT, int idx = 1) {
	tree[idx] = {INF, INF};
	if (l == r) return;
	int m = (l + r) >> 1;
	init(l, m, idx << 1);
	init(m + 1, r, (idx << 1) | 1);
}

void insert(Line L, int l = 0, int r = RIGHT, int idx = 1) {
	if (l == r) {
		if val(L, x) < val(tree[idx], x) tree[idx] = L;
		return;
	}

	int m = (l + r) >> 1;
	bool mid = (val(L, m) < val(tree[idx], m)); // true if the new line is better at m
	bool left = (val(L, l) > val(tree[idx], l));
}



