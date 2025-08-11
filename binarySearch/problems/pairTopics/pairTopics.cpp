#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: pairTopics
// URL: https://codeforces.com/problemset/problem/1324/D
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> A(n), B(n);
    for (int &val : A)
        cin >> val;
    for (int &val : B)
        cin >> val;

    // the rth topic is interesting by A[r] units for teacher and B[r] units for students
    // a pair of topics (i, j) for j > i is called good iff A[i] + A[j] > B[i] + B[j]
    // count the number of good pair of topics

    vector<int> diff(n);
    for (int index = 0; index < n; index++) {
        diff[index] = A[index] - B[index];
    }

    // so, now, a pair of topics (i, j) for j > i is good iff diff[i] > -diff[j] iff diff[i] + diff[j] > 0
    // so, we find the pair of topics (i, j) for j > i such that diff[i] + diff[j] > 0
    sort(diff.begin(), diff.end());
    int cnt = 0;
    for (int left = 0; left < n; left++) {
        int target = 0 - diff[left];
        // in the range [left + 1, end), we find the first element > target
        auto itr = upper_bound(diff.begin() + left + 1, diff.end(), target);
        if (itr == diff.end())
            continue;
        int index = itr - diff.begin();
        // we can form pairs with j = index to n - 1
        cnt += (n - index);
    }

    cout << cnt << endl;

    return 0;
}