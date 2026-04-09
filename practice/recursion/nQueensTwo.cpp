#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

int offset;
int config = 0;

void placeQueenInRowOptimized(int y, vector<int> &targetColumn, vector<int> &targetDiagnolRight, vector<int> &targetDiagnolLeft) {
    int n = (int)targetColumn.size();
    if (y >= n) {
        config++;
        return;
    }

    // where should we place the queen in the current row?
    for (int x = 0; x < n; x++) {
        if (!targetColumn[x] && !targetDiagnolRight[y - x + offset] && !targetDiagnolLeft[x + y]) {
            // we can place the queen here
            targetColumn[x]++;
            targetDiagnolRight[y - x + offset]++;
            targetDiagnolLeft[x + y]++;
            placeQueenInRowOptimized(y + 1, targetColumn, targetDiagnolRight, targetDiagnolLeft);
            // backtrack
            targetColumn[x]--;
            targetDiagnolRight[y - x + offset]--;
            targetDiagnolLeft[x + y]--;
        }
    }
}

void placeQueenInRow(int y, vector<vector<int>> &target) {
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
            placeQueenInRow(y + 1, target);
            // backtrack
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
    offset = n - 1;

    vector<vector<int>> target(n, vector<int>(n, 0));
    vector<int> targetColumn(n, 0), targetDiagnolLeft(2 * n, 0), targetDiagnolRight(2 * n, 0);

    // placeQueenInRow(0, target);
    placeQueenInRowOptimized(0, targetColumn, targetDiagnolRight, targetDiagnolLeft);
    cout << config << endl;
    return EXIT_SUCCESS;
}