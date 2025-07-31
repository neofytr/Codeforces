#include <bits/stdc++.h>
#include <cerrno>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

// Problem: wordLadderTwo
// URL: https://leetcode.com/problems/word-ladder-ii/description/
// Difficulty: hard
// Tags:
// Strategy:

class Solution {
  private:
    inline string &numToStr(int index, vector<string> &wordList) { return wordList[index]; }
    inline int strToNum(string &word, unordered_set<string> &dict) {}

  public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
        int wordLen = (int)beginWord.length();
        int n = (int)wordList.size();
        unordered_set<string> dict(wordList.begin(), wordList.end());
        unordered_map<string, int> strToIndex;
        for (int i = 0; i < wordList.size(); i++) {
            strToIndex[wordList[i]] = i;
        }

        if (strToIndex.find(beginWord) == strToIndex.end()) {
            strToIndex[beginWord] = wordList.size();
        }

        if (dict.find(endWord) == dict.end())
            return vector<vector<string>>();

        vector<vector<int>> graph;
        vector<bool> vis(n + 1, false);
        queue<int> que;
        int depth = 1;
        int src = strToIndex[beginWord];
        que.push(src);
        vis[src] = true;
        bool end = false;

        while (!que.empty()) {
            int size = (int)que.size();
            if (end) {
                break;
            }
            while (size--) {
                int index = que.front();
                string node = numToStr(index, wordList);
                string orig = node;
                que.pop();

                if (node == endWord) {
                    end = true;
                }
                for (int i = 0; i < wordLen; i++) {
                    char orig = node[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        node[i] = c;
                        if (dict.count(node) && !vis[strToIndex[node]]) {
                            vis[strToIndex[node]] = true;
                            que.push(strToIndex[node]);
                            graph[index].push_back(strToIndex[node]);
                        }
                    }
                    node[i] = orig;
                }
            }
            depth++;
        }

        return vector<vector<string>>();
    }
};