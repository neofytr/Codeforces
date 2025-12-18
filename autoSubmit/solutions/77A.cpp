#include <bits/stdc++.h>

// Function for fast I/O
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

// Map hero names to integer IDs (0-6)
std::map<std::string, int> name_to_id;

// Adjacency matrix to store liking relationships: likes[i][j] is true if hero i likes hero j
bool likes[7][7];

// Experience points for destroying each megaboss
long long A, B, C;

// Global variables to store the best results found
long long min_overall_diff = std::numeric_limits<long long>::max(); // Initialize with the maximum possible long long value
long long max_overall_liking = -1; // Initialize with -1, as liking can be 0 or positive

// Array to store current team assignments during recursion.
// current_teams[hero_id] will be 0, 1, or 2, representing assignment to Mephisto, Diablo, or Baal's team.
int current_teams[7];

// Initializes the map for hero names to integer IDs
void init_hero_names() {
    name_to_id["Anka"] = 0;
    name_to_id["Chapay"] = 1;
    name_to_id["Cleo"] = 2;
    name_to_id["Troll"] = 3;
    name_to_id["Dracul"] = 4;
    name_to_id["Snowy"] = 5;
    name_to_id["Hexadecimal"] = 6;
}

// Recursive function to explore all possible team assignments
// hero_idx: the index of the hero currently being assigned to a team (0 to 6)
void solve(int hero_idx) {
    // Base case: All 7 heroes have been assigned to a team
    if (hero_idx == 7) {
        int team_counts[3] = {0, 0, 0}; // Count of heroes in each of the three teams
        for (int i = 0; i < 7; ++i) {
            team_counts[current_teams[i]]++;
        }

        // Check if all three teams are non-empty. This is required as all megabosses must be destroyed.
        if (team_counts[0] == 0 || team_counts[1] == 0 || team_counts[2] == 0) {
            return; // Invalid partition, skip
        }

        // Calculate experience received by heroes in each team
        long long exp0 = A / team_counts[0]; // Experience for Mephisto's team
        long long exp1 = B / team_counts[1]; // Experience for Diablo's team
        long long exp2 = C / team_counts[2]; // Experience for Baal's team

        // Find the maximum and minimum experience values among the three teams
        long long max_e = std::max({exp0, exp1, exp2});
        long long min_e = std::min({exp0, exp1, exp2});
        long long current_diff = max_e - min_e; // Calculate the difference

        // Calculate the total amount of liking within teams for the current partition
        long long current_liking = 0;
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                // If hero i likes hero j AND they are in the same team (and not the same hero)
                if (i != j && current_teams[i] == current_teams[j] && likes[i][j]) {
                    current_liking++;
                }
            }
        }

        // Update global best results based on primary (minimize difference) and secondary (maximize liking) criteria
        if (current_diff < min_overall_diff) {
            // Found a new minimum difference
            min_overall_diff = current_diff;
            max_overall_liking = current_liking;
        } else if (current_diff == min_overall_diff) {
            // Found a partition with the same minimum difference, maximize liking
            max_overall_liking = std::max(max_overall_liking, current_liking);
        }
        return;
    }

    // Recursive step: Assign the current hero (hero_idx) to each of the three teams
    for (int team_id = 0; team_id < 3; ++team_id) {
        current_teams[hero_idx] = team_id; // Assign hero_idx to team_id
        solve(hero_idx + 1);             // Recurse for the next hero
    }
}

int main() {
    fast_io(); // Enable fast I/O

    init_hero_names(); // Initialize hero name mappings

    int n; // Number of liking relationships
    std::cin >> n;

    // Read and store liking relationships
    for (int k = 0; k < n; ++k) {
        std::string p_name, dummy_likes, q_name;
        std::cin >> p_name >> dummy_likes >> q_name; // "dummy_likes" is just to consume the "likes" string
        int p_id = name_to_id[p_name];
        int q_id = name_to_id[q_name];
        likes[p_id][q_id] = true;
    }

    // Read megaboss experience values
    std::cin >> A >> B >> C;

    // Start the recursive brute-force search for team assignments
    solve(0); // Start with hero 0

    // Print the final results: minimal experience difference and maximal liking
    std::cout << min_overall_diff << " " << max_overall_liking << std::endl;

    return 0;
}