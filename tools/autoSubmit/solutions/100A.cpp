#include <bits/stdc++.h>

int main() {
    // Enable fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k, n1; // Declare variables: n for room side length, k for number of carpets, n1 for carpet side length
    std::cin >> n >> k >> n1; // Read the three integer inputs

    // Calculate the total area of the room.
    // Since the room is a square with side length n, its area is n * n.
    int room_area = n * n;

    // Calculate the total combined area of all carpets.
    // Each carpet is a square with side length n1, so its area is n1 * n1.
    // With k carpets, the total area is k * (n1 * n1).
    int total_carpet_area = k * n1 * n1;

    // Soroush can carpet his room completely if and only if the total area of all carpets
    // is greater than or equal to the area of his room. This is because carpets can be
    // put over each other (overlapping is allowed), simplifying the problem to a
    // straightforward area comparison.
    if (total_carpet_area >= room_area) {
        std::cout << "YES\n"; // Output "YES" if the room can be completely covered
    } else {
        std::cout << "NO\n";  // Output "NO" otherwise
    }

    return 0; // Indicate successful execution
}