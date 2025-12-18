#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

// Fast I/O
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

int N, M;
char initial_grid[30][30];
bool is_covered[30][30]; // True if cell is part of a chip

// Stores {char_id -> {{r1,c1}, {r2,c2}}}
std::map<char, std::pair<std::pair<int, int>, std::pair<int, int>>> chip_coords;
// Stores { {r,c} -> char_id } for cells covered by chips
std::map<std::pair<int, int>, char> cell_to_chip_char;
// Stores list of identified 2x2 squares (top-left corners). There will be 14 of these.
std::vector<std::pair<int, int>> squares;
// Stores { {r,c} -> square_idx } for cells within chips
std::map<std::pair<int, int>, int> cell_to_square_idx;

// Backtracking state
int digit_counts[7]; // How many times each digit 0-6 is used for squares (max 2 for each)
int assigned_square_values[14]; // Digit assigned to squares[i]
std::pair<int, int> assigned_chip_dominoes[28]; // Stores {d1,d2} for each chip (indexed by char_to_int), {-1,-1} if not yet determined
bool domino_types_used[7][7]; // True if domino {d1,d2} (min/max) is currently assigned to any chip
int chip_for_domino[7][7]; // Stores chip_int_id for domino {d1,d2}, or -1 if not assigned

long long total_ways = 0;
char final_grid_result[30][30]; // Stores the grid for the first found solution
bool first_solution_found = false;

// Helper to convert char ('a'-'z', 'A','B') to int (0-27)
int char_to_int(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    return c - 'A' + 26;
}

// Helper to get a canonical domino pair {min_val, max_val}
std::pair<int, int> get_domino_pair(int v1, int v2) {
    return {std::min(v1, v2), std::max(v1, v2)};
}

void solve(int square_idx) {
    if (square_idx == 14) { // All 14 squares have been assigned a digit
        // Final validation: check if exactly 28 distinct dominoes are used
        int actual_used_domino_count = 0;
        for (int i = 0; i < 7; ++i) {
            for (int j = i; j < 7; ++j) { // Iterate unique domino types (0-0 to 6-6 and 0-1 to 5-6)
                if (domino_types_used[i][j]) {
                    actual_used_domino_count++;
                }
            }
        }

        if (actual_used_domino_count == 28) { // All 28 unique domino types must be used exactly once
            total_ways++;
            if (!first_solution_found) {
                first_solution_found = true;
                // Store the current solution's grid
                for (int r = 0; r < N; ++r) {
                    for (int c = 0; c < M; ++c) {
                        if (is_covered[r][c]) {
                            // Find which 2x2 square (r,c) belongs to, get its assigned digit
                            int sq_i = cell_to_square_idx[{r, c}];
                            final_grid_result[r][c] = (char)('0' + assigned_square_values[sq_i]);
                        } else {
                            final_grid_result[r][c] = '.'; // Empty cell
                        }
                    }
                }
            }
        }
        return;
    }

    std::pair<int, int> current_square_coord = squares[square_idx];

    for (int d = 0; d <= 6; ++d) { // Try assigning digit 'd' (0-6) to the current 2x2 square
        if (digit_counts[d] == 2) continue; // Digit 'd' already used twice for squares

        digit_counts[d]++;
        assigned_square_values[square_idx] = d;

        bool conflict = false;
        std::vector<char> affected_chips_chars; // Chips whose status might change due to this assignment
        
        // Collect all chips that touch the current square
        std::pair<int, int> cells_in_square[4];
        cells_in_square[0] = {current_square_coord.first, current_square_coord.second};
        cells_in_square[1] = {current_square_coord.first, current_square_coord.second + 1};
        cells_in_square[2] = {current_square_coord.first + 1, current_square_coord.second};
        cells_in_square[3] = {current_square_coord.first + 1, current_square_coord.second + 1};

        for (int i = 0; i < 4; ++i) {
            affected_chips_chars.push_back(cell_to_chip_char[cells_in_square[i]]);
        }
        // Remove duplicates from affected_chips_chars
        std::sort(affected_chips_chars.begin(), affected_chips_chars.end());
        affected_chips_chars.erase(std::unique(affected_chips_chars.begin(), affected_chips_chars.end()), affected_chips_chars.end());

        // Keep track of changes made in this step for backtracking
        std::vector<std::pair<int, std::pair<int, int>>> modified_domino_assignments; // Stores {chip_int_id, old_domino_pair_for_chip}
        std::vector<std::pair<std::pair<int, int>, int>> modified_domino_types_used; // Stores {{d1,d2}, old_chip_int_id_for_domino}
        
        for (char chip_char : affected_chips_chars) {
            int chip_int_id = char_to_int(chip_char);
            std::pair<int, int> cell1 = chip_coords[chip_char].first;
            std::pair<int, int> cell2 = chip_coords[chip_char].second;
            int sq_idx1 = cell_to_square_idx[cell1];
            int sq_idx2 = cell_to_square_idx[cell2];

            // A chip's domino is fully determined if both its cells belong to squares whose values are now assigned
            // (i.e., square_idx1 and square_idx2 are both less than or equal to the current square_idx)
            if (sq_idx1 <= square_idx && sq_idx2 <= square_idx) {
                int val1 = assigned_square_values[sq_idx1];
                int val2 = assigned_square_values[sq_idx2];
                std::pair<int, int> required_domino = get_domino_pair(val1, val2);

                if (assigned_chip_dominoes[chip_int_id].first == -1) { // This chip was not fixed before this step
                    if (domino_types_used[required_domino.first][required_domino.second] && 
                        chip_for_domino[required_domino.first][required_domino.second] != chip_int_id) { 
                        // This domino type is already taken by a DIFFERENT chip
                        conflict = true;
                        break;
                    }
                    // Temporarily assign this domino for the current path
                    modified_domino_assignments.push_back({chip_int_id, assigned_chip_dominoes[chip_int_id]}); // Store old state
                    assigned_chip_dominoes[chip_int_id] = required_domino;

                    if (!domino_types_used[required_domino.first][required_domino.second]) { // Domino type wasn't used, now it is
                        modified_domino_types_used.push_back({required_domino, chip_for_domino[required_domino.first][required_domino.second]}); // Store old state
                        domino_types_used[required_domino.first][required_domino.second] = true;
                        chip_for_domino[required_domino.first][required_domino.second] = chip_int_id;
                    }
                } else if (assigned_chip_dominoes[chip_int_id] != required_domino) { 
                    // Chip was already fixed in a prior step, but this assignment implies a different domino. Conflict.
                    conflict = true;
                    break;
                }
            }
        }

        if (!conflict) {
            solve(square_idx + 1);
        }

        // Backtrack: undo changes made in this step for this digit 'd'
        for (const auto& entry : modified_domino_types_used) { // Undo changes to domino_types_used
            domino_types_used[entry.first.first][entry.first.second] = false; // Restore to false (only became true in this step)
            chip_for_domino[entry.first.first][entry.first.second] = entry.second; // Restore old chip_int_id (was -1)
        }
        for (const auto& entry : modified_domino_assignments) { // Undo changes to assigned_chip_dominoes
            assigned_chip_dominoes[entry.first] = entry.second; // Restore old state (was {-1,-1})
        }
        digit_counts[d]--; // Decrement count for digit 'd'
    }
}


int main() {
    fast_io();

    std::cin >> N >> M;

    std::vector<std::pair<int, int>> temp_chip_cells[28]; // Temporary storage for cells of each chip character

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            std::cin >> initial_grid[r][c];
            if (initial_grid[r][c] != '.') {
                is_covered[r][c] = true;
                temp_chip_cells[char_to_int(initial_grid[r][c])].push_back({r, c});
            } else {
                is_covered[r][c] = false;
            }
        }
    }

    // Populate chip_coords and cell_to_chip_char maps
    // These mappings are used globally in the backtracking
    for (int i = 0; i < 28; ++i) {
        char c = (i < 26) ? ('a' + i) : ('A' + (i - 26));
        chip_coords[c] = {temp_chip_cells[i][0], temp_chip_cells[i][1]};
        cell_to_chip_char[temp_chip_cells[i][0]] = c;
        cell_to_chip_char[temp_chip_cells[i][1]] = c;
    }

    // Identify the 14 non-overlapping 2x2 squares
    // The problem implies these are uniquely defined by the chip layout and cover all chip cells.
    for (int r = 0; r < N - 1; ++r) {
        for (int c = 0; c < M - 1; ++c) {
            if (is_covered[r][c] && is_covered[r + 1][c] && is_covered[r][c + 1] && is_covered[r + 1][c + 1]) {
                squares.push_back({r, c}); // Add top-left corner of valid 2x2 square
            }
        }
    }
    
    // Populate cell_to_square_idx map
    // Each cell covered by a chip belongs to exactly one of the 14 2x2 squares
    for (int i = 0; i < 14; ++i) {
        std::pair<int, int> sq_tl = squares[i];
        cell_to_square_idx[sq_tl] = i;
        cell_to_square_idx[{sq_tl.first, sq_tl.second + 1}] = i;
        cell_to_square_idx[{sq_tl.first + 1, sq_tl.second}] = i;
        cell_to_square_idx[{sq_tl.first + 1, sq_tl.second + 1}] = i;
    }

    // Initialize global backtracking state variables
    for (int i = 0; i < 7; ++i) digit_counts[i] = 0;
    for (int i = 0; i < 14; ++i) assigned_square_values[i] = -1; // -1 indicates unassigned
    for (int i = 0; i < 28; ++i) assigned_chip_dominoes[i] = {-1, -1}; // {-1,-1} indicates unassigned
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            domino_types_used[i][j] = false;
            chip_for_domino[i][j] = -1; // -1 indicates no chip owns this domino type
        }
    }

    // Start the backtracking search from the first square (index 0)
    solve(0);

    // Print the total number of ways
    std::cout << total_ways << "\n";
    // Print one of the possible solutions
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            std::cout << final_grid_result[r][c];
        }
        std::cout << "\n";
    }

    return 0;
}