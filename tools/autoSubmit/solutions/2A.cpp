#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<std::pair<std::string, int>> rounds_data(n);
    std::map<std::string, int> final_scores;

    for (int i = 0; i < n; ++i) {
        std::string name;
        int score;
        std::cin >> name >> score;
        rounds_data[i] = {name, score};
        final_scores[name] += score;
    }

    int max_score = std::numeric_limits<int>::min();
    for (const auto& pair : final_scores) {
        max_score = std::max(max_score, pair.second);
    }
    
    // Identify potential winners: players who ended with max_score
    std::vector<std::string> potential_winners_names;
    for (const auto& pair : final_scores) {
        if (pair.second == max_score) {
            potential_winners_names.push_back(pair.first);
        }
    }

    // If only one potential winner, that's the winner
    if (potential_winners_names.size() == 1) {
        std::cout << potential_winners_names[0] << std::endl;
        return 0;
    }

    // Tie-breaking: Replay rounds to find who reached max_score first among potential winners
    std::map<std::string, int> current_scores_during_replay;
    std::string winner_name = "";

    for (const auto& round : rounds_data) {
        const std::string& name = round.first;
        int score_delta = round.second;

        current_scores_during_replay[name] += score_delta;

        // Check if this player is one of the final max_score holders
        // AND if they have reached or exceeded max_score at this point
        if (final_scores.at(name) == max_score && current_scores_during_replay.at(name) >= max_score) {
            winner_name = name;
            break; 
        }
    }

    std::cout << winner_name << std::endl;

    return 0;
}