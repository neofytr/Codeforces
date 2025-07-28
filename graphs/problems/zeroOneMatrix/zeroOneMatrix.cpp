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

    vector<vector<int>> solveOne(vector<vector<int>> &mat) {
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

    vector<vector<int>> solveTwo(vector<vector<int>> &mat) {
        int m = (int)mat.size();
        int n = (int)mat[0].size();
        int currDist = 0;
        int dr[] = {-1, 0, +1, 0};
        int dc[] = {0, -1, 0, +1};
        vector<vector<int>> dist(m, vector<int>(n, -1));
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        deque<pair<int, int>> que;
        for (int row = 0; row < m; row++) {
            for (int col = 0; col < n; col++) {
                if (!mat[row][col]) {
                    dist[row][col] = 0;
                    que.push_back({row, col}); // initialize all the zeroes in the queue for the bfs
                    visited[row][col] = true;
                }
            }
        }

        // multi-source bfs
        while (!que.empty()) {
            int size = (int)que.size();
            // the nodes visited inside this loop are all at the same level (same distance) from a 0
            while (size--) {
                auto elt = que.front();
                int row = elt.first;
                int col = elt.second;
                que.pop_front();

                // each 1 is visited exactly once (due to the use of visited array)
                // only the shortest distance for a 1 is stored since a 1 is visited exactly once
                // by the bfs, which started from a 0, that reached it the earliest even though all
                // the bfs are at the same distance from a 0; this implies that the shortest distance
                // for each 1 is stored

                // due to multi-source bfs, from each 0, distance is incremented by one for all, then
                // again by one for all, and so on; so, if a source bfs reaches some 1, it will be due to the
                // 0 that is closest to that 1
                dist[row][col] = currDist;
                for (int index = 0; index < 4; index++) {
                    int nrow = row + dr[index];
                    int ncol = col + dc[index];
                    if (nrow >= 0 && nrow < m && ncol >= 0 && ncol < n && !visited[nrow][ncol]) {
                        visited[nrow][ncol] = true;
                        que.push_back({nrow, ncol});
                    }
                }
            }

            currDist++;
        }

        return dist;
    }

  public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat) { return solveTwo(mat); }
};