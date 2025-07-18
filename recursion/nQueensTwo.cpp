#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

int config = 0;

void placeQueenInRow(int y, vector<vector<int>> &target, vector<vector<bool>> &board) {
    int n = (int)target.size();
    if (y >= n) {
        config++;
        return;
    }

    // where should we place the queen in the current row?
    for (int x = 0; x < n; x++) {
        if (!target[y][x]) {
            // place the queen here
            target[y][x]++;
            for (int row = y + 1, col = x + 1; row < n && col < n; row++, col++)
                target[row][col]++;
            for (int row = y + 1; row < n; row++)
                target[row][x]++;
            for (int row = y + 1, col = x - 1; row < n && col >= 0; row++, col--)
                target[row][col]++;
            board[y][x] = true;
            placeQueenInRow(y + 1, target, board);
            // backtrack
            board[y][x] = false;
            target[y][x]--;
            for (int row = y + 1, col = x + 1; row < n && col < n; row++, col++)
                target[row][col]--;
            for (int row = y + 1; row < n; row++)
                target[row][x]--;
            for (int row = y + 1, col = x - 1; row < n && col >= 0; row++, col--)
                target[row][col]--;
        }
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> target(n, vector<int>(n, 0));
    vector<vector<bool>> board(n, vector<bool>(n, false));

    // possible[y][x] is true if we can place a queen there; false otherwise
    placeQueenInRow(0, target, board);
    cout << config << endl;
    return EXIT_SUCCESS;
}