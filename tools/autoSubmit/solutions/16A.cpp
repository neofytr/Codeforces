#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> flag(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> flag[i];
    }

    bool is_valid = true;

    // Rule 1: Each horizontal row must contain squares of the same colour.
    for (int i = 0; i < n; ++i) {
        char first_char_in_row = flag[i][0];
        for (int j = 1; j < m; ++j) {
            if (flag[i][j] != first_char_in_row) {
                is_valid = false;
                break; 
            }
        }
        if (!is_valid) {
            break; 
        }
    }

    // Rule 2: The colours of adjacent horizontal rows must be different.
    // This check is only performed if Rule 1 is already satisfied for all rows.
    if (is_valid) {
        for (int i = 0; i < n - 1; ++i) {
            // Compare the first character (which represents the color of the row)
            // of the current row with the next row.
            if (flag[i][0] == flag[i + 1][0]) {
                is_valid = false;
                break;
            }
        }
    }

    if (is_valid) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}