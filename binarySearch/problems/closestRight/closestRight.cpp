#include <bits/stdc++.h>
using namespace std;

// Problem: closestRight
// URL: https://codeforces.com/edu/course/2/lesson/6/1/practice/contest/283911/problem/C
// Difficulty: easy
// Tags:
// Strategy:

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    int x;
    while (k--) {
        cin >> x;
        int left = -1; // arr[left] < x
        int right = n; // arr[right] >= x

        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (arr[mid] < x)
                left = mid;
            else
                right = mid;
        }

        if (right == n) {
            // all elements in the array are < x
            cout << n + 1 << endl;
            ;
        } else {
            cout << right + 1 << endl;
        }
    }
    return 0;
}