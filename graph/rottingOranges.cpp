#include <bits/stdc++.h>
#include <deque>
#include <utility>
#include <vector>
using namespace std;

#define ROTTEN (2)
#define FRESH (1)

class Solution {
  public:
    int orangesRotting(vector<vector<int>> &grid) {
        int m = (int)grid.size();
        int n = (int)grid[0].size();
        int minutes = 0;
        int freshCount = 0;
        for (int row = 0; row < m; row++) {
            for (int col = 0; col < n; col++) {
                if (grid[row][col] == FRESH) {
                    freshCount++;
                }
            }
        }
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        deque<pair<int, int>> rottenBox;

        while (true) {
            for (int row = 0; row < m; row++) {
                for (int col = 0; col < n; col++) {
                    if (!visited[row][col] && grid[row][col] == ROTTEN) {
                        visited[row][col] = true;
                        if (row > 0 && grid[row - 1][col] == FRESH) {
                            rottenBox.push_back(make_pair(row - 1, col));
                        }
                        if (row < m - 1 && grid[row + 1][col] == FRESH) {
                            rottenBox.push_back(make_pair(row + 1, col));
                        }
                        if (col > 0 && grid[row][col - 1] == FRESH) {
                            rottenBox.push_back(make_pair(row, col - 1));
                        }
                        if (col < n - 1 && grid[row][col + 1] == FRESH) {
                            rottenBox.push_back(make_pair(row, col + 1));
                        }
                    }
                }
            }

            if (rottenBox.empty() && !freshCount)
                break;
            if (rottenBox.empty() && freshCount)
                return -1;

            while (!rottenBox.empty()) {
                auto elt = rottenBox.front();
                rottenBox.pop_front();

                int row = elt.first;
                int col = elt.second;
                grid[row][col] = ROTTEN;
                freshCount--;
            }

            minutes++;
        }

        return minutes;
    }
};