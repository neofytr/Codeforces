#include <bits/stdc++.h>
#include <cstdlib>
#include <numeric>
#include <vector>
using namespace std;

#define int long long

// Problem: books
// URL: https://codeforces.com/problemset/problem/279/B
// Difficulty: medium
// Tags:
// Strategy:

bool canRead(int x, int t, vector<int> &arr) {
    int n = (int)arr.size();
    // can he read atleast x books in time t?
    // this is possible iff there is a subarray [l, r] of arr such that summation from i = l to r of arr[i] <= t and l - r + 1 >= x

    int sum = 0;
    int left = 0;
    int right = 0;

    while (right < n) {
        while (right < n && sum + arr[right] <= t) {
            sum += arr[right++];
        }

        if (right - left >= x)
            return true;

        sum -= arr[left++];
    }

    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    cin >> n >> t;
    vector<int> arr(n);
    for (int &val : arr) {
        cin >> val;
    }
    // valera has t free minutes to read books
    // he took n books to the library
    // he takes arr(r) minutes to read the rth book
    // he chooses an arbitrary book r and reads the books one by one, first r, then r + 1, and
    // so on until either he runs out of time or reads the last book
    // he reads each book completely before starting the next one
    // he starts reading a book only when he has enough time to finish it

    // what is the maximum number of books he can read?

    // if he cannot read atleast x books, he cannot read atleat x + 1 books
    int left = 0; // he can read zero books
    int total = accumulate(arr.begin(), arr.end(), 0LL);
    if (total <= t) {
        // he can read all the books
        cout << n << endl;
        return EXIT_SUCCESS;
    }
    int right = n; // he cannot read all the books

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (canRead(mid, t, arr))
            left = mid;
        else
            right = mid;
    }

    cout << left << endl;
    return 0;
}