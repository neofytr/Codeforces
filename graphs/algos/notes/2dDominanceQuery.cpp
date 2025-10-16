#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: 2D Dominance Query (Top-Right Dominance)

// Given a set of points {(x1, y1), (x2, y2), ..., (xn, yn)},
// and multiple queries of the form (xr, yr), we want to check if there exists any point
// (x, y) in the set such that:
// x >= xr and y >= yr

// Additionally, we want to find one such point if it exists

// This is a classical 2D dominance query problem, also known as a Top-Right quandrant
// query or skyline / maximal points problem

// Solution Idea:

// 1. Sort all the points in descending order of the x-coordinate
// This ensures that as we move along the list, x is decreasing

// 2. Build a suffix array storing the maximum y-coordinate from the current point
// to the end, and also store the
// This helps us quickly find the largest y for all points with x >= xr

// 3. For each query (xr, yr):
//    - Perform binary search on the sorted x-coordinates to find the first point with x >= xr
//    - Look at the corresponding suffix maximum y
// 		If it's >= yr, a valid point exists

// Complexity:
//	  - Preprocessing (sorting + suffix max): O(nlog(n))
// 	  - Each query: O(log(n))
// 	  - Space: O(n)

int32_t main() {
	int n;
	cin >> n;

	int x, y;
	vector<pair<int, int>> pts;
	for (int r = 1; r <= n; r++)
		cin >> x >> y, pts.push_back({x, y})

	// sort points by x descending
	sort(pts.begin(), pts.end(), [](auto &a, auto &b) {
		a.x > b.x;
	});

	// compute suffix max array for y and store index of that max
	// max[r] is the maximum value of y from pts[r, n - 1]
	// maxIdx[r] is the index of that y in pts
	vector<int> maxY(n);
	vector<int> maxIdx(n);

	maxY[n - 1] = pts[n - 1].y;
	maxIdx[n - 1] = n - 1;

	for (int r = n - 2; r >= 0; r--) {
		if (pts[r].y > maxY[r + 1])
			maxY[r] = pts[r].y, maxIdx[r] = r;
		else 
			maxY[r] = maxY[r + 1], maxIdx[r] = maxIdx[r + 1];
	}

	// extract x-coordinates for binary search
	vector<int> xs;
	for (auto &p : pts) xs.push_back(p.x);

	int q;
	cin >> q;
	int xr, yr;
	while(q--) {
		cin >> xr >> yr;

		// binary search for first point with x >= xr
		auto itr = lower_bound(xs.begin(), xs.end(), xr, greater<int>());
		bool found = false;

		if (itr != xs.end()) {
			int idx = itr - xs.begin();
			int candidateIdx = maxIdx[idx]; // index of point
			pair<int, int> pt = pts[candidateIdx];
			if (pt.y >= yr) {
				// valid point exists, print it
				cout << "(" << xr << "," << yr << ") -> YES, point ("<< p.x << "," << p.y << ")\n";
				found = true;
			}

			if (!found)
				cout << "(" << xr << "," << yr << ") -> NO\n";
		}
	}
}

