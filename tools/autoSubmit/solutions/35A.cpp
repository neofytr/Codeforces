#include <bits/stdc++.h>

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int ball_position;
    // Read the initial position of the ball (1, 2, or 3).
    std::cin >> ball_position;

    // The problem states there are exactly 3 shuffles.
    for (int i = 0; i < 3; ++i) {
        int cup1_idx, cup2_idx;
        // Read the two cup indexes involved in the current shuffle.
        // These indexes represent the current physical positions of the cups being swapped.
        std::cin >> cup1_idx >> cup2_idx;

        // Check if the ball is currently under cup1_idx.
        if (ball_position == cup1_idx) {
            // If the ball is under cup1_idx, it moves to cup2_idx because cup1_idx is swapped with cup2_idx.
            ball_position = cup2_idx;
        }
        // Otherwise, check if the ball is currently under cup2_idx.
        else if (ball_position == cup2_idx) {
            // If the ball is under cup2_idx, it moves to cup1_idx because cup2_idx is swapped with cup1_idx.
            ball_position = cup1_idx;
        }
        // If the ball is neither under cup1_idx nor cup2_idx, it must be under the third cup,
        // which is not involved in this particular shuffle. So, its position remains unchanged.
    }

    // After all 3 shuffles, print the final position of the ball.
    std::cout << ball_position << std::endl;

    return 0;
}