#include <bits/stdc++.h>
using namespace std;

// Problem: wordLadder
// URL: https://leetcode.com/problems/word-ladder/description/
// Difficulty: hard
// Tags:
// Strategy:

class Solution {
  private:
    bool isNeighbour(string &u, string &v) {
        int n = (int)u.size();
        int count = 0;
        for (int index = 0; index < n; index++) {
            if (u[index] != v[index])
                count++;
            if (count > 1)
                return false;
        }
        return count == 1;
    }

  public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
        int n = (int)wordList.size();
        vector<vector<int>> graph(n + 1);
        bool found = false;
        int src = -1;
        bool foundEnd = false;
        int end = -1;

        for (int u = 0; u < n; u++) {
            if (wordList[u] == beginWord) {
                found = true;
                src = u;
            }
            if (wordList[u] == endWord) {
                foundEnd = true;
                end = u;
            }
            for (int v = u + 1; v < n; v++) {
                if (isNeighbour(wordList[u], wordList[v])) {
                    graph[u].push_back(v);
                    graph[v].push_back(u);
                }
            }
        }

        if (!found) {
            for (int v = 0; v < n; v++) {
                if (isNeighbour(beginWord, wordList[v])) {
                    graph[n].push_back(v);
                    graph[v].push_back(n); // bidirectional
                }
            }
            src = n;
        }

        if (!foundEnd) {
            return 0;
        }

        vector<bool> vis(n + 1, false);
        vector<int> dist(n + 1, INT_MAX);
        queue<int> que;

        dist[src] = 0;
        vis[src] = true;
        que.push(src);

        while (!que.empty()) {
            int node = que.front();
            que.pop();
            for (int v : graph[node]) {
                if (!vis[v]) {
                    vis[v] = true;
                    dist[v] = dist[node] + 1;
                    que.push(v);
                }
            }
        }

        if (dist[end] == INT_MAX)
            return 0;
        return dist[end] + 1; // add 1 to include the beginWord
    }
};
