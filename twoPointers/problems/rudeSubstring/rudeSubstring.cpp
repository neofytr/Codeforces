#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: rudeSubstring
// URL: https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/G
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c;
    cin >> n >> c;

    string str;
    cin >> str;

    // rudeness of a string of length k is the number of pairs (i, j) where 0 <= i < j < k for which
    // str[i] = a and str[j] = b

    // a segment [l, r] of the string str is said to be good iff it's rudeness <= c
    // this good property is subsegment monotonic since, if it's true for some segment, it's true for all
    // it's subsegments too

    // for each index 0 <= r < n, we find the maximum length segment [l, r] for l <= r such that its good
    // we then take the maximum of these maximums for each 0 <= r < n to find the maximum length segment of str that is good

    int l = 0, countA = 0, countB = 0;
    int rudeness = 0, maxi = 0;

    for (int r = 0; r < n; r++) {
        if (str[r] == 'a') {
            countA++;
        } else { // 'b'
            countB++;
            rudeness += countA;
        }

        while (l <= r && rudeness > c) {
            if (str[l] == 'a') {
                countA--;
                rudeness -= countB;
            } else if (str[l] == 'b') {
                countB--;
            }
            l++;
        }

        if (r >= l)
            maxi = max(maxi, r - l + 1);
    }
    cout << maxi << "\n";
}