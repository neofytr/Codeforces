# wordLadder

```markdown
## Word Ladder Problem Documentation

### 1. Problem Description

The problem, as indicated by the code comments and URL (https://leetcode.com/problems/word-ladder/description/), is the "Word Ladder" problem.  Given a `beginWord`, an `endWord`, and a `wordList`, find the length of the shortest transformation sequence from `beginWord` to `endWord` such that:

1.  Only one letter can be changed at a time.
2.  Each transformed word must exist in the `wordList`.  The `beginWord` is not required to be in the `wordList`.

Return 0 if no such transformation sequence exists.

### 2. Approach Explanation

The solution uses a Breadth-First Search (BFS) algorithm to find the shortest transformation sequence. The basic idea is to treat each word as a node in a graph, where an edge exists between two words if they differ by only one letter. The algorithm starts at the `beginWord` and explores the graph layer by layer until it reaches the `endWord`. The depth of the search represents the number of transformations required.

Specifically, the algorithm performs the following steps:

1.  **Initialization:**
    *   Create an unordered set `list` from the given `wordList` for efficient word lookups.
    *   Add the `beginWord` to the `list` for easier processing later.
    *   Check if the `endWord` is in the `wordList`. If not, return 0, as a transformation is impossible.
    *   Initialize a queue `que` with the `beginWord`.
    *   Initialize `depth` to 1, representing the initial word in the sequence.

2.  **BFS Traversal:**
    *   While the queue is not empty:
        *   Get the size of the current level in the BFS.
        *   Iterate through all nodes in the current level:
            *   Dequeue a word `node` from the queue.
            *   If the `node` is equal to the `endWord`, return the current `depth`.
            *   For each character in the `node`:
                *   Try changing the character to every possible letter from 'a' to 'z'.
                *   If the modified word exists in the `list`:
                    *   Remove the modified word from the `list` to avoid revisiting it. This prevents cycles and ensures that the shortest path is found first.
                    *   Enqueue the modified word.
                *   Restore the original character.

3.  **No Solution:**
    *   If the queue becomes empty before reaching the `endWord`, it means there is no transformation sequence. Return 0.

### 3. Key Insights and Algorithmic Techniques Used

*   **Breadth-First Search (BFS):** BFS is crucial for finding the *shortest* transformation sequence. BFS explores the graph level by level, so the first time the `endWord` is encountered, it's guaranteed to be the shortest path.
*   **Unordered Set for Efficient Lookup:**  Using an `unordered_set` (hash set) for the `wordList` allows for constant-time average-case complexity for checking if a word exists and for erasing words. This is much more efficient than searching a vector linearly.
*   **Backtracking (Implicit):** The inner loop that tries all possible character replacements effectively uses a form of backtracking. It systematically explores all possible one-letter changes, and when a valid neighbor is found, it continues the search from that neighbor. When no valid neighbor is found, it restores the original character and explores other possibilities.
*   **Avoiding Cycles:** Removing the visited words from the `list` is a critical optimization. It prevents the algorithm from getting stuck in cycles, ensuring that the shortest path is found and the algorithm terminates. Without this, the time complexity could become much worse, and the algorithm might not even terminate.

### 4. Time and Space Complexity Analysis

*   **Time Complexity:**  O(M\*N\*26), where:
    *   N is the length of the wordList
    *   M is the length of each word.
    The outer while loop (BFS) can iterate over, at most, all the words in the `wordList`. Inside the inner loops, each word of length `M` is mutated through 26 possibilities for each character.
*   **Space Complexity:** O(N), where N is the number of words in the `wordList`. This is due to the space used by the `unordered_set` and the queue. In the worst case, the queue can contain all the words in the `wordList`.

### 5. Important Code Patterns or Tricks Used

*   **In-place Character Replacement and Restoration:**  The code efficiently explores all possible one-letter changes by replacing a character, checking if the new word is valid, and then restoring the original character. This avoids the need to create a new word object for each potential change.
*   **Using Size of Queue for Level Tracking:** The `size` variable captures the number of nodes at each level of the BFS, allowing the algorithm to accurately track the transformation depth.
*   **Removing Visited Words from the List:** The crucial step of removing visited words from the `list` to avoid cycles.

### 6. Any Edge Cases Handled

*   **`endWord` Not in `wordList`:** The code explicitly checks if the `endWord` is present in the `wordList` before starting the BFS. If it's not, it returns 0, indicating that no transformation sequence is possible.
*   **No Transformation Possible:** If the BFS completes without finding the `endWord`, the code returns 0, indicating that no transformation sequence exists.
*   **Implicitly Handled Empty `wordList`:** If `wordList` is empty and `beginWord` == `endWord`, the set `list` contains only `beginWord`, which will be `endWord` if they are same, thus returning 1. If the `beginWord` != `endWord` then `list` will contain only `beginWord`, and `endWord` check will return `false` and the solution returns 0.

```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <queue>
#include <string>
#include <unordered_set>
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
        int wordLength = (int)beginWord.length();
        unordered_set<string> list(wordList.begin(), wordList.end());

        if (!list.count(endWord))
            return 0;
        list.insert(beginWord);

        int depth = 1;
        queue<string> que;
        que.push(beginWord);

        while (!que.empty()) {
            int size = (int)que.size();
            while (size--) {
                string node = que.front();
                que.pop();
                if (node == endWord)
                    return depth;

                for (int i = 0; i < wordLength; i++) {
                    char orig = node[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        node[i] = c;
                        if (list.count(node)) {
                            list.erase(node);
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
*Documentation generated on 2025-07-31 21:32:35*
