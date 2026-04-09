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