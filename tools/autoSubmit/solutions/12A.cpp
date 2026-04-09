#include <bits/stdc++.h>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main() {
    fast_io();

    std::vector<std::string> grid(3);
    for (int i = 0; i < 3; ++i) {
        std::cin >> grid[i];
    }

    bool symmetric = true;

    // Check for central symmetry with respect to the central button (at index [1][1])
    // A point (r, c) is centrally symmetric to (2-r, 2-c)
    // We iterate through all cells and check if the character at (r,c)
    // is the same as the character at its centrally symmetric counterpart (2-r, 2-c).
    // The central cell (1,1) is symmetric to itself, so grid[1][1] == grid[2-1][2-1]
    // which simplifies to grid[1][1] == grid[1][1], always true.
    // So this loop correctly covers all pairs and the central element.
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (grid[r][c] != grid[2 - r][2 - c]) {
                symmetric = false;
                break; // Found a mismatch, no need to check further
            }
        }
        if (!symmetric) {
            break; // Found a mismatch, exit outer loop
        }
    }

    if (symmetric) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}