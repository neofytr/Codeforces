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
