#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

#define int long long

// Problem: cowStalls
// URL: https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/C
// Difficulty: hard
// Tags:
// Strategy:

bool canMake(int dist, int k, vector<int> &stalls) {
    // can we make the min distance between the cows atleast dist
    // min distance can be found between two consecutive cows only

    // we start from the first stall and see if we can find a stall that is atleast dist away from it
    // and so on

    int left = k - 1;
    int curr = stalls[0];
    while (left) {
        int toFind = curr + dist;
        // find an index r such that stalls[r] >= toFind

        auto itr = lower_bound(stalls.begin(), stalls.end(), toFind);
        if (itr == stalls.end())
            return false;

        curr = *itr;
        left--;
    }

    return true;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k; // (k <= n)

    vector<int> stalls(n); // sorted in ascending order by default
    for (int &val : stalls)
        cin >> val;

    // we have to arrange the k cows in the n stalls (1 cow per stall)
    // let s is an arrangement of the k cows in the n stalls
    // define min(s) = the minimum distance between any two cows in the arrangement s

    // we are the to find max(min(s), for all possible arrangements s of the k cows in the n stalls)
    // we define a predicate
    // f(x) = 1 if there is an arragement where we can make the minimum distance between the cows atleast x
    //      = 0 otherwise

    // if we cannot make the minimum distance between the cows atleast x, then we cannot make the minimum distance between the cows atleast y for any y >= x
    // thus, it follows that f is monotonic

    // if we get an x such that f(r) = 1 for all r <= x and f(r) = 0 for all r > x
    // then, this means we can make the min distance between the cows atleast x, but not anything > x
    // so, this x is the max(min(s)) we were looking for

    int left = 0;            // this is possible
    int right = 2 * 1e9 + 1; // this is impossible since the stall coordinates are in the range 0 to 10^9

    // since f is monotonic and f(left) = 1 and f(right) = 0, we will get such an x that we described above

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (canMake(mid, k, stalls)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    cout << left << endl;
    return 0;
}