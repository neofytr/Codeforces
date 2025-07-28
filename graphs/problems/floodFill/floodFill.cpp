#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
  private:
    void traverse(int row, int col, int origColor, int color, vector<vector<int>> &image, vector<vector<bool>> &visited) {
        int m = image.size();
        int n = image[0].size();

        if (row >= m || col >= n) {
            return;
        }
        if (row < 0 || col < 0) {
            return;
        }
        if (visited[row][col] || image[row][col] != origColor) {
            return;
        }

        image[row][col] = color;
        visited[row][col] = true;
        traverse(row + 1, col, origColor, color, image, visited);
        traverse(row - 1, col, origColor, color, image, visited);
        traverse(row, col + 1, origColor, color, image, visited);
        traverse(row, col - 1, origColor, color, image, visited);
    }

  public:
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color) {
        int m = image.size();
        int n = image[0].size();
        int origColor = image[sr][sc];
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        traverse(sr, sc, origColor, color, image, visited);
        return image;
    }
};