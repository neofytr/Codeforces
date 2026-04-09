#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int m, n;
    std::cin >> m >> n;

    // The total area of the board is M * N squares.
    // Each domino covers 2 squares.
    // The maximum number of dominoes that can be placed is
    // the total area divided by the area covered by one domino.
    // Integer division correctly handles both cases:
    // If M * N is even, (M * N) / 2 dominoes perfectly tile the board.
    // If M * N is odd, (M * N - 1) / 2 dominoes can be placed, leaving one square uncovered.
    // Integer division (M * N) / 2 automatically computes (M * N - 1) / 2 when M * N is odd.
    std::cout << (m * n) / 2 << std::endl;

    return 0;
}