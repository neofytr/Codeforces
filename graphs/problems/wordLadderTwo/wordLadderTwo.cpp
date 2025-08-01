#include <bits/stdc++.h>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

// Problem: wordLadderTwo
// URL: https://www.geeksforgeeks.org/problems/word-ladder-ii/1
// Difficulty: hard
// Tags:
// Strategy:

class Solution {
  public:
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string> &wordList) {
        vector<vector<string>> res;
        int wordLen = (int)beginWord.length();
        unordered_set<string> dict(wordList.begin(), wordList.end());
        queue<vector<string>> que;
        bool end = false;

        que.push({beginWord});
        while (!que.empty() && !end) {
            int size = (int)que.size();
            unordered_set<string> level;
            while (size--) {
                vector<string> path = que.front();
                que.pop();
                string word = *path.rbegin();
                string origWord = word;

                for (int i = 0; i < wordLen; i++) {
                    char orig = word[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        word[i] = c;
                        if (!dict.count(word) || word == origWord)
                            continue;
                        level.insert(word);
                        path.push_back(word);
                        que.push(path);
                        if (word == endWord) {
                            res.push_back(path);
                            end = true;
                        }
                        path.pop_back();
                    }
                    word[i] = orig;
                }
            }
            int n = (int)level.size();
            for (string str : level) {
                dict.erase(str);
            }
        }

        return res;
    }
};