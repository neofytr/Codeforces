#include <bits/stdc++.h>
#include <deque>
#include <vector>
using namespace std;

class Solution {
  private:
    int distanceToNearestZero(int row, int col, vector<vector<int>> &mat) {
        int m = (int)mat.size();
        int n = (int)mat[0].size();
        int dist = 0;
        deque<pair<int, int>> que;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        visited[row][col] = true;
        que.push_back({row, col});

        while (!que.empty()) {
            int size = (int)que.size();
            while (size--) {
                auto elt = que.front();
                int r = elt.first;
                int c = elt.second;
                que.pop_front();

                if (!mat[r][c])
                    return dist;

                if (r > 0) {
                    que.push_back({r - 1, c});
                    visited[r - 1][c] = true;
                }

                if (r < m - 1) {
                    que.push_back({r + 1, c});
                    visited[r + 1][c] = true;
                }

                if (c > 0) {
                    que.push_back({r, c - 1});
                    visited[r][c - 1] = true;
                }

                if (c < n - 1) {
                    que.push_back({r, c + 1});
                    visited[r][c + 1] = true;
                }
            }
            dist++;
        }

        return dist;
    }

  public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
        int m = (int)mat.size();
        int n = (int)mat[0].size();
        vector<vector<int>> output(m, vector<int>(n));

        for (int row = 0; row < m; row++) {
            for (int col = 0; col < n; col++) {
                output[row][col] = distanceToNearestZero(row, col, mat);
            }
        }

        return output;
    }
};