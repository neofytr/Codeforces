// https:// leetcode.com/problems/course-schedule-ii/
#include <bits/stdc++.h>
#include <queue>
#include <vector>
using namespace std;

class Solution {
  public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> inDegree(numCourses, 0);
        for (auto elt : prerequisites) {
            graph[elt[1]].push_back(elt[0]);
            inDegree[elt[0]]++;
        }

        vector<int> sort;
        queue<int> que;
        for (int node = 0; node < numCourses; node++) {
            if (!inDegree[node])
                que.push(node);
        }

        while (!que.empty()) {
            int node = que.front();
            que.pop();
            sort.push_back(node);

            for (int v : graph[node]) {
                if (!(--inDegree[v])) {
                    que.push(v);
                }
            }
        }

        if (sort.size() != numCourses) {
            return vector<int>();
        } else
            return sort;
    }
};