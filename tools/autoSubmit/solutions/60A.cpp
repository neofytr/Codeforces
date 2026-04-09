#include <bits/stdc++.h>

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    // Initialize the range of possible boxes where the flakes could be.
    // Initially, flakes could be in any box from 1 to n.
    int min_possible_box = 1;
    int max_possible_box = n;

    for (int k = 0; k < m; ++k) {
        std::string token1, token2, token3;
        int i;
        
        // Read the hint: "To the left of i" or "To the right of i"
        // We only care about the third token ("left" or "right") and the integer i.
        std::cin >> token1 >> token2 >> token3 >> i;

        if (token3 == "left") {
            // Hint: "To the left of i"
            // This implies that the flakes are NOT in box 'i' and NOT in any box to its right.
            // Therefore, the flakes must be in one of the boxes 1, 2, ..., i-1.
            // We update the maximum possible box that can contain the flakes.
            max_possible_box = std::min(max_possible_box, i - 1);
        } else { // token3 == "right"
            // Hint: "To the right of i"
            // This implies that the flakes are NOT in box 'i' and NOT in any box to its left.
            // Therefore, the flakes must be in one of the boxes i+1, i+2, ..., n.
            // We update the minimum possible box that can contain the flakes.
            min_possible_box = std::max(min_possible_box, i + 1);
        }
    }

    // After processing all hints, check for contradictions.
    // If the minimum possible box index is greater than the maximum possible box index,
    // it means there is no box that satisfies all hints simultaneously.
    if (min_possible_box > max_possible_box) {
        std::cout << -1 << std::endl;
    } else {
        // Otherwise, the range [min_possible_box, max_possible_box]
        // represents all boxes that could potentially contain the flakes.
        // The number of boxes in this range is max_possible_box - min_possible_box + 1.
        std::cout << max_possible_box - min_possible_box + 1 << std::endl;
    }

    return 0;
}