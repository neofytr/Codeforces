#include <bits/stdc++.h>

int main() {
    // Enable fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Number of walruses
    int m; // Initial number of chips the presenter has

    std::cin >> n >> m;

    // Calculate the total number of chips required for one full round
    // (from walrus 1 needing 1 chip up to walrus n needing n chips)
    // This is the sum of an arithmetic series: 1 + 2 + ... + n = n * (n + 1) / 2
    int chips_for_full_round = n * (n + 1) / 2;

    // If the presenter has enough chips for one or more full rounds,
    // we can skip these full rounds by taking the modulo of m with chips_for_full_round.
    // This efficiently handles cases where m is very large, reducing it to a value
    // less than a full round's cost, or 0 if it's an exact multiple.
    if (m >= chips_for_full_round) {
        m %= chips_for_full_round;
    }

    // Now, m represents the chips remaining after completing all possible full rounds.
    // Simulate the process walrus by walrus for these remaining chips.
    int current_walrus = 1; // Start with walrus number 1

    while (true) {
        int chips_needed = current_walrus; // Walrus 'current_walrus' needs 'current_walrus' chips

        if (m < chips_needed) {
            // If the presenter doesn't have enough chips for the current walrus,
            // the process ends. The presenter keeps the remaining 'm' chips.
            std::cout << m << std::endl;
            break; // Exit the loop
        } else {
            // The presenter has enough chips. Give chips_needed to the current walrus.
            m -= chips_needed;

            // Move to the next walrus in clockwise order
            current_walrus++;
            if (current_walrus > n) {
                // If we've passed walrus n, cycle back to walrus 1.
                current_walrus = 1;
            }
        }
    }

    return 0;
}