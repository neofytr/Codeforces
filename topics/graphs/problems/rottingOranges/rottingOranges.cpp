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
        int drow[] = {-1, 0, +1, 0};
        int dcol[] = {0, -1, 0, +1};

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

                for (int index = 0; index < 4; index++) {
                    int nrow = row + drow[index];
                    int ncol = col + dcol[index];

                    if (nrow < m && nrow >= 0 && ncol < n && ncol >= 0 && grid[nrow][ncol] == FRESH) {
                        que.push_back({nrow, ncol});
                        // since this pushed elt won't be analyzed until later, it may so happen
                        // that it's pushed again; so, we edit it's metadata
                        grid[nrow][ncol] = ROTTEN;
                        freshCount--;
                        infected = true;
                    }
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