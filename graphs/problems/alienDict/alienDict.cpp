// https://www.geeksforgeeks.org/problems/alien-dictionary/1

#include <bits/stdc++.h>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

class Solution {
  public:
    string findOrder(vector<string> &words) {
        int K = 26;
        vector<vector<int>> graph(K);
        vector<int> inDegree(K, 0);
        unordered_set<int> chars;

        for (string &word : words) {
            for (char ch : word) {
                chars.insert(ch - 'a');
            }
        }

        for (int i = 0; i < (int)words.size() - 1; i++) {
            string &first = words[i];
            string &second = words[i + 1];
            int len = min(first.size(), second.size());

            int j = 0;
            while (j < len && first[j] == second[j])
                j++;

            if (j < len) {
                int u = first[j] - 'a';
                int v = second[j] - 'a';
                graph[u].push_back(v);
                inDegree[v]++;
            } else if (first.size() > second.size()) {
                // prefix violation: invalid input
                return "";
            }
        }

        queue<int> q;
        for (int i = 0; i < K; i++) {
            if (chars.count(i) && !inDegree[i])
                q.push(i);
        }

        string order;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            order.push_back(node + 'a');
            for (int v : graph[node]) {
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        return order.size() == chars.size() ? order : "";
    }
};
