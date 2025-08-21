# cardSubstrings

```markdown
# Documentation for Card Substrings Solution

This document provides a detailed explanation of the provided C++ code solution for the "Card Substrings" problem from Codeforces.

## 1. Problem Description (Inferred)

The problem (available at [https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/F](https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/F)) can be described as follows:

Given a string `str` of length `n` and a string `cards` of length `m`, determine the number of substrings of `str` that can be "made" using the characters available in `cards`.  A substring of `str` can be "made" if for each character `c`, the number of times `c` appears in the substring is less than or equal to the number of times `c` appears in `cards`.

## 2. Approach Explanation

The solution utilizes a sliding window approach to efficiently count the valid substrings. The key idea is to maintain a window `[l, r]` within the string `str` and check if the characters within the window can be formed using the characters in the `cards` string.

Specifically:

1.  **Frequency Counting:** It first calculates the frequency of each character in the `cards` string using an unordered map `freqCards`. This map stores the number of times each character is available.

2.  **Sliding Window:** It then iterates through the `str` string using the right pointer `r` of the sliding window. For each position `r`, it maintains an unordered map `freq` to store the frequency of characters within the current window `[l, r]`.

3.  **Validity Check:** The `isGood` function checks if the current window `[l, r]` is valid.  It iterates through the `freq` map (frequency of characters in the current window) and checks if the count of each character `c` is less than or equal to the count of `c` in `freqCards` (frequency of characters in the `cards` string).

4.  **Window Adjustment:** If the current window `[l, r]` becomes invalid (i.e., `isGood` returns `false`), the left pointer `l` is moved to the right until the window becomes valid again.  This is done by decrementing the frequency of the character at `str[l]` in the `freq` map and incrementing `l`.

5.  **Counting Valid Substrings:** Once a valid window `[l, r]` is found for a given `r`, all substrings ending at `r` and starting at any position between `l` and `r` are also valid due to subsegment monotonicity.  Therefore, we add `(r - l + 1)` to the total count of valid substrings.

## 3. Key Insights and Algorithmic Techniques Used

*   **Sliding Window:** The core algorithmic technique is the sliding window, which efficiently explores all possible substrings.  It allows us to avoid recomputing the frequency of characters for each substring.
*   **Frequency Mapping:** Using `unordered_map` to store and update character frequencies is crucial for efficient counting.
*   **Subsegment Monotonicity:** The problem exhibits subsegment monotonicity, meaning if a segment `[l, r]` is valid, then all its subsegments `[l', r']` where `l <= l' <= r' <= r` are also valid. This is implicitly utilized by adding `(r - l + 1)` to the count, because if the window `[l, r]` is valid, all subsegments ending at `r` are also valid.
*   **Greedy Approach:** The sliding window expands greedily to the right (incrementing `r`) and shrinks from the left (incrementing `l`) only when necessary, maintaining the largest possible valid window ending at `r`.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(n), where n is the length of the string `str`. The right pointer `r` iterates through the string once. The left pointer `l` also iterates through the string at most once. The `isGood` function iterates through the frequency map, which in the worst case, contains all unique characters from `str`. Since the number of unique characters is limited (e.g., 26 for lowercase English letters), this can be considered constant.  Therefore the overall time complexity is dominated by the iterations through `str`, giving O(n).

*   **Space Complexity:** O(m) in the worst case, where m is the number of distinct characters appearing in `cards`. The `freqCards` map stores the frequency of the characters in `cards`. The `freq` map in the sliding window can store at most n distinct characters in the worst case, so in theory, the space complexity could be O(min(n,m)), although in many real-world scenarios, the length of the cards string m will limit the distinct characters appearing in string str.

## 5. Important Code Patterns or Tricks Used

*   **Efficient Frequency Counting:** Using `unordered_map` for frequency counting provides fast lookups and updates.
*   **`ios_base::sync_with_stdio(false); cin.tie(NULL);`:** This optimization disables synchronization between C and C++ streams and unties `cin` and `cout`, significantly improving input/output performance.
*   **`#define int long long`:**  This ensures that integers have a larger range, which prevents integer overflows. It is common practice in competitive programming to use `long long` as the default integer type, especially for problems where intermediate results may become large.
*   **Clarity Through Comments:** The original code has inline comments, which greatly enhances the readability of the solution.

## 6. Any Edge Cases Handled

*   The code implicitly handles the case where the `cards` string might not contain all characters present in the `str` string. The `isGood` function checks if the frequency of each character in the substring is within the bounds specified by `freqCards`. If a character is not present in `cards`, its count in `freqCards` defaults to 0.  This ensures that if a substring contains a character not present in the `cards`, the `isGood` function will correctly identify it as invalid.
*   Empty substrings are not explicitly considered; however, if the string `cards` is empty, the program will still execute correctly. The check `if (l <= r)` will prevent processing empty substrings and will not count any substring as valid in that case.


## Original Code
```cpp
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
```

---
*Documentation generated on 2025-08-21 08:38:40*
