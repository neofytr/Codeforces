#include <bits/stdc++.h>

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s_coord_str, t_coord_str;
    // Read the starting and target chessboard coordinates
    std::cin >> s_coord_str >> t_coord_str;

    // Convert chessboard coordinates to 0-indexed integer coordinates
    // Columns (x-axis): 'a' -> 0, 'b' -> 1, ..., 'h' -> 7
    // Rows (y-axis): '1' -> 0, '2' -> 1, ..., '8' -> 7
    int sx = s_coord_str[0] - 'a';
    int sy = s_coord_str[1] - '1';
    int tx = t_coord_str[0] - 'a';
    int ty = t_coord_str[1] - '1';

    // Initialize the king's current position
    int cur_x = sx;
    int cur_y = sy;

    // Store the sequence of moves
    std::vector<std::string> moves;

    // Continue moving until the king reaches the target square
    while (cur_x != tx || cur_y != ty) {
        std::string move_str = ""; // String to build the current move (e.g., "R", "U", "RU")

        // Determine horizontal movement
        if (cur_x < tx) { // King needs to move right
            move_str += 'R';
            cur_x++;
        } else if (cur_x > tx) { // King needs to move left
            move_str += 'L';
            cur_x--;
        }

        // Determine vertical movement
        if (cur_y < ty) { // King needs to move up
            move_str += 'U';
            cur_y++;
        } else if (cur_y > ty) { // King needs to move down
            move_str += 'D';
            cur_y--;
        }
        
        // Add the determined move to the list
        moves.push_back(move_str);
    }

    // Print the total number of moves
    std::cout << moves.size() << "\n";

    // Print each move in the sequence
    for (const std::string& move : moves) {
        std::cout << move << "\n";
    }

    return 0;
}