#include <bits/stdc++.h>
#include <vector>
using namespace std;

void subArraySum() {
    int n, x;
    cin >> n >> x;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // all the elements of the array are non-negative
    // we want to find the number of subarrays of arr that have their sum = x
    int cnt = 0;
    int left = 0, right = 0;
    int sum = 0;
    while (left < n) {
        while (right < n && sum < x) {
            sum += arr[right++];
        }

        if (sum == x) {
            // [left, right - 1] is one such subarray
            cnt++;
        }

        sum -= arr[left++];
    }

    cout << cnt << endl;
}

int main() {
    // iterating two monotonic pointers across an array to search for a pair of indices satisfying
    // some condition in linear time

    // In two pointers method, two pointers are used to iterate through the array values
    // Both pointers can move to one direction only, which ensures that the algorithm works efficiently

    // The two pointers method iterates two pointers across the array, to track the start and end of an interval
    // , or two values in a sorted array that we are currently checking
    // Both pointers are monotonic; meaning each pointer starts at one end of the array and only move in one direction

    // Subarray sum
    subArraySum();
}

// Let n >= 2
// Let x1, x2, ..., xn be the sequence S
// Let [l, r] denote the subsequence xl, ..., xr where 1 <= l <= r <= n
// Let f is a binary predicate defined on any subsequence [l, r] for 1 <= l <= r <= n

// f is subsegment monotonic iff
// (f is true on [l, r] -> f is true on any [x, y] such that l <= x <= y <= r)
// f is supersegment monotonic iff 
// (f is true on [l, r] -> f is true on any [x, y] such that 1 <= x <= l <= r <= y <= n)

// Let f is subsegment monotonic
// We need to find the largest subsequence of S such that f is true
// To accomplish this, we find the largest subsequence of S ending at r such that f is true, for all 1 <= r <= n
//, and then take the maximum of all of them

bool f(int l, int r) {
    return true;
}

void subseq() {
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    int l = 1;
    for (int r = 1; r <= n; r++) {
        // add arr[r] to the current subsequence
        while (l <= r && !f(l, r)) {
            // remove arr[l] from the subsequence
            l++;
        }

        if (l <= r) // the current subsequence is the largest subsequence of S ending at r such that f is true
    }
}

// Let f is supersegment monotonic
// We need to find the smallest subsequence of S such that f is true
// To accomplish this, we find the smallest subsequence of S ending at r for which f is true, and then
// take a minimum of all of them

void superseg() {
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    int l = 1;
    for (int r = 1; r <= n; r++) {
        // add arr[r] to the current subsequence

        while (l <= r && f(l, r)) {
            // remove arr[l] from the current subsequence
            l++;
        }

        if (l >= 2) // [l - 1, r] is the smallest subsequence ending at r for which f is true
    }
}

// You can convert a binary search into a two-pointer technique when:
// The problem involves two sorted sequences (or one sorted sequence used twice) and 
// you need to find pairs (or subsets) whose relationship is monotonic with respect to one or both pointers
// If moving one pointer in a particular direction causes the condition you're testing to move monotonically (non-increasing
// or non-decreasing), then you can replace multiple binary searches with a single two-pointer linear scan

// Both binary search and two pointers exploit monotonicity, but in slightly different ways
// 1. Binary Search
// The monotonicity is in one variable and the algorithm halves the search space each time O(log(n))
// 2. Two pointers
// The monotonicity is in two variables (l and r) and the algorithm moves each pointer linearly (O(n + m))

// So, if a problem has a monotonic relationship involving two sorted indices or arrays, then we can
// often replace a binary search with two pointers

// We can replace binary search with two pointers when:
// As one pointer moves in one direction, the value or condition you're testing moves monotonically 
// That means, you can determine which pointer to move next without restarting a binary search next time

// If you ever write a loop like:

for (int i = 0; i < n; i++) {
    // for each a[i], do binary search for something in b
}

// and both a and b are sorted, ask yourself:
// Does the search index in b only move in one direction as i increases?
// If yes, then we can replace binary search with a linear pointer movement

// Example:

// binary search
void findBin() {
    int n, m, x;
    cin >> n >> m >> x;

    // a and b are guaranteed to be sorted in non-decreasing order and have distinct elements
    vector<int> a(n + 1), b(m + 1);
    for (int r = 1; r <= n; r++)
        cin >> a[r];
    for (int r = 1; r <= m; r++)
        cin >> b[r];

    // Find number of pairs (i, j) where 1 <= i <= n and 1 <= j <= m such that a[i] + b[j] = x
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        int target = x - a[i];
        if (binary_search(b.begin() + 1, b.end(), target))
            cnt++;
    }
    cout << cnt << endl;
}

// two pointers
void find() {
    int n, m, x;
    cin >> n >> m >> x;

    // a and b are guaranteed to be sorted in non-decreasing order and have distinct elements
    vector<int> a(n + 1), b(m + 1);
    for (int r = 1; r <= n; r++)
        cin >> a[r];
    for (int r = 1; r <= m; r++)
        cin >> b[r];

    // Find number of pairs (i, j) where 1 <= i <= n and 1 <= j <= m such that a[i] + b[j] = x
    int cnt = 0;
    int i = 1, j = m;
    while (i <= n && j >= 1) {
        if (b[j] > x - a[i])
            j--;
        else if (b[j] < x - a[i])
            i++;
        else if (b[j] == x - a[i])
            cout << i << " " << j << endl, cnt++, j--, i++;
    }

    cout << cnt << endl;
}

// If the pointer i moved forward, then the binary search answer pointer (j) moves always backwards
// since a[i] + b[j] = constant = x and increasing i increases a[i] so b[j] has to decrease and hence j has to
// decrease too (all this because the arrays are sorted in strictly increasing order).

// We replaced binary search with a linear scan because the sum if monotonic:
// 1. increasing i increases sum
// 2. decreasing j decreases sum