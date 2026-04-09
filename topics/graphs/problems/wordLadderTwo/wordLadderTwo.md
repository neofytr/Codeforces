# wordLadderTwo

```markdown
# Word Ladder II Solution Documentation

This document provides a detailed analysis of the provided C++ code, which solves the "Word Ladder II" problem.

## 1. Problem Description

The "Word Ladder II" problem (available at [https://www.geeksforgeeks.org/problems/word-ladder-ii/1](https://www.geeksforgeeks.org/problems/word-ladder-ii/1)) asks us to find *all* the shortest transformation sequences from a `beginWord` to an `endWord`, given a dictionary `wordList`.  Each transformation can only change one letter at a time, and each transformed word must be present in the `wordList`.

## 2. Approach Explanation

The solution employs a combination of Breadth-First Search (BFS) and Depth-First Search (DFS) to find all shortest word ladders.  Here's the breakdown:

1. **BFS to Build a Graph:**  A BFS is performed starting from the `beginWord`.  The BFS constructs a graph where nodes are words, and edges connect words that differ by a single letter and exist in the `wordList`. The `dist` map stores the shortest distance (number of transformations) from the `beginWord` to each word.  Critically, the BFS only adds edges to the graph if the destination node hasn't been visited or is one level below the current node. This ensures we only consider shortest paths.  The `stop` flag is used to optimize the BFS by stopping once the `endWord` is reached, as all shortest paths will be found by then.

2. **DFS to Find All Paths:** After the BFS, a DFS is performed to explore all paths from the `beginWord` to the `endWord` using the graph constructed in the BFS step. The DFS builds the path incrementally and adds it to the `res` vector when the `endWord` is reached. Backtracking is used to explore all possible paths.

## 3. Key Insights and Algorithmic Techniques Used

*   **BFS for Shortest Path:** BFS guarantees finding the shortest paths.  The key is to use the `dist` map to keep track of the distance from the `beginWord`.
*   **Graph Representation for Path Reconstruction:** The `graph` (adjacency list) stores the valid transitions (one-letter changes) between words.  This allows efficient exploration of potential paths during the DFS.
*   **Level-by-Level BFS Exploration:** The outer `while` loop of the BFS ensures we explore words at the same distance from the `beginWord` together. This is essential for only building edges between levels which will give the shortest paths.
*   **DFS for Path Enumeration:** DFS is ideal for exploring all possible paths from a starting node to a target node in a graph. The backtracking mechanism ensures all valid combinations are considered.
*   **Optimization with `stop` flag:** Stop BFS once endWord is reached. Since BFS explores level-by-level, once the endWord is found, we know we have reached the shortest paths. Further BFS won't find shorter paths, so no need to continue exploring other levels.
*   **Custom Hashing:** A custom hash function `StringHash` is defined to improve performance when using `unordered_map` and `unordered_set` with strings.  This can reduce the probability of collisions.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   **BFS:**  O(N \* M \* 26), where N is the number of words in `wordList` and M is the average length of a word. The factor of 26 comes from trying all possible letter substitutions for each position in a word.
    *   **DFS:** In the worst case, where all words are part of shortest paths, the time complexity of DFS can be exponential. However, the BFS step limits the size of the graph, making the DFS more manageable. A very loose upper bound could be O(V^2), where V is the number of vertices in the graph constructed by the BFS, representing the number of accessible nodes using shortest paths.
    *   **Overall:** Dominated by the BFS, so approximately O(N \* M \* 26) + time to copy string vectors in DFS (can vary depending on the size of the result).

*   **Space Complexity:**
    *   **`dict`:** O(N) - Stores all words in the dictionary.
    *   **`graph`:** O(V + E) - Stores the graph where V is the number of words included in shortest paths and E is the number of edges between those words. In the worst-case scenario, this can be close to O(N^2).
    *   **`dist`:** O(V) - Stores the distance from the `beginWord` to each visited word.
    *   **`que`:** O(W) - Stores words in the queue during BFS, W is at most N.
    *   **`path`:** O(L) - Stores current path during DFS, where L is the length of the shortest path from beginWord to endWord.
    *   **`res`:** O(K \* L) - K is the total number of shortest paths of length L.  This can be significant in the worst case.

    *   **Overall:**  O(N + V + E + K\*L), where K is the number of shortest paths, V is the number of vertices in graph (at most N), E is the number of edges in graph (at most N^2).

## 5. Important Code Patterns or Tricks Used

*   **`unordered_set` for efficient lookup:** The `unordered_set` `dict` provides O(1) average-case complexity for checking if a word exists in the dictionary.

*   **`unordered_map` for storing distance and graph:** The `unordered_map` `dist` efficiently stores distances, and the `graph` efficiently represents the adjacency list.

*   **Lambda function for DFS:** The use of a lambda function `dfs` simplifies the code by encapsulating the recursive logic for path traversal.

*   **String manipulation with character replacement:** The code efficiently generates neighboring words by iterating through each character position and trying all possible alphabet substitutions. This is a common pattern for problems involving string transformations.

*   **Custom Hash Function:** Implementing `StringHash` avoids default string hashing, which can be less performant and more prone to collisions. While the provided rolling hash is simple, it can offer improvements over the default.

## 6. Edge Cases Handled

*   **`endWord` not in `wordList`:** The code explicitly checks if the `endWord` is in the `wordList`. If it's not, an empty result is returned.

*   **No path exists:** If the BFS doesn't reach the `endWord` (i.e., `dist.count(endWord)` is false after BFS), it means there's no path from `beginWord` to `endWord`, and an empty result is returned.

*   **Self-loops avoided:** The `if (c == original) continue;` prevents creating a self-loop where a word transforms into itself.

*   **Visited level handling (crucial):** Only explore nodes in the next level.  This ensures you're only finding the shortest paths, critical for the "II" part of the problem statement.

```

## Original Code
```cpp
#include <bits/stdc++.h>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// Problem: wordLadderTwo
// URL: https://www.geeksforgeeks.org/problems/word-ladder-ii/1
// Difficulty: hard
// Tags:
// Strategy:

struct StringHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(const string &s) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        uint64_t hash = 0;
        for (char c : s) {
            hash = hash * 31 + c; // Simple polynomial rolling hash
        }
        return splitmix64(hash + FIXED_RANDOM);
    }
};

class Solution {
  public:
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string> &wordList) {
        int wordLen = beginWord.length();
        unordered_set<string, StringHash> dict(wordList.begin(), wordList.end());
        unordered_map<string, vector<string>, StringHash> graph;
        unordered_map<string, int, StringHash> dist;
        vector<vector<string>> res;

        if (!dict.count(endWord))
            return res;

        dict.insert(beginWord);

        queue<string> que;
        que.push(beginWord);
        dist[beginWord] = 0;
        bool stop = false;

        // we would want all paths from the beginWord to endWord that are the shortest

        // we take into account paths from the current level to the next level; to do this either we set
        // all nodes to visited when we finish a level, or see if a node is a level below and visited (visited during the same level traversal)

        while (!que.empty() && !stop) {
            int size = (int)que.size();
            while (size--) {
                string word = que.front();
                que.pop();

                string temp = word;
                for (int i = 0; i < wordLen; i++) {
                    char original = temp[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == original)
                            continue;
                        temp[i] = c;
                        if (!dict.count(temp))
                            continue;

                        if (!dist.count(temp)) { // we don't explore paths between nodes on the same level (for nodes on the same level, the dist is already set)
                            dist[temp] = dist[word] + 1;
                            que.push(temp);
                            graph[word].push_back(temp);
                        } else if (dist[temp] == dist[word] + 1) { // to build all paths from the current level to the next level (can be shortest)
                            graph[word].push_back(temp);
                        }

                        if (temp == endWord) {
                            stop = true;
                        }
                    }
                    temp[i] = original;
                }
            }
        }

        if (!dist.count(endWord))
            return res;

        vector<string> path;
        function<void(const string &)> dfs = [&](const string &u) {
            path.push_back(u);
            if (u == endWord) {
                res.push_back(path);
            } else {
                for (const string &v : graph[u]) {
                    dfs(v);
                }
            }
            path.pop_back();
        };

        dfs(beginWord);
        return res;
    }
};
```

---
*Documentation generated on 2025-08-01 11:12:00*
