#include <bits/stdc++.h>
using namespace std;

#define int long long

void twoDimDiffArrays() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> arr(n, vector<int>(m));
    for (int row = 0; row < n; row++)
        for (int col = 0; col < n; col++)
            cin >> arr[row][col];

    // we are given q queries of the form
    // (x1, y1), (x2, y2), x
    // where 0 <= x1 <= x2 < n and 0 <= y1 <= y2 < m
    // for each query, we increment all the elements of arr in the rectangle with diagonal endpoints (x1, y1) and (x2, y2)
    vector<vector<int>> diff(n, vector<int>(m, 0));
    int q, x1, x2, y1, y2, x;
    cin >> q;
    while (q--) {
        cin >> x1 >> x2 >> y1 >> y2 >> x;

    }
}

void twoDimPrefix() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> arr(n, vector<int>(m));
    for (int row = 0; row < n; row++)
        for (int col = 0; col < m; col++)
            cin >> arr[row][col];

    // for 1 <= r <= n and 1 <= c <= m,
    // prefix[r][c] = sum of the rectangle with diagonal end points (0,0) and (r - 1, c - 1)
    // row[0][c] = 0 for all 0 <= c <= m
    // row[r][0] = 0 for all 0 <= r <= n
    vector<vector<int>> prefix(n + 1, vector<int>(n + 1, 0));
    for (int row = 1; row <= n; row++)
        for (int col = 1; col <= m; col++)
            prefix[row][col] = prefix[row - 1][col] + prefix[row][col - 1] + arr[row - 1][col - 1] - prefix[row - 1][col - 1];

    int q, x1, x2, y1, y2;
    while (q--) {
        cin >> x1 >> x2 >> y1 >> y2;
        // (x1, y1) and (x2, y2) are diagonal end points of a rectangle we want the sum of in array
        // x2 > x1 and y2 > y1
        int ans = prefix[y2 + 1][x2 + 1] - prefix[y1][x2 + 1] - prefix[y2 + 1][x1] + prefix[y2][x2];
        cout << ans << endl;
    }
}

void prefixSums() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // for 1 <= r <= n, prefix[r] is the sum of elements in the array in the index range [0, r)
    // prefix[0] = 0
    vector<int> prefix(n + 1, 0);

    // prefix[r] = prefix[r - 1] + arr[r - 1] for 1 <= r <= n
    // sum[l, r] = prefix[r + 1] - prefix[l] for 0 <= l <= r <= n - 1
    // sum[l, r) = prefix[r] - prefix[l] for 0 <= l <= r <= n
}

void differenceArray() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // we are given q queries of the form (l, r, x), which means increment each of arr[l], ..., arr[r] by x, where 0 <= l <= r < n
    int q, l, r, x;
    cin >> q;
    vector<int> prefix(n + 1);

    while (q--) {
        cin >> l >> r >> x;
        // updating difference array: range update query in constant time
        prefix[l] += x;
        prefix[r + 1] -= x;
    }

    // pros:
    // constant time range update queries,
    // no recursion or precomputation needed,
    // can be coded in very few lines,
    // very fast and efficient for batch range updates,
    // updates do not affect the original array until all queries are processed

    // cons:
    // only efficient when there are only update queries and no fetch queries
    // if we want to get element values in between updates, each get is o(n)
    // overall complexity can degrade to o(n * q1 + q), where q1 = number of get queries
    // this is almost like brute force when many get queries exist

    // solution:
    // we can use fenwick tree (binary indexed tree) with difference array
    // to support get queries in o(log n) while still having o(1) range updates
    // fenwick is easy to code and supports prefix sums which we need to recover single element from difference array

    // applying the updates to the array in o(n) (for a get operation after the range updates)
    arr[0] += prefix[0];
    for (int r = 1; r <= n; r++)
        prefix[r] += prefix[r - 1], arr[r] += prefix[r];
}
