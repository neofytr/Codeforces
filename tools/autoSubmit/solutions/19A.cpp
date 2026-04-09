#include <bits/stdc++.h>

struct Team {
    std::string name;
    int points;
    int goals_scored;
    int goals_missed;

    // Constructor to easily initialize, using move semantics for efficiency
    Team(std::string n) : name(std::move(n)), points(0), goals_scored(0), goals_missed(0) {}
    // Default constructor, necessary if std::map might default-construct values
    Team() : name(""), points(0), goals_scored(0), goals_missed(0) {}
};

// Custom comparison function for sorting teams according to problem rules
bool compareTeams(const Team& a, const Team& b) {
    // Rule 1: Primary - Points (decreasing order)
    if (a.points != b.points) {
        return a.points > b.points;
    }
    
    // Rule 2: Secondary - Goal Difference (goals scored - goals missed, decreasing order)
    int gd_a = a.goals_scored - a.goals_missed;
    int gd_b = b.goals_scored - b.goals_missed;
    if (gd_a != gd_b) {
        return gd_a > gd_b;
    }
    
    // Rule 3: Tertiary - Goals Scored (decreasing order)
    return a.goals_scored > b.goals_scored;
    
    // The problem statement guarantees that these three rules "help to order the teams
    // without ambiguity", meaning no further tie-breakers (like lexicographical name order)
    // are needed for the main sorting phase to determine ranks.
}

int main() {
    // Fast I/O setup
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    // Use a map to store team data, mapping team name (string) to Team object.
    // This allows O(log N) lookup by name for updating scores.
    std::map<std::string, Team> teams_map;
    for (int i = 0; i < n; ++i) {
        std::string team_name;
        std::cin >> team_name;
        // Construct Team object in place within the map
        teams_map.emplace(team_name, Team(team_name)); 
    }

    // There are n * (n - 1) / 2 matches in a round-robin tournament
    int num_matches = n * (n - 1) / 2;
    for (int i = 0; i < num_matches; ++i) {
        std::string match_line;
        std::cin >> match_line; // Read the entire match description line, e.g., "A-B 1:1"

        // Parse match_line into name1, name2, num1, num2
        // Find the position of '-' to separate name1 from the rest
        size_t dash_pos = match_line.find('-');
        std::string name1 = match_line.substr(0, dash_pos);

        // Find the position of ' ' to separate name2 from the scores
        size_t space_pos = match_line.find(' ', dash_pos + 1);
        std::string name2 = match_line.substr(dash_pos + 1, space_pos - (dash_pos + 1));
        
        // Find the position of ':' to separate score num1 from num2
        size_t colon_pos = match_line.find(':', space_pos + 1);
        int num1 = std::stoi(match_line.substr(space_pos + 1, colon_pos - (space_pos + 1)));
        int num2 = std::stoi(match_line.substr(colon_pos + 1));

        // Update statistics for team1
        teams_map[name1].goals_scored += num1;
        teams_map[name1].goals_missed += num2;

        // Update statistics for team2
        teams_map[name2].goals_scored += num2;
        teams_map[name2].goals_missed += num1;

        // Update points based on match outcome
        if (num1 > num2) { // name1 wins
            teams_map[name1].points += 3;
        } else if (num2 > num1) { // name2 wins
            teams_map[name2].points += 3;
        } else { // Draw
            teams_map[name1].points += 1;
            teams_map[name2].points += 1;
        }
    }

    // Transfer teams from map values to a vector.
    // std::map elements are inherently sorted by key, but we need custom sorting based on rules.
    std::vector<Team> teams_vec;
    for (const auto& pair : teams_map) {
        teams_vec.push_back(pair.second); // 'pair.second' is the Team object
    }

    // Sort the vector of teams using the custom comparison function
    std::sort(teams_vec.begin(), teams_vec.end(), compareTeams);

    // Collect the names of the top n/2 qualifying teams
    std::vector<std::string> qualified_names;
    for (int i = 0; i < n / 2; ++i) {
        qualified_names.push_back(teams_vec[i].name);
    }

    // Sort the collected qualified names lexicographically (as required for output)
    std::sort(qualified_names.begin(), qualified_names.end());

    // Output the qualified names, each on a new line
    for (const std::string& name : qualified_names) {
        std::cout << name << "\n";
    }

    return 0;
}