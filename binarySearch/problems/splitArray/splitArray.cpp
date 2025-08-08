#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

#define int long long

// Problem: splitArray
// URL: https://codeforces.com/edu/course/2/lesson/6/3/practice/contest/285083/problem/B
// Difficulty: medium
// Tags:
// Strategy:

bool canDivide(int s, int k, vector<int> &arr) {
    // we are to find if we can get k segments such that sum of all <= s
    int sum = 0;
    int segs = 1;
    for (int r = 0; r < arr.size(); r++) {
        if (arr[r] > s) // we need to ensure that we can atleast fit this element into a segment of his own
            return false;
        sum += arr[r];
        if (sum > s) {
            segs++;
            sum = 0;
            r--;
        }
    }

    return segs <= k;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // we are to divide the array into k non-empty contiguous segments
    // we are to find the sum of all the elements in each of these k segments and choose the maximum one
    // now, from all the possible ways to divide the array into these k non-empty contiguous segments, we are
    // to choose the one with the minimum value of this maximum sum

    // we define a predicate
    // f(s) = 1 if there is a way in which we can divide the array into k such segments such that sum of any of the segments is atmost s
    //      = 0 otherwise

    // it's easy to see that if f(s) = 1, then f(s + 1) = 1 since if we can divide such that sum <= s, we can divide in such a way that sum <= s + 1
    // thus, f is monotonic
    // if f(s) = 1 for all s >= a and f(s) = 0 for all s < a
    // then, we can divide the array into segments such that sum of any segments is atmost a and we cannot divide
    // such that the sum of any segment is atmost r for any r < a
    // then, the sum a will be achieved in some segment and will be the minimum possible maximum sum
    // assume that the sum a isnt achieved in the division corresponding to atmost a sum
    // there is only one possible case then, either all of the segments have sum < a, which isnt' possible
    // since there is no way to divide such that segment sum is atmost r for any r < a
    // and hence we have a contradiction

    int left = 0;          // this is impossible since all the elements are >= 1
    int right = LLONG_MAX; // this is possible

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (canDivide(mid, k, arr))
            right = mid;
        else
            left = mid;
    }

    cout << right << endl;
    return 0;
}