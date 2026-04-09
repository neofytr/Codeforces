#include <bits/stdc++.h>

int main() {
    // Optimize C++ standard streams for competitive programming
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    // Variables to store the name and score of the first team encountered
    std::string team1_name = "";
    int team1_score = 0;

    // Variables to store the name and score of the second team encountered
    std::string team2_name = "";
    int team2_score = 0;

    for (int i = 0; i < n; ++i) {
        std::string current_team_name;
        std::cin >> current_team_name;

        // If team1_name is empty, this is the first goal and defines team1
        if (team1_name == "") {
            team1_name = current_team_name;
            team1_score++;
        } 
        // If the current goal is scored by team1
        else if (current_team_name == team1_name) {
            team1_score++;
        } 
        // Otherwise, the current goal must be scored by the second team.
        // (Guaranteed that there are no more than two different teams
        // and the match did not end in a tie.)
        else { 
            // If team2_name is still empty, this is the first time we see team2.
            // Otherwise, team2_name is already set to current_team_name (the second unique team).
            team2_name = current_team_name; // Set (or re-set) team2's name
            team2_score++;
        }
    }

    // After processing all goals, compare scores to find the winner.
    // It's guaranteed the match did not end in a tie.
    if (team1_score > team2_score) {
        std::cout << team1_name << std::endl;
    } else { // team2_score must be greater
        std::cout << team2_name << std::endl;
    }

    return 0;
}