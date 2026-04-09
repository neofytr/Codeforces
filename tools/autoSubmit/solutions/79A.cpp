#include <bits/stdc++.h>

// Function to try and make a move for Ciel
// Ciel maximizes 100-yen coins.
// Returns true if a move was made, false if no move is possible.
bool ciel_move(long long& x, long long& y) {
    // Possible ways to make 220 yen (100-yen coins, 10-yen coins):
    // 1. (2, 2)   -> 200 + 20 = 220 (2 100-yen coins)
    // 2. (1, 12)  -> 100 + 120 = 220 (1 100-yen coin)
    // 3. (0, 22)  -> 0 + 220 = 220 (0 100-yen coins)

    // Ciel prioritizes options with more 100-yen coins.

    // Try Option 1: Take 2 100-yen coins and 2 10-yen coins
    if (x >= 2 && y >= 2) {
        x -= 2;
        y -= 2;
        return true;
    }
    // Try Option 2: Take 1 100-yen coin and 12 10-yen coins
    if (x >= 1 && y >= 12) {
        x -= 1;
        y -= 12;
        return true;
    }
    // Try Option 3: Take 0 100-yen coins and 22 10-yen coins
    if (y >= 22) { // x >= 0 is always true for this option
        y -= 22;
        return true;
    }
    
    return false; // No valid move can be made
}

// Function to try and make a move for Hanako
// Hanako maximizes 10-yen coins.
// Returns true if a move was made, false if no move is possible.
bool hanako_move(long long& x, long long& y) {
    // Possible ways to make 220 yen (100-yen coins, 10-yen coins):
    // 1. (0, 22)  -> 0 + 220 = 220 (22 10-yen coins)
    // 2. (1, 12)  -> 100 + 120 = 220 (12 10-yen coins)
    // 3. (2, 2)   -> 200 + 20 = 220 (2 10-yen coins)

    // Hanako prioritizes options with more 10-yen coins.

    // Try Option 1: Take 0 100-yen coins and 22 10-yen coins
    if (y >= 22) { // x >= 0 is always true for this option
        y -= 22;
        return true;
    }
    // Try Option 2: Take 1 100-yen coin and 12 10-yen coins
    if (x >= 1 && y >= 12) {
        x -= 1;
        y -= 12;
        return true;
    }
    // Try Option 3: Take 2 100-yen coins and 2 10-yen coins
    if (x >= 2 && y >= 2) {
        x -= 2;
        y -= 2;
        return true;
    }
    
    return false; // No valid move can be made
}

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    long long x, y; // x: number of 100-yen coins, y: number of 10-yen coins
    std::cin >> x >> y;

    bool ciel_turn = true; // Ciel takes the first turn

    while (true) {
        if (ciel_turn) {
            // It's Ciel's turn
            if (!ciel_move(x, y)) {
                // Ciel cannot make a valid move, so Ciel loses. Hanako wins.
                std::cout << "Hanako\n";
                return 0;
            }
        } else {
            // It's Hanako's turn
            if (!hanako_move(x, y)) {
                // Hanako cannot make a valid move, so Hanako loses. Ciel wins.
                std::cout << "Ciel\n";
                return 0;
            }
        }
        
        ciel_turn = !ciel_turn; // Switch turn to the other player
    }

    return 0; // Should not be reached
}