#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: cheCity
// URL: https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/C
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, r;
    cin >> n >> r;

    vector<int> dist(n);
    for (int &val : dist)
        cin >> val;

    // dist is sorted in increasing order
    // we want to find out the number of pairs (i, j) such that i < j and dist[j] - dist[i] > r
    int count = 0;
    for (int i = 0; i < n; i++) {
        // we want to find j such that dist[j] > r + dist[i]
        // we find the maximum j for which this is true (say q); then, it's true for all j in the range
        // [right, n - 1]
        const int target = r + dist[i];
        int left = -1;
        int right = n;

        while (right != left + 1) {
            const int mid = left + (right - left) / 2;
            if (dist[mid] > target)
                right = mid;
            else
                left = mid;
        }

        if (right <= n)
            count += n - right;
    }

    cout << count << endl;

    return 0;
}