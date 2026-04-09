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
