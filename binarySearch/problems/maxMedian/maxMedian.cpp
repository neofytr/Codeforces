#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: maxMedian
// URL: https://codeforces.com/contest/1201/problem/C
// Difficulty: hard
// Tags:
// Strategy:

bool func(int x, int k, vector<int> &arr, vector<int> &prefix) {
    // we want to see if we can make the median x using atmost k operations
    int n = (int)arr.size();
    int currMedian = arr[n / 2];
    // x is the new median
    // we will find the largest element in the array such that its <= x; say its y
    // we have to increase all the elements from currMedian to y to be equal to atleast x
    // if it can be done in k operations, we return true, or we return false

    int left = -1;
    int right = n;
    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= x)
            left = mid;
        else
            right = mid;
    }

    if (left < n / 2) {
        // we can never make the median x
        return false;
    }

    int count = (min(n - 1, left) - (n / 2) + 1) * x - (prefix[min(n - 1, left) + 1] - prefix[n / 2]);

    return count <= k;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    // n is always odd
    // k is the maximum number of operations we can make

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // we have an array of n integers, with n being odd
    // we can perform the following operation at most k times
    // choose one of the elements from the array (say a) and replace it with a + 1

    // we want to make the median of the array as large as possible using at most k such operations
    // the median of an odd-sized array is the middle element after the array is sorted in non-decreasing order

    // if we cannot make the median x after atmost k operations, we cannot make it x + 1
    // we can binary search on answer then

    sort(arr.begin(), arr.end());
    vector<int> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + arr[i - 1];
    }

    int left = arr[n / 2]; // we can make the median this using atmost k operations

    // get an upper bound
    int x = left;
    while (func(x, k, arr, prefix)) {
        if (x <= 0)
            x++;
        else
            x *= 2;
    }
    int right = x + 1;

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (func(mid, k, arr, prefix))
            left = mid;
        else
            right = mid;
    }

    cout << left << endl;
    return 0;
}