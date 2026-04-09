#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::vector<std::string> board(8);
    for (int i = 0; i < 8; ++i) {
        std::cin >> board[i];
    }

    int strokes = 0;

    // First, count strokes for full black rows.
    // If a row is entirely 'B', it's optimal to paint that row (1 stroke) rather than
    // paint all 8 columns to cover its cells (8 strokes), unless all 8 rows are painted.
    for (int i = 0; i < 8; ++i) {
        bool all_b_in_row = true;
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] == 'W') {
                all_b_in_row = false;
                break;
            }
        }
        if (all_b_in_row) {
            strokes++;
        }
    }

    // If all 8 rows were found to be entirely 'B', it means the whole board is 'B'.
    // In this case, painting all 8 rows is the minimum number of strokes (8).
    // No columns need to be painted separately as all cells are already covered.
    if (strokes == 8) {
        std::cout << 8 << std::endl;
        return 0;
    }

    // If not all rows were entirely 'B' (i.e., strokes < 8), then there's at least one row
    // that contains a 'W' and thus cannot be painted.
    // For any 'B' square (r, c) in such a row, it must be covered by painting column c.
    // Based on the problem guarantee ("client's requirements can be fulfilled"),
    // if a square (r, c) is 'B' and row r is not entirely 'B', then column c *must* be entirely 'B'.
    // Therefore, any column that is entirely 'B' needs to be painted, unless all rows were already painted (which is handled above).
    for (int j = 0; j < 8; ++j) {
        bool all_b_in_col = true;
        for (int i = 0; i < 8; ++i) {
            if (board[i][j] == 'W') {
                all_b_in_col = false;
                break;
            }
        }
        if (all_b_in_col) {
            strokes++;
        }
    }

    std::cout << strokes << std::endl;

    return 0;
}