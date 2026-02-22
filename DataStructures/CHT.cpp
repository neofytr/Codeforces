#include <bits/stdc++.h>
using namespace std;

#define INF (1e18)

// Slope Monotonically Decreasing
// Query Minimum
struct Line {
	double m, c;
};

struct CHT {
	vector<pair<Line, double>> v(1);

	void insert(double m, double c) {
		double xint = -INF;
		while (!v.empty()) {
			auto &[L, x] = v.back();
			xint = (L.m - c) / (m - L.m);
			if (xint > x) break;
			v.pop(); // the last line becomes obsolete
		}
		v.push_back({{m, c}, xint});
	}

	int query(int x) {
		if (v.size() == 1) return -1;
		int left = 1;
		int right = v.size();
		while (right != left + 1) {
			int mid = left + (right - left) / 2;
			if (v[mid].second <= x) left = mid;
			else right = mid;
		}
		
		Line L = v[left].first;
		return L.m * x + L.c;
	}
}