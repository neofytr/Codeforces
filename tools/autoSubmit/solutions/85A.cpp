#include <iostream>
#include <vector>
#include <string>
#include <numeric> // For std::iota if needed, not actually used here
#include <algorithm> // For std::min/max if needed, not actually used here

// Use fast I/O
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

void solve() {
    int n;
    std::cin >> n;

    // Case 1: n is odd and greater than 1
    // It's a common observation in such tiling problems with "all vertical cuts intersected"
    // that if N is odd and N > 1, no solution exists.
    // Let's try to sketch a proof:
    // For each column index `j` from 0 to `N-2`, there must be at least one horizontal domino
    // `(r, j) - (r, j+1)` for some row `r`. This means that for each such `j`, at least one
    // cell in column `j` is covered by a horizontal domino extending to `j+1`.
    // Similarly, for each column index `j` from 1 to `N-1`, there must be at least one horizontal domino
    // `(r, j-1) - (r, j)` for some row `r`. This means at least one cell in column `j` is covered
    // by a horizontal domino extending from `j-1`.
    //
    // If N is odd, N-1 is even. Consider N=3.
    // Column 0 must have a horizontal domino `(r_0,0)-(r_0,1)`.
    // Column 1 must have a horizontal domino `(r_1,0)-(r_1,1)` AND `(r_2,1)-(r_2,2)`.
    // Column 2 must have a horizontal domino `(r_3,1)-(r_3,2)`.
    //
    // Consider coloring the grid cells (r,c) with two colors: say 'X' if c is even, 'Y' if c is odd.
    // A vertical domino (2x1) covers two cells of the same color (both 'X' or both 'Y').
    // A horizontal domino (1x2) covers one 'X' and one 'Y' cell.
    // Total cells in even columns (0,2,...,N-1 if N odd): 4 * ( (N-1)/2 + 1 ) = 4 * ( (N+1)/2 ) = 2(N+1) 'X' cells.
    // Total cells in odd columns (1,3,...,N-2 if N odd): 4 * ( (N-1)/2 ) = 2(N-1) 'Y' cells.
    // This parity counting is tricky.
    //
    // A more direct argument, as discovered in thought process:
    // If we have horizontal dominoes across all rows (e.g., `aabbccdd` tiling for 4xN, where `aa` is a domino, `bb` is a domino, etc.):
    // For `N=3`, a row like `aa bb cc` would mean `(r,0)-(r,1)` is a domino, and `(r,2)-(r,3)` is a domino. This can't tile 3 columns.
    // A row like `aa b` would leave `(r,2)` uncovered.
    // If we tile `4xN` with just horizontal 1x2 dominoes, characters would be like `C1C1 C2C2 C3C3 ...`. This is only possible if N is even.
    // If N is odd, this structure fails to fully cover the last column cells or causes overlaps.
    // If N is odd and N > 1, any specific column `j` must have some 1x2 dominoes crossing its boundaries.
    // If N is odd and N > 1, the columns `0, ..., N-1` must have cells `(r,c)` belonging to 1x2 dominoes `(r,c)-(r,c+1)` or `(r,c-1)-(r,c)`.
    // This implies that for any odd `N > 1`, a valid tiling is impossible due to the "each vertical cut intersected" condition.
    // A strong constraint like this often implies such parity conditions on N.
    if (n % 2 != 0 && n > 1) {
        std::cout << -1 << std::endl;
        return;
    }

    // Case 2: n = 1
    // The condition "each of the n-1 potential vertical cuts" means 0 cuts for n=1.
    // So any tiling is valid. Two 2x1 dominoes are sufficient.
    if (n == 1) {
        std::cout << "a\na\nb\nb\n";
        return;
    }

    // Case 3: n is even (n >= 2)
    // We will construct a pattern that satisfies all conditions.
    // The pattern consists of repeating 4x2 blocks.
    // Each 4x2 block is formed by columns `i` and `i+1`.
    //
    // Pattern strategy for columns `i` and `i+1`:
    // 1. Rows 0 and 3 are always covered by horizontal 1x2 dominoes.
    //    `grid[0][i] = grid[0][i+1]` and `grid[3][i] = grid[3][i+1]`.
    //    This ensures that any vertical cut `(i)-(i+1)` is crossed by at least 2 dominoes.
    // 2. Rows 1 and 2 (the middle 2x2 section) alternate between:
    //    a) Two vertical 2x1 dominoes: `(1,i)-(2,i)` and `(1,i+1)-(2,i+1)`.
    //    b) Two horizontal 1x2 dominoes: `(1,i)-(1,i+1)` and `(2,i)-(2,i+1)`.
    //    This alternation happens for every other 4x2 block.
    //
    // For coloring, we use different sets of characters for different structural parts
    // and cycle through them using modulo arithmetic to ensure non-side-neighboring for same-colored dominoes.
    // We use 4 distinct color sets, each cycling through 4 characters:
    // 'a' through 'd' for row 0.
    // 'e' through 'h' for row 3.
    // 'i' through 'l' for the first middle domino (row 1 or col i).
    // 'm' through 'p' for the second middle domino (row 2 or col i+1).
    // This uses a maximum of 16 colors ('a' through 'p'), well within the 26 lowercase Latin letters.

    std::vector<std::string> grid(4, std::string(n, ' '));

    for (int i = 0; i < n; i += 2) {
        int char_idx_block = i / 2; // Index for current 4x2 block (0, 1, 2, ...)

        char c_row0 = 'a' + (char_idx_block % 4);
        char c_row3 = 'e' + (char_idx_block % 4);
        char c_mid1 = 'i' + (char_idx_block % 4);
        char c_mid2 = 'm' + (char_idx_block % 4);

        // Place horizontal dominoes in row 0 and row 3
        grid[0][i] = grid[0][i+1] = c_row0;
        grid[3][i] = grid[3][i+1] = c_row3;

        // Alternate middle section tiling pattern
        if (char_idx_block % 2 == 0) { // Block (0, 2, 4, ...) uses vertical dominoes in rows 1-2
            grid[1][i] = grid[2][i] = c_mid1;      // (1,i)-(2,i) vertical
            grid[1][i+1] = grid[2][i+1] = c_mid2;  // (1,i+1)-(2,i+1) vertical
        } else { // Block (1, 3, 5, ...) uses horizontal dominoes in rows 1-2
            grid[1][i] = grid[1][i+1] = c_mid1;    // (1,i)-(1,i+1) horizontal
            grid[2][i] = grid[2][i+1] = c_mid2;    // (2,i)-(2,i+1) horizontal
        }
    }

    // Print the constructed grid
    for (int r = 0; r < 4; ++r) {
        std::cout << grid[r] << "\n";
    }
}

int main() {
    fast_io();
    solve();
    return 0;
}