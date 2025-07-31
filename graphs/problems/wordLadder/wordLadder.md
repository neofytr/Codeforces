# wordLadder

```markdown
## Word Ladder Solution Documentation

This document provides a comprehensive analysis of the provided C++ code, which solves the "Word Ladder" problem, originally found on [LeetCode](https://leetcode.com/problems/word-ladder/description/).

### 1. Problem Description

Given a `beginWord`, an `endWord`, and a `wordList`, find the length of the shortest transformation sequence from `beginWord` to `endWord`, such that:

1.  Only one letter can be changed at a time.
2.  Each transformed word must exist in the `wordList`.

Return 0 if no such transformation sequence exists.

For example:

```
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]

Output: 5

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.
```

### 2. Approach Explanation

The solution uses a Breadth-First Search (BFS) algorithm to explore the possible word transformations. The algorithm can be summarized as follows:

1. **Initialization:**
   - Store the given `wordList` in an `unordered_set` for efficient word lookup.
   - Check if the `endWord` is present in the `wordList`. If not, return 0 (no solution).
   - Initialize a `queue` to store words to be processed, starting with the `beginWord`.
   - Initialize a `vis` (visited) `unordered_set` to keep track of visited words, preventing cycles.
   - Initialize a `depth` variable to 1, representing the length of the current transformation sequence.

2. **BFS Iteration:**
   - While the `queue` is not empty:
     - Process all words at the current `depth`.
     - For each word in the current level of the BFS:
       - If the current word is equal to the `endWord`, return the current `depth` (solution found).
       - Generate all possible one-letter-different words from the current word.
       - For each generated word:
         - If the generated word exists in the `wordList` and has not been visited:
           - Add the generated word to the `vis` set.
           - Add the generated word to the `queue` for processing in the next level.
     - Increment the `depth` after processing all words at the current level.

3. **No Solution:**
   - If the `queue` becomes empty and the `endWord` is not found, return 0 (no solution).

### 3. Key Insights and Algorithmic Techniques Used

*   **Breadth-First Search (BFS):** BFS guarantees finding the *shortest* path from the `beginWord` to the `endWord`. Each level of the BFS represents one transformation step.
*   **`unordered_set` for Efficient Lookup:** Using an `unordered_set` (`dict`) to store the `wordList` allows for fast `O(1)` average-case lookup of words when generating potential transformations.  Similarly, `vis` is used for efficient checking of visited words.
*   **Generating One-Letter-Different Words:** The code iterates through each character of the current word and tries every possible letter from 'a' to 'z' at that position.  This is the core of the transformation logic.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:** O(M\*N\*26), where:
    *   N is the number of words in `wordList`.
    *   M is the length of the words in `wordList`.  The outer `while (!que.empty())` loop runs at most N times (in the worst case, we visit all words in the wordList). The inner `while (size--)` loop also runs O(N) times in the worst case.  Inside the inner loop, we generate all possible one-letter-different words. Generating these words takes O(M\*26) time (iterating through each position and changing it to all 26 characters). The `dict.count()` and `vis.count()` operations take O(1) on average due to the use of unordered sets.  Therefore, the time complexity is O(N + N * (M * 26)) which simplifies to O(M\*N\*26).
*   **Space Complexity:** O(N), where N is the number of words in `wordList`.
    *   `dict`: Stores the `wordList` as an `unordered_set` (O(N)).
    *   `vis`: Stores visited words (O(N) in the worst case).
    *   `que`: Stores words to be processed in the BFS (O(N) in the worst case).

### 5. Important Code Patterns or Tricks Used

*   **Using `unordered_set` for efficient lookups:** This is a standard technique when you need to quickly check if an element exists in a collection.
*   **Generating all possible transformations:** The nested loops efficiently explore all possible one-letter-different words.  The `orig` variable is used to restore the original character after each transformation attempt.
*   **Standard BFS Implementation:** The code follows the standard BFS template, using a `queue` and a `vis` set to explore the graph level by level.  The `size` variable is used to iterate through all nodes in a single level of the BFS.

### 6. Any Edge Cases Handled

*   **`endWord` not in `wordList`:** The code explicitly checks if the `endWord` is present in the `wordList` before starting the BFS. If it's not there, it returns 0, indicating no possible transformation.
*   **Empty `wordList` or `beginWord` == `endWord`:** The algorithm correctly handles the case where the `wordList` is empty, or if `beginWord` is the same as the `endWord`. In those cases, it will either return 0 or 1 respectively.
*   **No valid transformation sequence:** If the BFS completes without finding the `endWord`, the code returns 0, indicating that no valid transformation sequence exists.
```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;

// Problem: wordLadder
// URL: https://leetcode.com/problems/word-ladder/description/
// Difficulty: hard
// Tags:
// Strategy:

class Solution {
  public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
        int wordLen = (int)beginWord.length();
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (dict.find(endWord) == dict.end())
            return 0;

        unordered_set<string> vis;
        queue<string> que;
        int depth = 1;
        que.push(beginWord);
        vis.insert(beginWord);

        while (!que.empty()) {
            int size = (int)que.size();
            while (size--) {
                string node = que.front();
                que.pop();

                if (node == endWord)
                    return depth;
                for (int i = 0; i < wordLen; i++) {
                    char orig = node[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        node[i] = c;
                        if (dict.count(node) && !vis.count(node)) {
                            vis.insert(node);
                            que.push(node);
                        }
                    }
                    node[i] = orig;
                }
            }
            depth++;
        }

        return 0;
    }
};

```

---
*Documentation generated on 2025-07-31 21:23:13*
