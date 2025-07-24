// https://leetcode.com/problems/course-schedule/description/
#include <bits/stdc++.h>
#include <queue>
#include <vector>
using namespace std;

class Solution {
  public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> inDegree(numCourses, 0);
        for (auto elt : prerequisites) {
            graph[elt[1]].push_back(elt[0]);
            inDegree[elt[0]]++;
        }

        vector<int> topoSort;
        queue<int> que;
        for (int node = 0; node < numCourses; node++) {
            if (!inDegree[node])
                que.push(node);
        }

        while (!que.empty()) {
            int node = que.front();
            que.pop();
            topoSort.push_back(node);

            for (int v : graph[node]) {
                if (!(--inDegree[v])) {
                    que.push(v);
                }
            }
        }

        return topoSort.size() == numCourses;
    }
};