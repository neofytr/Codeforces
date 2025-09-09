#include <iostream>

/**
 * @brief Solves a single test case for the Divisibility Problem.
 * * As mathematically proven, for any given positive integer x, y = 2*x is a valid solution.
 * The concatenation x#y becomes divisible by the sum x+y.
 */
void solve() {
    int x;
    std::cin >> x;
    
    // For any given x, y = 2*x is a valid answer.
    int y = 2 * x;
    
    std::cout << y << std::endl;
}

int main() {
    // Fast I/O for performance
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}