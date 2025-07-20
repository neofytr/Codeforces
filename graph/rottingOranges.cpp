// https://leetcode.com/problems/rotting-oranges/description/

#include <bits/stdc++.h>
using namespace std;

#define FRESH 1
#define ROTTEN 2

class Solution {
  public:
    int orangesRotting(vector<vector<int>> &grid) {
        int m = (int)grid.size();
        int n = (int)grid[0].size();
        int minutes = 0;
        int freshCount = 0;
        deque<pair<int, int>> que;

        for (int row = 0; row < m; row++) {
            for (int col = 0; col < n; col++) {
                if (grid[row][col] == FRESH) {
                    freshCount++;
                } else if (grid[row][col] == ROTTEN) {
                    que.push_back({row, col});
                }
            }
        }

        if (!freshCount) {
            // if there are no fresh oranges initially, we are done
            return 0;
        }

        while (!que.empty()) {
            int size = (int)que.size();
            bool infected = false;
            // finish the current level
            while (size--) {
                auto elt = que.front();
                que.pop_front();
                int row = elt.first;
                int col = elt.second;

                if (row > 0 && grid[row - 1][col] == FRESH) {
                    que.push_back({row - 1, col});
                    // since this pushed elt won't be analyzed until later, it may so happen
                    // that it's pushed again; so, we edit it's metadata
                    grid[row - 1][col] = ROTTEN;
                    freshCount--;
                    infected = true;
                }

                if (row < m - 1 && grid[row + 1][col] == FRESH) {
                    que.push_back({row + 1, col});
                    // since this pushed elt won't be analyzed until later, it may so happen
                    // that it's pushed again; so, we edit it's metadata
                    grid[row + 1][col] = ROTTEN;
                    freshCount--;
                    infected = true;
                }

                if (col > 0 && grid[row][col - 1] == FRESH) {
                    que.push_back({row, col - 1});
                    // since this pushed elt won't be analyzed until later, it may so happen
                    // that it's pushed again; so, we edit it's metadata
                    grid[row][col - 1] = ROTTEN;
                    freshCount--;
                    infected = true;
                }

                if (col < n - 1 && grid[row][col + 1] == FRESH) {
                    que.push_back({row, col + 1});
                    // since this pushed elt won't be analyzed until later, it may so happen
                    // that it's pushed again; so, we edit it's metadata
                    grid[row][col + 1] = ROTTEN;
                    freshCount--;
                    infected = true;
                }
            }

            if (infected) {
                // this is so that minutes isn't incremented in the last round when no new
                // fresh oranges are added in the queue
                minutes++;
            }
        }

        if (!freshCount)
            return minutes;
        else
            return -1;
    }
};