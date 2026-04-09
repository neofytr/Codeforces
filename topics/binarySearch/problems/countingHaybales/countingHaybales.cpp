#include <bits/stdc++.h>
using namespace std;

// Problem: countingHaybales
// URL: https://usaco.org/index.php?page=viewproblem2
// Difficulty: easy
// Tags:
// Strategy:

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    sort(arr.begin(), arr.end());
    int a, b;
    while (q--) {
        cin >> a >> b;

        // we need to find the lowest index in the array such that arr[i] >= a

        // we define a function
        // f(x) = 0 if arr[x] < a
        //      = 1 if arr[x] >= a
        // we assume f(-1) = 0 and f(n) = 1
        // we can show that if f(x) = 1, then f(x + 1) = 1 for any n > x >= 0 since the array is sorted
        // then, since f(n) = 1 and f(-1) = 0, there exists an index 0 <= r <= n such that
        // f(x) = 0 for all 0 <= x < r and f(x) = 1 for all n >= x >= r
        // we need to find this r

        int left = -1;
        int right = n;

        // we follow the invariant
        // f(left) = 0;
        // f(right) = 1;

        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (arr[mid] >= a)
                right = mid;
            else
                left = mid;
        }

        if (right == n) {
            // all the elements in the array are < a
            cout << 0 << endl;
            continue;
        }

        int indexA = right;

        left = -1;
        right = n;

        // a <= b
        // we need to find the maximum index r such that arr[r] <= b
        // arr[left] <= b
        // arr[right] > b

        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (arr[mid] <= b)
                left = mid;
            else
                right = mid;
        }

        if (left == -1) {
            // all the elements in arr are > b
            cout << 0 << endl;
        }

        int indexB = left;
        cout << indexB - indexA + 1 << endl;
    }
    return 0;
}