#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // A set of points on the plane is beautiful iff
    // 1. The coordinates of each point in the set are integers
    // 2. The euclidean distance between any two points in the set is
    // non-integral

    // Consider the rectangle R = {(x, y) such that 0 <= x <= n, 0 <= y <= n and x + y > 0}
    // We are to find the maximal U subset R such that U is beautiful

    // Let U subset R is beautiful
    // Then, two points in U cannot be from the same row, or same column
    // Thus, we can have atmost one point from each row, or from each column
    // Thus, |U| <= min(n, m) + 1

    // Consider the line x + y = min(n, m)
    // Any two points (x1, y1), (x2, y2) on it have a distance = |x2 - x1| * root(2), which is non-integral
    // Also, this line has min(n, m) + 1 integral points inside the rectangle R
    // Thus, one such maximal subset U of R is the integral points lying on this line

    int k = min(n, m);
    cout << k + 1 << endl;
    for (int r = 0; r <= k; r++)
    	cout << r << " " << k - r << endl;

    return 0;
}
