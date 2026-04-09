#include <bits/stdc++.h>

int main() {
    // Enable fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    int current_child = 1; // Child 1 starts with the ball

    // The game involves n-1 throws
    for (int k = 1; k <= n - 1; ++k) {
        // Calculate the next child who receives the ball
        // current_child is 1-indexed (1 to n).
        // To use modulo arithmetic correctly, convert to 0-indexed (0 to n-1): (current_child - 1)
        // Add k positions (the current throw distance): (current_child - 1 + k)
        // Apply modulo n to wrap around the circle: (current_child - 1 + k) % n
        // Convert back to 1-indexed: ((current_child - 1 + k) % n) + 1
        int next_child = ((current_child - 1 + k) % n) + 1;
        
        // Print the child number
        std::cout << next_child;

        // Print a space if it's not the last number
        if (k < n - 1) {
            std::cout << " ";
        }
        
        // Update the current child holding the ball for the next throw
        current_child = next_child;
    }

    // Print a newline at the end of the output
    std::cout << std::endl;

    return 0;
}