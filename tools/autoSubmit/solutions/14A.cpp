#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> grid(n);
    int min_r = n, max_r = -1; 
    int min_c = m, max_c = -1; 

    for (int i = 0; i < n; ++i) {
        std::cin >> grid[i];
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '*') {
                min_r = std::min(min_r, i);
                max_r = std::max(max_r, i);
                min_c = std::min(min_c, j);
                max_c = std::max(max_c, j);
            }
        }
    }
    
    for (int i = min_r; i <= max_r; ++i) {
        for (int j = min_c; j <= max_c; ++j) {
            std::cout << grid[i][j];
        }
        std::cout << "\n";
    }

    return 0;
}