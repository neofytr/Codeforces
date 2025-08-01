# wordLadderTwo

```markdown
# Word Ladder II Problem Documentation

## 1. Problem Description

The problem, "Word Ladder II," is a variation of the classic Word Ladder problem. Given a `beginWord`, an `endWord`, and a dictionary `wordList`, the goal is to find *all* shortest transformation sequences from `beginWord` to `endWord` such that:

*   Only one letter can be changed at a time.
*   Each transformed word must exist in the `wordList`.  The `beginWord` itself is not necessarily in the word list initially, but can be added.
*   Return an empty list if no such transformation sequence exists.

The problem is available at [https://www.geeksforgeeks.org/problems/word-ladder-ii/1](https://www.geeksforgeeks.org/problems/word-ladder-ii/1).

## 2. Approach Explanation

The solution uses a combination of Breadth-First Search (BFS) and Depth-First Search (DFS) to find all shortest transformation sequences.

1.  **BFS (Graph Construction):**
    *   The BFS constructs a directed graph where nodes represent words in the dictionary and edges connect words that differ by only one letter.
    *   The BFS also calculates the shortest distance (number of transformations) from the `beginWord` to each word in the dictionary. This distance is stored in the `dist` map.  This distance is crucial for only exploring shortest paths later during DFS.
    *   The graph is represented by an `unordered_map` named `graph`. The keys are words, and the values are vectors of strings representing the words that can be reached from that word in one transformation and are on the next level/distance.
    *   Importantly, the BFS explores levels. It iterates through all nodes on the current level before moving to the next level. This ensures we find the shortest distance to each node.
    *   The `stop` variable prevents further BFS exploration once the `endWord` has been reached, as any further exploration could only find longer paths.

2.  **DFS (Path Finding):**
    *   After the graph is constructed by BFS, the DFS explores all paths from the `beginWord` to the `endWord` using the graph constructed in the BFS stage.
    *   The DFS only explores paths that follow the shortest path established during the BFS stage.  The graph only contains edges between words at consecutive distances, ensuring only shortest paths are explored during DFS.
    *   The DFS maintains a `path` vector to track the current sequence of words being explored. When the `endWord` is reached, the `path` is added to the `res` vector, representing a valid transformation sequence.
    *   Backtracking is employed by popping the last word from the `path` after exploring all paths from it.

## 3. Key Insights and Algorithmic Techniques Used

*   **BFS for Shortest Path:** BFS is used to determine the shortest path because it explores the graph level by level, ensuring that the first time a node is visited, it is reached through the shortest possible path.
*   **Graph Representation:**  The adjacency list representation using an `unordered_map` effectively stores the possible transformations from each word.  The keys are the words and values are the words reachable from them in one transformation.
*   **Distance Tracking:** The `dist` map stores the shortest distance from the `beginWord` to each reachable word. This is essential for ensuring that only the shortest transformation sequences are considered during the DFS phase.
*   **DFS for Path Enumeration:** DFS is employed to enumerate all possible paths from the `beginWord` to the `endWord` while respecting the shortest path constraint.
*   **Optimization - Level-by-Level BFS:** The BFS processes the queue level-by-level by using an inner loop `while (size--)`. This prevents revisiting nodes on the same level in the graph, ensuring that the shortest distance to each word is calculated correctly.
*   **Early Stopping:** The `stop` variable efficiently halts the BFS once `endWord` is reached as it means any further search can only produce non-shortest paths.

## 4. Time and Space Complexity Analysis

*   **Time Complexity:**
    *   **BFS:** O(V \* L \* 26), where V is the number of words in the dictionary (and `beginWord`) and L is the length of the word. In the worst case, each word can be transformed into L \* 26 other words.  The set operations add another log(V) factor in principle, but this is often negligible compared to the L\*26 factor. The main loop for BFS could be considered O(V) amortized, as each word is added and removed a small constant number of times.
    *   **DFS:** In the worst-case scenario, all possible paths could lead to the `endWord`, and we need to traverse all of them.  The complexity in this scenario would be exponential to the path length.  However, due to the BFS step, only *shortest* paths are traversed during DFS.  The DFS could be approximated by O(V*E) (visiting nodes in graph V and edges E), but given that E <= VL (maximum number of edges from one node V * path length L), and L is bounded by V, then the DFS complexity can be approximated as O(V^3) for densely connected graphs. More generally, it depends on how many shortest paths exist.
    *   **Overall:**  Dominated by DFS in the worst case if there are many shortest paths. In typical cases, it's close to O(V \* L \* 26 + V^3), but closer to  O(V \* L \* 26) or O(V\*V\*L) if the number of shortest paths is small.  The graph construction is likely to be the major factor in typical scenarios.
*   **Space Complexity:**
    *   `dict`: O(V), where V is the number of words in the dictionary (and `beginWord`).
    *   `graph`: O(V \* L) in the worst case.  If the graph is a fully connected graph, each node could have almost V neighbors, but due to the single letter difference constraint, it's closer to V * L.
    *   `dist`: O(V) stores the distance to each reachable word.
    *   `queue`: O(V) at most, containing all nodes at the current level.
    *   `path`: O(L), where L is the length of the shortest path.
    *   `res`:  In the worst case, it can contain all possible paths, but in most cases, it will be far fewer paths.  Its space complexity could be O(P * L) where P is the number of possible shortest paths.
    *   **Overall:** O(V \* L + P * L). The dictionary `dict` dominates the space complexity initially, followed by the graph and `res` storing the results. If P is large, `res` could be the dominant factor.

## 5. Important Code Patterns or Tricks Used

*   **String Hashing:** A custom `StringHash` struct with `splitmix64` is used for the `unordered_set` and `unordered_map` to improve hashing performance and reduce the likelihood of collisions. This can be essential for large dictionaries.
*   **Level-by-Level BFS:** The BFS processes the queue level-by-level to guarantee that the shortest distance is found correctly.
*   **Graph Construction during BFS:** The graph is built during the BFS, which avoids the need for a separate graph construction step and integrates distance calculation with graph building.
*   **Using function<void(const string &)> for DFS:** Using `std::function` creates a generic lambda that takes the current string and allows for an easy to implement recursive DFS.

## 6. Edge Cases Handled

*   **`endWord` Not in `wordList`:** The code checks if the `endWord` is present in the `wordList` before starting the BFS. If not, an empty vector is returned, preventing an infinite loop.
*   **No Path Exists:** If the BFS completes without finding the `endWord` (i.e., `dist.count(endWord)` is false), it means there is no path from the `beginWord` to the `endWord`, and an empty vector is returned.
*   **Self-Loops:** The code explicitly avoids considering self-loops in the transformation process by skipping transformations where the character is unchanged (`if (c == original) continue;`).
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
*Documentation generated on 2025-08-01 11:01:43*
