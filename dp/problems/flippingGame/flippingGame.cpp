#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: flippingGame
// URL: https://codeforces.com/problemset/problem/327/A
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    int total = 0;
    for (const int val : arr)
        if (val)
            total++;

    vector<int> prefix(n + 1, 0);
    for (int r = 1; r <= n; r++)
        prefix[r] = prefix[r - 1] + (!arr[r - 1]);
    // for any (i, j) where 0 <= i <= j < n, the number of ones in the array will be total + (numOfZerosIn(i, j) - numOfOnes(i, j))
    // ans(i, j) = total + zeroes(i, j) - (j - i + 1 - zeroes(i, j))
    //           = (total - 1) + 2 * zeroes(i, j) + (i - j)
    //           = (total - 1) + 2 *(prefix[j + 1] - prefix[i]) + (i - j)
    //           = total + (2 * prefix[j + 1] - (j + 1)) - (2 * prefix[i] - i)

    // let del[r] = 2*prefix[r] - r for 0 <= r <= n
    // so,
    // ans(i, j) = total + del[j + 1] - del[i] for 0 <= i <= j < n

    // we have to find max(ans(i, j) for 0 <= i <= j < n)

    vector<int> del(n + 1, 0);
    for (int r = 0; r <= n; r++)
        del[r] = 2 * prefix[r] - r;

    int miniDel = del[0];
    int maxi = LLONG_MIN;
    for (int j = 0; j < n; j++) {
        maxi = max(maxi, del[j + 1] - miniDel);
        miniDel = min(miniDel, del[j]);
    }
    cout << maxi + total << endl;
    return 0;
}