#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: cardSubstrings
// URL: https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/F
// Difficulty: hard
// Tags:
// Strategy:

bool isGood(unordered_map<char, int> &freq, unordered_map<char, int> &freqCards) {
    for (auto &[c, x] : freq)
        if (x > freqCards[c])
            return false;
    return true;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    string str, cards;
    cin >> str >> cards;

    // we can make a substring [l, r] of the string iff the number of times each char occurs in the
    // substring is <= the number of times that same char appears in the cards

    // this has subsegment monotonicity; if a segment can be made, then so can its subsegments

    unordered_map<char, int> freqCards;
    for (const char c : cards)
        freqCards[c]++;

    unordered_map<char, int> freq;
    int l = 0;
    int count = 0;
    for (int r = 0; r < n; r++) {
        freq[str[r]]++;
        while (l <= r && !isGood(freq, freqCards))
            freq[str[l++]]--;
        if (l <= r) {
            // we have the largest segment ending at r that is good
            count += (r - l + 1);
        }
    }
    cout << count << endl;
    return 0;
}